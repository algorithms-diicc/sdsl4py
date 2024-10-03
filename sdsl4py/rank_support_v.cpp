#ifndef RANK_SUPPORT_CPP
#define RANK_SUPPORT_CPP

#include <pybind11/pybind11.h>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/rank_support.hpp>

namespace py = pybind11;

// Agregar funciones de rank support
template <typename T>
void add_rank_support(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<const sdsl::bit_vector*>(), py::arg("bit_vector") = nullptr, R"pbdoc(
            Constructor for rank_support.
            Args:
                bit_vector (sdsl::bit_vector*): Pointer to the bit vector.
        )pbdoc")
        .def("rank", &T::rank, py::arg("i"), R"pbdoc(
            Returns the number of 1-bits in the bit vector up to position i (inclusive).
            Args:
                i (size_type): The index position.
            Returns:
                size_type: The number of 1-bits up to position i.
        )pbdoc")
        .def("size_in_bytes", [](const T& v) { return sdsl::size_in_bytes(v); }, R"pbdoc(
            Returns the size of the rank support structure in bytes.
        )pbdoc")
        .def("store_to_file", [](const T& v, const std::string& file) { return sdsl::store_to_file(v, file); }, R"pbdoc(
            Stores the rank support structure to a file.
        )pbdoc")
        .def("load_from_file", [](T& v, const std::string& file) { return sdsl::load_from_file(v, file); }, R"pbdoc(
            Loads the rank support structure from a file.
        )pbdoc");
}

PYBIND11_MODULE(sdsl_rank_support, m) {
    m.doc() = "Python bindings for SDSL rank supports";

    // Agregar rank supports al módulo
    add_rank_support<sdsl::rank_support_v<1>>(m, "RankSupportV1");  // Rank support para bits de valor 1
    add_rank_support<sdsl::rank_support_v<0>>(m, "RankSupportV0");  // Rank support para bits de valor 0
}

#endif // RANK_SUPPORT_CPP
