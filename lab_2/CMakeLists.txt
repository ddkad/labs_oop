cmake_minimum_required(VERSION 3.14) 
project(lab_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(lab_2_lib src/twelve.cpp) 
target_include_directories(lab_2_lib PUBLIC include)

add_executable(lab_2_exe src/main.cpp) 
target_link_libraries(lab_2_exe PRIVATE lab_2_lib)

enable_testing()
add_executable(tests test/tests.cpp)
target_link_libraries(tests lab_2_lib gtest_main)  
target_include_directories(tests PRIVATE include)

add_test(NAME TwelveTests COMMAND tests)