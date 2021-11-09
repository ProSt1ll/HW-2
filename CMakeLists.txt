cmake_minimum_required(VERSION 3.20)
project(HW_2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic  --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic --coverage")

set(SOURCES_FOR_STATIC libs/find_words/src/find_words.c)
set(SOURCES_FOR_SHARED libs/find_words_forked/src/find_words_forked.c)

add_library(find_words_forked SHARED ${SOURCES_FOR_SHARED})
target_include_directories(find_words_forked PUBLIC libs/find_words_forked/include)

add_library(find_words STATIC ${SOURCES_FOR_STATIC})
target_include_directories(find_words PUBLIC libs/find_words/include)

find_package(GTest REQUIRED)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests GTest::gtest find_words)

add_executable(tests_forked tests/tests_forked.cpp)
target_link_libraries(tests_forked GTest::gtest find_words_forked)

add_executable(stress_test tests/stress_test.cpp)
target_link_libraries(stress_test GTest::gtest find_words)

add_executable(stress_test_forked tests/stress_test_forked.cpp)
target_link_libraries(stress_test_forked GTest::gtest find_words_forked)