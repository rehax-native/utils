#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "app.h"

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

static NSMutableDictionary * applicationThemeListeners = nil;
static int nextListenerId = 0;

@interface AppThemeListener : NSObject
{
  @public
  std::function<void(rehaxUtils::App::ApplicationTheme)> callback;
}
@end

@implementation AppThemeListener

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
  callback(rehaxUtils::App::getApplicationTheme());
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
  if (applicationThemeListeners == nil) {
    applicationThemeListeners = [NSMutableDictionary new];
  }
  nextListenerId++;
  AppThemeListener * listener = [AppThemeListener new];
  listener->callback = callback;
  applicationThemeListeners[[NSNumber numberWithInt:nextListenerId]] = listener;
  [NSApp addObserver:listener forKeyPath:@"effectiveAppearance" options:NSKeyValueObservingOptionNew context:nil];
  return { nextListenerId };
}

void rehaxUtils::App::removeApplicationThemeChangeListener(rehaxUtils::App::ApplicationThemeListenerId listenerId)
{
  NSNumber * key = [NSNumber numberWithInt:listenerId.id];
  if ([applicationThemeListeners objectForKey:key]) {
    AppThemeListener * listener = applicationThemeListeners[key];
    [NSApp removeObserver:listener forKeyPath:@"effectiveAppearance"];
    [applicationThemeListeners removeObjectForKey:key];
  }
}
