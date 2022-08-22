#pragma once

#include <iostream>

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
