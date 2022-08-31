#import <Foundation/Foundation.h>
#include "HttpFetch.h"

using namespace rehaxUtils;

void HttpFetch::makeRequest(HttpRequest request) {
  @autoreleasepool {
    NSString *nsUrl = [NSString stringWithUTF8String:request.url.c_str()];
    NSMutableURLRequest * urlRequest = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:nsUrl]];
    switch (request.method) {
      case HttpMethod::GET:
        urlRequest.HTTPMethod = @"GET";
        break;
      case HttpMethod::POST:
        urlRequest.HTTPMethod = @"POST";
        break;
      case HttpMethod::PUT:
        urlRequest.HTTPMethod = @"PUT";
        break;
      case HttpMethod::PATCH:
        urlRequest.HTTPMethod = @"PATCH";
        break;
      case HttpMethod::DELETE:
        urlRequest.HTTPMethod = @"DELETE";
        break;
      case HttpMethod::OPTIONS:
        urlRequest.HTTPMethod = @"OPTIONS";
        break;
    }
    if (request.body.hasPointer() && request.body->data() != nullptr && request.body->size() > 0) {
      NSData *nsData = [NSData dataWithBytes:request.body->data() length:request.body->size()];
      // NSLog(@"%@", nsData);
      // NSLog(@"%@", [NSString stringWithUTF8String:(const char*) data]);
      urlRequest.HTTPBody = nsData;
    }

    for (const auto & [key, value] : request.requestHeaders) {
      NSString *nsKey = [NSString stringWithUTF8String:key.c_str()];
      NSString *nsValue = [NSString stringWithUTF8String:value.c_str()];
      [urlRequest setValue:nsValue forHTTPHeaderField:nsKey];
    }

    NSURLSession * session = [NSURLSession sharedSession];
    NSRunLoop * currentRunLoop = [NSRunLoop currentRunLoop];

    auto callback = request.callback;
    // static int runloopcounter = 0;
    // static bool handlesRunloop = false;

    NSURLSessionDataTask * task = [session dataTaskWithRequest:urlRequest completionHandler:^(NSData *data, NSURLResponse *urlResponse, NSError *error) {
      HttpResponse response;
      if (error) {
        response.errorMessage = [[error localizedDescription] UTF8String];
        // NSLog(@"Error: %@", error);
        // callback([[error localizedDescription] UTF8String], 0, {}, nullptr, 0);
      } else {
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *) urlResponse;
        response.status = [httpResponse statusCode];

        NSUInteger len = [data length];
        if (len > 0) {
          void * typedData = malloc(len);
          memcpy(typedData, [data bytes], len);
          response.body = Object<HttpBody>::Create(typedData, len);
        }
      }
      dispatch_async(dispatch_get_main_queue(), ^{
        callback(response);
      });

      // if (handlesRunloop) {
      //   runloopcounter--;
      //   if (runloopcounter == 0) {
      //     CFRunLoopStop(CFRunLoopGetCurrent());
      //   }
      // }
    }];

    [task resume];

    // if ([currentRunLoop currentMode] == nullptr) {
    //   // handlesRunloop = true;
    //   // runloopcounter++;
    //   [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:5]];
    // // } else if (handlesRunloop) {
    // //   runloopcounter++;
    // }
  }
}
