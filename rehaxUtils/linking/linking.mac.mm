#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "links.h"

void rehaxUtils::Linking::openUrl(std::string url) {
  NSString * nsUrl = [NSString stringWithUTF8String:url.c_str()];
  NSURL * nsUrlObj = [NSURL URLWithString:nsUrl];
  [[NSWorkspace sharedWorkspace] openURL:nsUrlObj];
}
