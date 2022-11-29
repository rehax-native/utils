#pragma once

#include <iostream>

namespace rehaxUtils {

class App {

public:
  static std::string getApplicationSupportDirectory();
  static std::string getApplicationSupportDirectoryForApp();
  static std::string getApplicationGroupContainerDirectory(std::string appGroupID);

  enum class ApplicationTheme {
    /** OS does not support theming */
    Unsupported,

    SystemLight,
    SystemDark,
  };

  struct ApplicationThemeListenerId
  {
    int id;
  };

  static ApplicationTheme getApplicationTheme();
  static ApplicationThemeListenerId addApplicationThemeChangeListener(std::function<void(ApplicationTheme)> listener);
  static void removeApplicationThemeChangeListener(ApplicationThemeListenerId listenerId);
};

}
