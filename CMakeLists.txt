cmake_minimum_required(VERSION 3.20)
project(stl_homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 用当前编译器从源码构建固定版本的 GoogleTest，避免混用 MSVC/MinGW 二进制库。
include(FetchContent)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(homework
    src/exercise02_numbers.cpp
    src/exercise03_brackets.cpp
    src/exercise04_words.cpp
    src/exercise05_tasks.cpp
)
target_include_directories(homework PUBLIC include)

add_executable(homework_tests
    tests/exercise01_templates_test.cpp
    tests/exercise02_numbers_test.cpp
    tests/exercise03_brackets_test.cpp
    tests/exercise04_words_test.cpp
    tests/exercise05_tasks_test.cpp
)
target_link_libraries(homework_tests PRIVATE homework GTest::gtest_main)

if(MSVC)
    target_compile_options(homework PRIVATE /utf-8 /W4)
    target_compile_options(homework_tests PRIVATE /utf-8 /W4)
else()
    # TODO 阶段存在未使用参数是正常的，因此不启用 -Werror。
    target_compile_options(homework PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(homework_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
include(GoogleTest)
gtest_discover_tests(homework_tests)

