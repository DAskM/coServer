cmake_minimum_required(VERSION 2.8)
project(conServer)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC
    src/log.cc
    src/util.cc
    src/config.cc)

add_library(conServer SHARED ${LIB_SRC})

include_directories(/usr/local/include/yaml-cpp)
link_directories(/usr/local/lib)

add_executable(test tests/test.cc)
add_dependencies(test conServer)
target_link_libraries(test conServer)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config conServer)
target_link_libraries(test_config conServer yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)