#ifndef SUFFIX_ARRAY_LCP_WRAPPER_CPP
#define SUFFIX_ARRAY_LCP_WRAPPER_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sdsl/vectors.hpp>
#include <string>

namespace py = pybind11;

// Función para agregar el Suffix Array
template <typename T>
void add_suffix_array(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>())  // Constructor por defecto
        .def("size_in_bytes", [](const T& sa) { return sdsl::size_in_bytes(sa); }, R"pbdoc(
            Returns the size of the suffix array in bytes.
        )pbdoc")
        .def("size_in_mega_bytes", [](const T& sa) { return sdsl::size_in_mega_bytes(sa); }, R"pbdoc(
            Returns the size of the suffix array in megabytes.
        )pbdoc")
        .def("store_to_file", [](const T& sa, const std::string& file) { return sdsl::store_to_file(sa, file); }, R"pbdoc(
            Stores the suffix array to a file.
        )pbdoc")
        .def("load_from_file", [](T& sa, const std::string& file) { return sdsl::load_from_file(sa, file); }, R"pbdoc(
            Loads the suffix array from a file.
        )pbdoc")
      .def("construct0", [](T& sa, const std::string& file) { return
      sdsl::construct(sa, file, 0); }, R"pbdoc(
            Construct the SA array from a serialized input file.
        )pbdoc")
      .def("construct1", [](T& sa, const std::string& file) { return
      sdsl::construct(sa, file, 1); }, R"pbdoc(
            Construct the SA array from a file with 1-byte symbols.
        )pbdoc")
        .def("get", [](const T& sa, size_t idx) { return sa[idx]; }, R"pbdoc(
            Returns the idx-th entry of the suffix array.
        )pbdoc")
        .def("size", &T::size, R"pbdoc(
            Returns the number of elements in the suffix array.
        )pbdoc");
}



#endif // SUFFIX_ARRAY_LCP_WRAPPER_CPP
