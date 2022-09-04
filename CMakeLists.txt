cmake_minimum_required(VERSION 3.14)
project(rehaxUtils)

set(CMAKE_CXX_STANDARD 20)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(MACOSX TRUE)
endif()
if (WIN32)
  set(WIN TRUE)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(.)

enable_testing()

add_executable(
  ObjectPtrTest
  rehaxUtils/pointers/Object.h
  rehaxUtils/pointers/__test__/ReferenceCounterTest.cc
  rehaxUtils/pointers/__test__/ReferenceCounterTreeTest.cc
  rehaxUtils/pointers/__test__/CastTest.cc
)
target_link_libraries(
  ObjectPtrTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ObjectPtrTest)

# To run the tests:
# cmake -S . -B build_test
# cmake --build build_test --target ObjectPtrTest
# build_test/ObjectPtrTest

# To create an xcode project for development:
# cmake -G Xcode -S . -B build
if (${MACOSX})
  file(GLOB REHAX_UTILS_MAC_SRC_FILES
    rehaxUtils/linking/linking.mac.mm
    rehaxUtils/timer/mac/timer.mm
    rehaxUtils/httpFetch/HttpFetch.cc
    rehaxUtils/httpFetch/HttpFetch.mac.mm
    rehaxUtils/app/app.mm
    rehaxUtils/paths/paths.mac.mm
  )

  add_library(
    rehax-utils-mac STATIC
    ${REHAX_UTILS_MAC_SRC_FILES}
  )

  add_executable(
    rehax-utils-mac-http-test
    rehaxUtils/httpFetch/HttpFetch.cc
    rehaxUtils/httpFetch/HttpFetch.mac.mm
    rehaxUtils/httpFetch/__test__/Verbs.cc
  )
  target_link_libraries(
    rehax-utils-mac-http-test
    "-framework Foundation"
  )
endif()

if (${WIN})
  file(GLOB REHAX_UTILS_WIN_SRC_FILES
    rehaxUtils/linking/linking.win.cc
    rehaxUtils/timer/win/timer.cc
    rehaxUtils/httpFetch/HttpFetch.cc
    rehaxUtils/httpFetch/HttpFetch.win.cc
    rehaxUtils/app/app.win.cc
    rehaxUtils/paths/paths.win.cc
  )

  add_library(
    rehax-utils-win STATIC
    ${REHAX_UTILS_WIN_SRC_FILES}
  )

  add_executable(
    rehax-utils-win-http-test
    rehaxUtils/httpFetch/HttpFetch.cc
    rehaxUtils/httpFetch/HttpFetch.win.cc
    rehaxUtils/httpFetch/__test__/Verbs.cc
  )
  # target_link_libraries(
  #   rehax-utils-win-http-test
  #   # "-framework Foundation"
  # )
endif()
