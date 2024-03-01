#pragma once

#include <pybind11/pybind11.h>
#include <sdsl/enc_vector.hpp>
#include <sdsl/vlc_vector.hpp>
#include <sdsl/dac_vector.hpp>

namespace py = pybind11;

void make_binding_encvector(py::module &m);
void make_binding_vlcvector(py::module &m);
void make_binding_dacvector(py::module &m);
