#pragma once

#include <iostream>

#if __APPLE__
#include <TargetConditionals.h>
#endif

namespace rehaxUtils {

enum class OSName {
    Android,
    IOs,
    Mac,
    Linux,
    Windows,
};

class OS {
public:
  constexpr static OSName name();
  constexpr static bool isWindows();
  constexpr static bool isMac();
  constexpr static bool isIos();
  constexpr static bool isAndroid();
  constexpr static bool isLinux();
};

}

constexpr rehaxUtils::OSName rehaxUtils::OS::name() {
  if (rehaxUtils::OS::isWindows()) {
    return OSName::Windows;
  }
  if (rehaxUtils::OS::isMac()) {
    return OSName::Mac;
  }
  if (rehaxUtils::OS::isIos()) {
    return OSName::IOs;
  }
  // Android must come before linux, because it also is linux.
  if (rehaxUtils::OS::isAndroid()) {
    return OSName::Android;
  }
  if (rehaxUtils::OS::isLinux()) {
    return OSName::Linux;
  }
}

constexpr bool rehaxUtils::OS::isWindows() {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  return true;
  #else
  return false;
  #endif
}

constexpr bool rehaxUtils::OS::isMac() {
  #if __APPLE__ && TARGET_OS_MAC
  return true;
  #else
  return false;
  #endif
}

constexpr bool rehaxUtils::OS::isIos() {
  #if __APPLE__ && TARGET_OS_IPHONE
  return true;
  #else
  return false;
  #endif
}

constexpr bool rehaxUtils::OS::isAndroid() {
  #if __ANDROID__
  return true;
  #else
  return false;
  #endif
}

constexpr bool rehaxUtils::OS::isLinux() {
  #if __linux__
  return true;
  #else
  return false;
  #endif
}