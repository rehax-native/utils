#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x601
#endif
#include <Shlobj.h>

#include "app.h"

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
  // Unsupported on win
  return "";
}
