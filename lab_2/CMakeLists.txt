cmake_minimum_required(VERSION 3.10)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${CMAKE_PROJECT_NAME}_lib src/twelve.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC include)


add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)


enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)
target_include_directories(tests PRIVATE include)

add_test(NAME TwelveTests COMMAND tests)