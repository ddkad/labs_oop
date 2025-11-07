cmake_minimum_required(VERSION 3.14)
project(GeometryFigures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
)

set(HEADERS
    include/array.h
    include/figure.h
    include/point.h
    include/triangle.h
    include/hexagon.h
    include/octagon.h
)

# ОСНОВНАЯ ПРОГРАММА
add_executable(lab_4 ${SOURCES} ${HEADERS})
target_include_directories(lab_4 PRIVATE include src)

# ТЕСТЫ ВСЕГДА ВКЛЮЧЕНЫ (убрали условие)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(geometry_tests 
    test/array_test.cpp
    test/point_test.cpp
    test/triangle_test.cpp
    test/hexagon_test.cpp
    test/octagon_test.cpp
    test/figure_test.cpp
)

target_link_libraries(geometry_tests PRIVATE gtest_main)
target_include_directories(geometry_tests PRIVATE include src)

add_test(NAME GeometryTests COMMAND geometry_tests)