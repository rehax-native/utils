/*
  Because of the asynchronous nature of the httpFetch library, we don't use gtest
*/

#include "../HttpFetch.h"
#include <cassert>

using namespace rehaxUtils;

int main() {
  HttpFetch::makeRequest(HttpRequest{
    .url = "https://httpbin.org/get",
    .method = HttpMethod::GET,
    .callback = [] (HttpResponse response) {
      assert(response.status == 200);
    }
  });
  return 0;
}
