cmake_minimum_required(VERSION 3.14)
project(GeometryFigures)

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

add_library(geometry_lib 
    src/figures.cpp
    src/point.cpp
    src/rectangle.cpp
    src/square.cpp
    src/trapezoid.cpp
    src/vector_figures.cpp
    src/vector_points.cpp   
)
target_include_directories(geometry_lib PUBLIC include)

add_executable(geometry_figures src/main.cpp)
target_link_libraries(geometry_figures PRIVATE geometry_lib)

enable_testing()
add_executable(tests 
    test/test_main.cpp
    test/test_point.cpp
    test/test_figures.cpp
    test/test_vector.cpp
)
target_link_libraries(tests PRIVATE geometry_lib gtest_main)
target_include_directories(tests PRIVATE include)

add_test(NAME GeometryTests COMMAND tests)