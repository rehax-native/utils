#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "paths.h"

std::string rehaxUtils::App::getCurrentUserHomeDirectory() {
  NSString * homeDirectory = NSHomeDirectory();
  return [homeDirectory UTF8String];
}

std::string rehaxUtils::App::getCurrentUserDesktopDirectory() {
  NSArray * paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);
  NSString * applicationSupportDirectory = [paths firstObject];
  return [applicationSupportDirectory UTF8String];
}
