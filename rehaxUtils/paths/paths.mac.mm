#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "paths.h"

std::string rehaxUtils::Paths::getCurrentUserHomeDirectory() {
  NSString * homeDirectory = NSHomeDirectory();
  return [homeDirectory UTF8String];
}

std::string rehaxUtils::Paths::getCurrentUserDesktopDirectory() {
  NSArray * paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);
  NSString * applicationSupportDirectory = [paths firstObject];
  return [applicationSupportDirectory UTF8String];
}
