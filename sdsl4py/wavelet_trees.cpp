#ifndef WAVELET_TREES_CPP
#define WAVELET_TREES_CPP

#include <pybind11/pybind11.h>
#include <sdsl/wavelet_trees.hpp>
#include <sdsl/vectors.hpp>

namespace py = pybind11;

// Tipos de Wavelet Trees en SDSL
using sdsl::wt_int;
using sdsl::wt_huff;
using sdsl::wt_huff_int;
using sdsl::wt_gmr;

// Función auxiliar para añadir wavelet trees a un módulo Python
template <typename T>
void add_wavelet_tree(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>(), R"pbdoc(
            Default constructor for wavelet tree.
        )pbdoc")
        .def("access", [](const T& wt, size_t idx) { return wt[idx]; }, py::arg("idx"), R"pbdoc(
            Accesses the element at the given position.
            Args:
                idx (size_t): Index of the element to access.
            Returns:
                The value at the given index.
        )pbdoc")
        .def("rank", [](const T& wt, size_t idx, int symbol) { return wt.rank(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the number of occurrences of a symbol up to the given index.
            Args:
                idx (size_t): Index up to which the symbol count is calculated.
                symbol (int): Symbol for which to calculate the rank.
            Returns:
                Number of occurrences of the symbol.
        )pbdoc")
        .def("select", [](const T& wt, size_t idx, int symbol) { return wt.select(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the position of the i-th occurrence of the symbol.
            Args:
                idx (size_t): The index of the occurrence.
                symbol (int): Symbol for which to calculate the select.
            Returns:
                The position of the occurrence.
        )pbdoc")
        .def("size_in_bytes", [](const T& wt) { return sdsl::size_in_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in bytes.
        )pbdoc")
        .def("size_in_mega_bytes", [](const T& wt) { return sdsl::size_in_mega_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in megabytes.
        )pbdoc")
        .def("store_to_file", [](const T& wt, const std::string& file) { return sdsl::store_to_file(wt, file); }, py::arg("file"), R"pbdoc(
            Stores the wavelet tree to a file.
            Args:
                file (str): The name of the file to store the tree.
        )pbdoc")
        .def("load_from_file", [](T& wt, const std::string& file) { return sdsl::load_from_file(wt, file); }, py::arg("file"), R"pbdoc(
            Loads the wavelet tree from a file.
            Args:
                file (str): The name of the file to load the tree from.
        )pbdoc");
}

// Definición del módulo Pybind11 para wavelet trees
PYBIND11_MODULE(sdsl_wavelet, m) {
    m.doc() = "Python bindings for SDSL Wavelet Trees";

    // Agregar wavelet trees al módulo
    add_wavelet_tree<wt_int<>>(m, "WaveletTreeInt");
    add_wavelet_tree<wt_huff<>>(m, "WaveletTreeHuff");
    add_wavelet_tree<wt_huff_int<>>(m, "WaveletTreeHuffInt");
    add_wavelet_tree<wt_gmr<>>(m, "WaveletTreeGMR");
}

#endif // WAVELET_TREES_CPP
