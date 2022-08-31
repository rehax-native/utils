#include <Shlobj.h>
#include "paths.h"

std::string rehaxUtils::Paths::getCurrentUserHomeDirectory() {
  WCHAR path[MAX_PATH + 1] = {0};
  if (SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path) != S_OK) {
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

std::string rehaxUtils::Paths::getCurrentUserDesktopDirectory() {
  WCHAR path[MAX_PATH+1];
  if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE) != S_OK) {
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
