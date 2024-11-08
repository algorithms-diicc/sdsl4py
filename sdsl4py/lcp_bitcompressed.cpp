#ifndef LCP_BITCOMPRESSED_CPP
#define LCP_BITCOMPRESSED_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sdsl/lcp_bitcompressed.hpp>

namespace py = pybind11;
using sdsl::lcp_bitcompressed;

template <class T>
inline auto add_lcp_bitcompressed(py::module &m, const char* name){

    // Funciones utilitarias para tamaño y almacenamiento
    m.def("size_in_bytes", &sdsl::size_in_bytes<T>, py::arg("v"));
    m.def("size_in_mega_bytes", &sdsl::size_in_mega_bytes<T>, py::arg("v"));
    m.def("store_to_file", &sdsl::store_to_file<T>, py::arg("v"), py::arg("file"));
    m.def("load_from_file", &sdsl::load_from_file<T>, py::arg("v"), py::arg("file"));

    return py::class_<T>(m, name)
        // Constructor por defecto
        .def(py::init<>(), R"doc(
            Default constructor for lcp_bitcompressed.
        )doc")

        // Constructor que acepta una colección de Python para inicializar lcp_bitcompressed
        .def(py::init([](const std::vector<uint64_t>& data){
            T v(data.size());
            for(size_t i = 0; i < data.size(); ++i) {
                v[i] = data[i];
            }
            return v;
        }), R"doc(
            Constructor para lcp_bitcompressed que acepta una lista de Python.

            Parameters:
                data (list): Una lista de enteros para inicializar el lcp_bitcompressed.
        )doc", py::arg("data"))

        .def("empty", &T::empty, "True if lcp_bitcompressed is empty.")
        .def("size", &T::size, R"doc(
            Retorna el tamaño de lcp_bitcompressed.

            Returns:
                int: El número de elementos en el arreglo lcp_bitcompressed.
        )doc")
        .def("__len__", &T::size)

        .def("max_size", &T::max_size, R"doc(
            Retorna el tamaño máximo de lcp_bitcompressed.

            Returns:
                int: El tamaño máximo de lcp_bitcompressed.
        )doc")
        .def("bit_size", &T::bit_size, R"doc(
            Número total de bits en el arreglo lcp_bitcompressed.
        )doc")
        
        .def("__getitem__", [](const T &self, size_t index) {
            if (index >= self.size()) {
                throw py::index_error("Index out of bounds");
            }
            return self[index];
        }, py::is_operator())

        .def("__setitem__", [](T &self, size_t index, uint64_t value){
            if(index >= self.size()){
                throw py::index_error("Index out of bounds");
            }
            self[index] = value;
        }, py::is_operator())

        .def(py::self == py::self, R"doc(
            Equality operator for two lcp_bitcompressed arrays.
        )doc")
        .def(py::self != py::self)
        
        .def("__str__", [](T& self){
            std::stringstream ss;
            ss << "lcp_bitcompressed with " << self.size() << " elements.";
            return ss.str();
        });
}

void lcp_bitcompressed_wrapper(py::module &m) {
    add_lcp_bitcompressed<lcp_bitcompressed<>>(m, "lcp_bitcompressed");
}

#endif // LCP_BITCOMPRESSED_CPP
