cmake_minimum_required(VERSION 3.15)
project(sdsl4py)

add_compile_options(-O3 -DNDEBUG -fPIC)

add_subdirectory(sdsl-lite)
add_subdirectory(pybind11)

pybind11_add_module(sdsl4py sdsl4py/sdsl4py.cpp)
target_include_directories(sdsl4py PRIVATE sdsl-lite/include)
target_link_libraries(sdsl4py PRIVATE sdsl)
target_link_libraries(sdsl4py PRIVATE divsufsort)
target_link_libraries(sdsl4py PRIVATE divsufsort64)
