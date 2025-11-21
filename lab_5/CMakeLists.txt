cmake_minimum_required(VERSION 3.14)
project(lab_5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
elseif(MSVC)
    add_compile_options(/W4)
endif()

# Загрузка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная библиотека memory_resource
add_library(memory_resource src/dynamic_memory_resource.cpp)
target_include_directories(memory_resource PUBLIC include)

# Основная демонстрационная программа
add_executable(lab_5_main src/main.cpp)
target_link_libraries(lab_5_main PRIVATE memory_resource)
target_include_directories(lab_5_main PRIVATE include)

# Включение системы тестирования
enable_testing()

# Тесты для memory resource
add_executable(test_memory_resource test/test_memory_resource.cpp)
target_link_libraries(test_memory_resource PRIVATE memory_resource gtest_main)
target_include_directories(test_memory_resource PRIVATE include)

# Тесты для queue
add_executable(test_queue test/test_queue.cpp)
target_link_libraries(test_queue PRIVATE gtest_main)
target_include_directories(test_queue PRIVATE include)

# Интеграционные тесты
add_executable(test_integration test/test_integration.cpp)
target_link_libraries(test_integration PRIVATE memory_resource gtest_main)
target_include_directories(test_integration PRIVATE include)

# Добавление тестов в CTest
include(GoogleTest)
gtest_discover_tests(test_memory_resource)
gtest_discover_tests(test_queue)
gtest_discover_tests(test_integration)