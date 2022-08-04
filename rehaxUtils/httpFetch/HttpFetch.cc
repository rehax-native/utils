#include "HttpFetch.h"

using namespace rehaxUtils;

HttpBody::HttpBody() {}

HttpBody::HttpBody(void * data, size_t size)
:_data(data), _size(size) {}

HttpBody::~HttpBody() {
  if (_data != nullptr) {
    free(_data);
  }
}

size_t HttpBody::size() {
  return _size;
}

void * HttpBody::data() {
  return _data;
}