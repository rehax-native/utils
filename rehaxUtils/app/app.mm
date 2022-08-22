#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "paths.h"

std::string rehaxUtils::App::getApplicationSupportDirectory() {
  NSArray * paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString * applicationSupportDirectory = [paths firstObject];
  return [applicationSupportDirectory UTF8String];
}

std::string rehaxUtils::App::getApplicationGroupContainerDirectory(std::string appGroupID) {
  NSFileManager* mgr = [NSFileManager defaultManager];
  NSURL* url = [mgr containerURLForSecurityApplicationGroupIdentifier:[NSString stringWithUTF8String:appGroupID.c_str()]];
  return [[url path] UTF8String];
}
