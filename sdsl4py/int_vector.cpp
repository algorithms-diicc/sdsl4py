#ifndef INT_VECTOR_CPP
#define INT_VECTOR_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Para manejar colecciones estándar de Python
#include <sdsl/int_vector.hpp>
#include <vector>

namespace py = pybind11;

// Helper function to add int_vector class to the Python module
void add_int_vector(py::module &m) {
    py::class_<sdsl::int_vector<>>(m, "IntVector")
        .def(py::init<>(), R"pbdoc(
            Default constructor for an empty int_vector.
        )pbdoc")
        .def(py::init<size_t>(), py::arg("size"), R"pbdoc(
            Constructor that initializes an int_vector with a given size.
            Args:
                size (size_t): Number of elements in the int_vector.
        )pbdoc")
        .def(py::init([](const std::vector<uint64_t> &v) {
            // Constructor that accepts a std::vector and converts it into an int_vector
            sdsl::int_vector<> iv(v.size());
            for (size_t i = 0; i < v.size(); ++i) {
                iv[i] = v[i];
            }
            return iv;
        }), py::arg("data"), R"pbdoc(
            Constructor that initializes an int_vector from a Python list or iterable.
            Args:
                data (List[int]): A list of integers to initialize the int_vector.
        )pbdoc")
        .def("__len__", [](const sdsl::int_vector<> &v) {
            return v.size();
        }, R"pbdoc(
            Returns the size of the int_vector.
        )pbdoc")
        .def("__getitem__", [](const sdsl::int_vector<> &v, size_t idx) {
            return v[idx];
        }, py::arg("idx"), R"pbdoc(
            Accesses the element at the given index.
            Args:
                idx (size_t): Index of the element to access.
            Returns:
                The value at the given index.
        )pbdoc")
        .def("__setitem__", [](sdsl::int_vector<> &v, size_t idx, uint64_t value) {
            v[idx] = value;
        }, py::arg("idx"), py::arg("value"), R"pbdoc(
            Sets the element at the given index to a new value.
            Args:
                idx (size_t): Index of the element to set.
                value (int): New value to set.
        )pbdoc")
        .def("size_in_bytes", [](const sdsl::int_vector<> &v) {
            return sdsl::size_in_bytes(v);
        }, R"pbdoc(
            Returns the size of the int_vector in bytes.
        )pbdoc");
}

// Pybind11 module definition for int_vector
PYBIND11_MODULE(sdsl4py, m) {
    m.doc() = "Python bindings for SDSL IntVector";

    // Add int_vector to the module
    add_int_vector(m);
}

#endif // INT_VECTOR_CPP
