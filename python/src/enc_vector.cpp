#include "enc_vector.h"

template<class Coder>
static void _make_binding_encvector(py::module &m, std::string typestr);


void make_binding_encvector(py::module &m) {
    _make_binding_encvector<sdsl::enc_vector<sdsl::coder::elias_delta>> (m, "enc_vector_ed");
    _make_binding_encvector<sdsl::enc_vector<sdsl::coder::elias_gamma>> (m, "enc_vector_eg");
    _make_binding_encvector<sdsl::enc_vector<sdsl::coder::fibonacci>> (m, "enc_vector_fib");
}

void make_binding_vlcvector(py::module &m) {
    _make_binding_encvector<sdsl::vlc_vector<sdsl::coder::fibonacci>> (m, "vlc_vector_fib");
    _make_binding_encvector<sdsl::vlc_vector<sdsl::coder::elias_gamma>> (m, "vlc_vector_eg");
    _make_binding_encvector<sdsl::vlc_vector<sdsl::coder::elias_delta>> (m, "vlc_vector_ed");
}

void make_binding_dacvector(py::module &m) {
    //_make_binding_encvector<sdsl::dac_vector> (m, "dac_vector");
}



template<class Class>
static void _make_binding_encvector(py::module &m, std::string typestr) {
    py::class_<Class>(m, typestr.c_str())
    
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
