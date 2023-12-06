cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(pysdsl2)

include_directories("${CMAKE_SOURCE_DIR}include/sdsl")
include_directories("${CMAKE_SOURCE_DIR}/python")

add_subdirectory(pybind11)

file (GLOB SOURCE_FILES "lib/*.cpp")
file (GLOB HEADER_FILES "include/sdsl/*.hpp")

pybind11_add_module(pysdsl2 ${SOURCE_FILES} ${HEADER_FILES}  src/lib.cpp)
target_link_libraries(pysdsl2 PUBLIC sdsl)
