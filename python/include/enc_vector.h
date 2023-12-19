#pragma once

#include <pybind11/pybind11.h>
#include <sdsl/enc_vector.hpp>

namespace py = pybind11;

void make_binding_encvector(py::module &m);
