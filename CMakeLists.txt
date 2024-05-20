cmake_minimum_required(VERSION 2.8)
project(conServer)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(./src)
link_directories(/src/lib)

find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    src/log.cc
    src/util.cc
    src/config.cc
    src/thread.cc
    src/mutex.cc)

add_library(conServer SHARED ${LIB_SRC})

set(LIB_LIB
    conServer
    pthread
    ${YAMLCPP})

add_executable(test tests/test.cc)
add_dependencies(test conServer)
target_link_libraries(test ${LIB_LIB})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config conServer)
target_link_libraries(test_config ${LIB_LIB})

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread conServer)
target_link_libraries(test_thread ${LIB_LIB})

add_executable(test_assert tests/test_assert.cc)
add_dependencies(test_assert conServer)
target_link_libraries(test_assert ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)