#ifndef SELECT_SUPPORT_CPP
#define SELECT_SUPPORT_CPP

#include <pybind11/pybind11.h>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/select_support.hpp>

namespace py = pybind11;

// Helper function to add (bit) select classes to the Python module
template <typename T>
void add_select_support(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<const sdsl::bit_vector*>(), py::arg("bit_vector") = nullptr, R"pbdoc(
            Constructor for select_support.
            Args:
                bit_vector (sdsl::bit_vector*): Pointer to the bit vector.
        )pbdoc")
        .def("select", &T::select, py::arg("i"), R"pbdoc(
            Returns the position of the i-th 1-bit (or 0-bit depending on the type).
            Args:
                i (size_type): The index of the 1-bit (or 0-bit) to find.
            Returns:
                size_type: The position of the i-th 1-bit (or 0-bit).
        )pbdoc")
        .def("size_in_bytes", [](const T& v) { return sdsl::size_in_bytes(v); }, R"pbdoc(
            Returns the size of the select support structure in bytes.
        )pbdoc")
        .def("store_to_file", [](const T& v, const std::string& file) { return sdsl::store_to_file(v, file); }, R"pbdoc(
            Stores the select support structure to a file.
        )pbdoc")
        .def("load_from_file", [](T& v, const std::string& file) { return sdsl::load_from_file(v, file); }, R"pbdoc(
            Loads the select support structure from a file.
        )pbdoc");
}


#endif // SELECT_SUPPORT_CPP
