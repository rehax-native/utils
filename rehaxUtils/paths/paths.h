#pragma once

#include <iostream>

namespace rehaxUtils {

class Paths {

public:
  static std::string getCurrentUserHomeDirectory();
  static std::string getCurrentUserDesktopDirectory();
};

}
