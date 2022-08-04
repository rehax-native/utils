#pragma once

#include <unordered_map>
#include <iostream>
#include <functional>
#include "../pointers/Object.h"

namespace rehaxUtils {

enum class HttpMethod {
  GET,
  POST,
  PUT,
  PATCH,
  DELETE,
  OPTIONS
};

class HttpBody : public Object<HttpBody> {
public:
  HttpBody();
  HttpBody(void * data, size_t size);
  ~HttpBody();

  size_t size();
  void * data();

private:
  void * _data = nullptr;
  size_t _size = 0;
};

struct HttpResponse {
  std::string errorMessage;
  int status = 0;
  std::unordered_map<std::string, std::string> responseHeaders;
  ObjectPointer<HttpBody> body;
};

struct HttpRequest {
  std::string url;
  HttpMethod method;
  std::unordered_map<std::string, std::string> requestHeaders;
  ObjectPointer<HttpBody> body;
  std::function<void(HttpResponse)> callback;
};

class HttpFetch {

public:
  static void makeRequest(HttpRequest request);
};

}
