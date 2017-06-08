cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME_STR algorithm-club)
project(${PROJECT_NAME_STR} C CXX)
set(CMAKE_CXX_STANDARD 11)

include(CMakeToolsHelpers OPTIONAL)

find_package(Threads REQUIRED)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src/include)
set(EXT_PROJECT_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${EXT_PROJECT_DIR}/gtest)

#-------------------
# Test
#-------------------
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS}/googletest/include ${GTEST_INCLUDE_DIRS}/googlemock/include ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT} gtest gtest_main gmock gmock_main)

add_test(test1 ${PROJECT_TEST_NAME})
