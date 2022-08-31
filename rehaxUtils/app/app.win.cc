#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
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
  // NSArray * paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  // NSString * applicationSupportDirectory = [paths firstObject];

  // NSString * appBundleID = [[NSBundle mainBundle] bundleIdentifier];
  // return [[applicationSupportDirectory stringByAppendingPathComponent:appBundleID] UTF8String];

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
  return std::string(buffer) + "\\" + bunldeId;


  TCHAR szFileName[MAX_PATH];

GetModuleFileName(NULL, szFileName, MAX_PATH)
}

std::string rehaxUtils::App::getApplicationGroupContainerDirectory(std::string appGroupID) {
  // Unsupported on win
  return "";
}
