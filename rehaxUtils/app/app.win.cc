#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x601
#endif
#include <Shlobj.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Foundation.h>
#include <filesystem>

#include "app.h"

#define MAX_WIN32_PATH_LEN 256

std::string rehaxUtils::App::getApplicationSupportDirectory() {
  WCHAR path[MAX_PATH+1];
  if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_APPDATA, FALSE) != S_OK) {
    return "";
  }

  int pathlen = lstrlenW(path);

  int buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, NULL, 0, NULL, NULL);
  if (buflen <= 0) {
    return "";
  }

  char *buffer = new char[buflen+1];
  buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, buffer, buflen, NULL, NULL);
  if (buflen <= 0) {
    delete[] buffer;
    return "";
  }
  buffer[buflen] = 0;
  return std::string(buffer);
}

std::string rehaxUtils::App::getApplicationSupportDirectoryForApp() {
  WCHAR path[MAX_PATH+1];
  if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_APPDATA, FALSE) != S_OK) {
    return "";
  }

  int pathlen = lstrlenW(path);

  int buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, NULL, 0, NULL, NULL);
  if (buflen <= 0) {
    return "";
  }

  char *buffer = new char[buflen+1];
  buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, buffer, buflen, NULL, NULL);
  if (buflen <= 0) {
    delete[] buffer;
    return "";
  }
  buffer[buflen] = 0;

  std::string fullPath = std::string(buffer) + "\\";

  GetModuleFileNameW(NULL, path, MAX_PATH);
  pathlen = lstrlenW(path);

  buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, NULL, 0, NULL, NULL);
  if (buflen <= 0) {
      return "";
  }

  buflen = WideCharToMultiByte(CP_UTF8, 0, path, pathlen, buffer, buflen, NULL, NULL);
  if (buflen <= 0) {
      delete[] buffer;
      return "";
  }
  buffer[buflen] = 0;

  return fullPath + std::string(buffer);
}

std::string rehaxUtils::App::getApplicationGroupContainerDirectory(std::string appGroupID) {
  auto moduleHandle = GetModuleHandleA(appGroupID.c_str());
  const char filename[MAX_WIN32_PATH_LEN] = "";
  GetModuleFileNameA(moduleHandle, (LPSTR) & filename[0], MAX_WIN32_PATH_LEN);

  std::filesystem::path path(filename);
  std::string containerPath = path.parent_path().parent_path().string();

  return containerPath;
}

using namespace winrt::Windows::UI::ViewManagement;

rehaxUtils::App::ApplicationTheme rehaxUtils::App::getApplicationTheme() {
    auto settings = UISettings();
    auto foreground = settings.GetColorValue(UIColorType::Foreground);
    auto clr = foreground;
    bool isColorLight = (((5 * clr.G) + (2 * clr.R) + clr.B) > (8 * 128));
    bool isDarkMode = isColorLight;
    return isDarkMode ? ApplicationTheme::SystemDark : ApplicationTheme::SystemLight;
}

static std::unordered_map<int, winrt::event_token> themeListeners;
static int nextThemeListenerId = 0;

rehaxUtils::App::ApplicationThemeListenerId rehaxUtils::App::addApplicationThemeChangeListener(std::function<void(ApplicationTheme)> listener)
{
    // winrt::init_apartment();
    auto settings = UISettings();
    // std::cout << "Listening for theme " << std::endl;
    // This doesn't work. The event handler is never called.
    auto revoker = settings.ColorValuesChanged([listener] (auto&&...) {
        // std::cout << "Theme changed " << std::endl;
        listener(getApplicationTheme());
    });
    nextThemeListenerId++;
    themeListeners[nextThemeListenerId] = revoker;
    return { nextThemeListenerId };
}

void rehaxUtils::App::removeApplicationThemeChangeListener(ApplicationThemeListenerId listenerId)
{
    auto it = themeListeners.find(listenerId.id);
    if (it != themeListeners.end()) {
        auto settings = UISettings();
        settings.ColorValuesChanged(it->second);
        themeListeners.erase(listenerId.id);
    }
}
