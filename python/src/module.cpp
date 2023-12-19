#include <pybind11/pybind11.h>

#include "int_vector.h"
#include "bit_vector.h"
#include "enc_vector.h"

namespace py = pybind11;

PYBIND11_MODULE(pysdsl2, m) {
    m.doc() = R"pbdoc(
        libsdsl pybind11 based bindings
    )pbdoc";
    
    make_binding_intvector(m);
    make_binding_bitvector(m);
    
    make_binding_encvector(m);
}
