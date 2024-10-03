#include <pybind11/pybind11.h>

#include <sdsl/int_vector.hpp>
#include <sdsl/enc_vector.hpp>

#include "int_vector.cpp"
#include "compressed_int_vector.cpp"

namespace py = pybind11;

PYBIND11_MODULE(sdsl4py, m){
    m.doc() = "Python bindings for sdsl";

    int_vector_wrapper(m);
    enc_vector_wrapper(m);

    m.attr("__version__") = "0.0.1";
}