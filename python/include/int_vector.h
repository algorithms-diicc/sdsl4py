#pragma once

#include <pybind11/pybind11.h>
#include <sdsl/int_vector.hpp>

namespace py = pybind11;

/*
 * Makes binding for intvector's template
 * T is the compile-time size. 0 uses runtime-selected size.
 * typestr must be set to "T", or "" for T = 0
 */

void make_binding_intvector(py::module &m);

