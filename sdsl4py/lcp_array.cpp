#ifndef LCP_ARRAYS_CPP
#define LCP_ARRAYS_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sdsl/lcp_bitcompressed.hpp>
#include <sdsl/lcp_dac.hpp>
#include <sdsl/lcp_wt.hpp>

namespace py = pybind11;

using sdsl::lcp_bitcompressed;
using sdsl::lcp_dac;
using sdsl::lcp_wt;

// Helper function to add LCP array classes to the Python module
template <typename T>
void add_lcp_array(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>())  // Default constructor
        .def("size_in_bytes", [](const T& lcp) { return sdsl::size_in_bytes(lcp); }, R"pbdoc(
            Returns the size of the LCP array in bytes.
        )pbdoc")
        .def("size_in_mega_bytes", [](const T& lcp) { return sdsl::size_in_mega_bytes(lcp); }, R"pbdoc(
            Returns the size of the LCP array in megabytes.
        )pbdoc")
        .def("store_to_file", [](const T& lcp, const std::string& file) { return sdsl::store_to_file(lcp, file); }, R"pbdoc(
            Stores the LCP array to a file.
        )pbdoc")
        .def("load_from_file", [](T& lcp, const std::string& file) { return sdsl::load_from_file(lcp, file); }, R"pbdoc(
            Loads the LCP array from a file.
        )pbdoc")
      .def("construct0", [](T& lcp, const std::string& file) { return
      sdsl::construct(lcp, file, 0); }, R"pbdoc(
            Construct the LCP array from a serialized input file.
        )pbdoc")
      .def("construct1", [](T& lcp, const std::string& file) { return
      sdsl::construct(lcp, file, 1); }, R"pbdoc(
            Construct the LCP array from a file with 1-byte symbols.
        )pbdoc")
        .def("get", [](const T& lcp, size_t idx) { return lcp[idx]; }, R"pbdoc(
            Returns the idx-th entry of the LCP array.
        )pbdoc")
        .def("size", &T::size, R"pbdoc(
            Returns the number of elements in the LCP array.
        )pbdoc");
}
#endif // LCP_ARRAYS_CPP

