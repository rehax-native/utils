#include "linking.h"

void rehaxUtils::Linking::openUrl(std::string url) {
  system((std::string("cmd /c start ") + url).c_str());
}
