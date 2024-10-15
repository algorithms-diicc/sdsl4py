#ifndef INT_VECTOR_CPP
#define INT_VECTOR_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/iostream.h>
#include <sdsl/int_vector.hpp>

namespace py = pybind11;

using sdsl::int_vector;

template <class T>
inline auto add_int_vector(py::module &m, const char* name){

    // Utility functions for size
    m.def("size_in_bytes", &sdsl::size_in_bytes<T>, py::arg("v"));
    m.def("size_in_mega_bytes", &sdsl::size_in_mega_bytes<T>, py::arg("v"));
    m.def("store_to_file", &sdsl::store_to_file<T>, py::arg("v"), py::arg("file"));
    m.def("load_from_file", &sdsl::load_from_file<T>, py::arg("v"), py::arg("file"));

    return py::class_<T>(m, name, py::buffer_protocol())
        // Constructor que acepta el tamaño, valor por defecto y ancho de entero
        .def(py::init([](uint64_t size, uint64_t default_value, uint8_t int_width){
            return new T(size, default_value, int_width);
        }), py::arg("size") = 1, py::arg("default_value") = 0, py::arg("int_width") = 64)

        // Nuevo constructor que acepta una colección de Python
        .def(py::init([](const std::vector<uint64_t>& data){
            T v(data.size());
            for(size_t i = 0; i < data.size(); ++i) {
                v[i] = data[i];
            }
            return v;
        }), R"doc(
            Constructor para int_vector que acepta una lista de Python.

            Parameters:
                data (list): Una lista de enteros para inicializar el int_vector.
        )doc", py::arg("data"))

        .def("__bool__", [](T &self){
            return !self.empty();
        })
        .def("empty", &T::empty)
        .def("swap", &T::swap, py::arg("v"))
        .def("resize", &T::resize, py::arg("size"))
        .def("bit_resize", &T::bit_resize, py::arg("size"))
        .def("size", &T::size)
        .def("__len__", &T::size)
        .def("max_size", &T::max_size)
        .def("bit_size", &T::bit_size)
        .def("capacity", &T::capacity)

        .def("get_int", &T::get_int, py::arg("idx"), py::arg("len") = 64)
        .def("set_int", &T::set_int, py::arg("idx"), py::arg("x"), py::arg("len") = 64)
        .def("width", py::overload_cast<>(&T::width, py::const_))
        .def("width", py::overload_cast<uint8_t>(&T::width), py::arg("new_width"))

        .def("__getitem__", [](const T &self, size_t index) {
            if (index >= self.size()) {
                throw py::index_error("Index out of bounds");
            }
            return self[index];
        })
        .def("__setitem__", [](T &self, size_t index, size_t value){
            if(index >= self.size()){
                throw py::index_error("Index out of bounds");
            }
            self[index] = value;
        })

        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)
        .def(py::self &= py::self)
        .def(py::self |= py::self)
        .def(py::self ^= py::self)

        .def("__iter__", [](const py::sequence &self){
            return py::make_iterator(self.begin(), self.end());
        },
        py::keep_alive<0, 1>(), py::is_operator())
        
        .def("__str__", [](T& self){
            return sdsl::util::to_string(self);
        });
}

void int_vector_wrapper(py::module &m){
    // int_vector with runtime width
    add_int_vector<int_vector<0>>(m, "int_vector");

    // int_vector with fixed width
    add_int_vector<int_vector<8>>(m, "int_vector_8");
    add_int_vector<int_vector<16>>(m, "int_vector_16");
    add_int_vector<int_vector<32>>(m, "int_vector_32");
    add_int_vector<int_vector<64>>(m, "int_vector_64");

    // bit_vector
    add_int_vector<int_vector<1>>(m, "bit_vector").def("flip", &int_vector<1>::flip);
}

#endif //INT_VECTOR_CPP
