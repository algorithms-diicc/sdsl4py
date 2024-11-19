#ifndef BPS_CPP
#define BPS_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "sdsl/bp_support.hpp"  // Ajusta esta ruta según tu estructura de proyecto
#include "sdsl/bit_vectors.hpp"
#include "sdsl/util.hpp"

namespace py = pybind11;
using namespace sdsl;

// Definir wrapper para la clase bp_support_g
template <typename T>
void add_bp_support(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>())  // Constructor
        .def("find_open", &T::find_open)
        .def("find_close", &T::find_close)
        .def("enclose", &T::enclose)
        .def("double_enclose", &T::double_enclose)
        .def("excess", &T::excess)
        .def("rr_enclose", &T::rr_enclose)
        .def("rank", &T::rank)
        .def("select", &T::select)
        .def("initialize", [](T &self, bit_vector &bv) {
            util::init_support(self, &bv);
        }, py::arg("bv"));
}

#endif