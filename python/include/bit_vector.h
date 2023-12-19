#pragma once

#include <pybind11/pybind11.h>
#include <sdsl/int_vector.hpp>

namespace py = pybind11;

void make_binding_bitvector(py::module &m);
