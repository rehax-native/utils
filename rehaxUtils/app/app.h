#pragma once

#include <iostream>

namespace rehaxUtils {

class App {

public:
  static std::string getApplicationSupportDirectory();
  static std::string getApplicationSupportDirectoryForApp();
  static std::string getApplicationGroupContainerDirectory(std::string appGroupID);
};

}
