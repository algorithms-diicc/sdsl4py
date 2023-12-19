#include "enc_vector.h"

template<class Coder>
static void _make_binding_encvector(py::module &m, std::string typestr);

void make_binding_encvector(py::module &m) {
    _make_binding_encvector<sdsl::coder::elias_delta>(m, "ed");
    _make_binding_encvector<sdsl::coder::elias_gamma>(m, "eg");
    _make_binding_encvector<sdsl::coder::fibonacci>(m, "fib");
}

template<class Coder>
static void _make_binding_encvector(py::module &m, std::string typestr) {
    using Class = sdsl::enc_vector<Coder>;
    std::string class_name = std::string("enc_vector_") + typestr;
    py::class_<Class>(m, class_name.c_str())
    
    .def(py::init([](sdsl::int_vector<0> &v) {
        return Class(v);
    }))
    .def(py::init())

    // operator[]
    .def("__getitem__", [](const Class &a, size_t i) {
        return a[i];
    }, py::is_operator())

    
    // Iterator
    .def("__iter__", [](const Class &a) {
        return py::make_iterator(a.begin(), a.end());
    })
    
    .def("size", &Class::size);

    m.def("size_in_bytes", &sdsl::size_in_bytes<Class>);
}
