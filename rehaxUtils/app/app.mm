#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "app.h"
#include <unordered_map>

std::string rehaxUtils::App::getApplicationSupportDirectory() {
  NSArray * paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString * applicationSupportDirectory = [paths firstObject];
  return [applicationSupportDirectory UTF8String];
}

std::string rehaxUtils::App::getApplicationSupportDirectoryForApp() {
  NSArray * paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString * applicationSupportDirectory = [paths firstObject];

  NSString * appBundleID = [[NSBundle mainBundle] bundleIdentifier];
  return [[applicationSupportDirectory stringByAppendingPathComponent:appBundleID] UTF8String];
}

std::string rehaxUtils::App::getApplicationGroupContainerDirectory(std::string appGroupID) {
  NSFileManager* mgr = [NSFileManager defaultManager];
  NSURL* url = [mgr containerURLForSecurityApplicationGroupIdentifier:[NSString stringWithUTF8String:appGroupID.c_str()]];
  return [[url path] UTF8String];
}

@interface AppThemeListener : NSObject
{
  @public
  int nextListenerId;
  bool didStartListening;
  std::unordered_map<int, std::function<void(rehaxUtils::App::ApplicationTheme)>> applicationThemeListeners;
}

+ (AppThemeListener *)sharedListener;
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context;

@end

@implementation AppThemeListener

+ (AppThemeListener *)sharedListener
{
  static AppThemeListener * shared = nil;
  @synchronized(self) {
    if (shared == nil) {
      shared = [[self alloc] init];
      shared->nextListenerId = 0;
      shared->didStartListening = false;
    }
  }
  return shared;
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
  for (auto & pair : applicationThemeListeners) {
    pair.second(rehaxUtils::App::getApplicationTheme());
  }
}

@end

rehaxUtils::App::ApplicationTheme rehaxUtils::App::getApplicationTheme()
{
  if (
    [NSApp.effectiveAppearance.name isEqualToString:NSAppearanceNameDarkAqua] ||
    [NSApp.effectiveAppearance.name isEqualToString:NSAppearanceNameVibrantDark] ||
    [NSApp.effectiveAppearance.name isEqualToString:NSAppearanceNameAccessibilityHighContrastDarkAqua] ||
    [NSApp.effectiveAppearance.name isEqualToString:NSAppearanceNameAccessibilityHighContrastVibrantDark]
  ) {
    return rehaxUtils::App::ApplicationTheme::SystemDark;
  }
  return rehaxUtils::App::ApplicationTheme::SystemLight;
}

rehaxUtils::App::ApplicationThemeListenerId rehaxUtils::App::addApplicationThemeChangeListener(std::function<void(rehaxUtils::App::ApplicationTheme)> callback)
{
  AppThemeListener.sharedListener->nextListenerId++;
  
  // Before the app has finished launching, adding observer will have no effect
  // Therefore we add the observer only when we have an effectiveAppearance
  if (!AppThemeListener.sharedListener->didStartListening && NSApp.effectiveAppearance.name != nil) {
    [NSApp addObserver:AppThemeListener.sharedListener forKeyPath:@"effectiveAppearance" options:NSKeyValueObservingOptionNew context:nil];
    AppThemeListener.sharedListener->didStartListening = true;
  }
  AppThemeListener.sharedListener->applicationThemeListeners[AppThemeListener.sharedListener->nextListenerId] = callback;
  return { AppThemeListener.sharedListener->nextListenerId };
}

void rehaxUtils::App::removeApplicationThemeChangeListener(rehaxUtils::App::ApplicationThemeListenerId listenerId)
{
  if (AppThemeListener.sharedListener->applicationThemeListeners.contains(listenerId.id)) {
    AppThemeListener.sharedListener->applicationThemeListeners.erase(listenerId.id);
  }
}
