#include "bit_vector.h"
#include <sdsl/bit_vector_il.hpp>
#include <sdsl/rrr_vector.hpp>
#include <sdsl/sd_vector.hpp>
#include <sdsl/hyb_vector.hpp>

template<class Class>
static void _make_binding_bitvector(py::module &m, std::string typestr);

template<class Class>
static void _make_binding_bitvector_im(py::module &m, std::string typestr);

void make_binding_bitvector(py::module &m) {
    _make_binding_bitvector<sdsl::bit_vector>         (m, "bit_vector");
    _make_binding_bitvector_im<sdsl::bit_vector_il<>> (m, "bit_vector_il");
    _make_binding_bitvector_im<sdsl::rrr_vector<>>    (m, "rrr_vector");
    _make_binding_bitvector_im<sdsl::sd_vector<>>     (m, "sd_vector");
    _make_binding_bitvector_im<sdsl::hyb_vector<>>    (m, "hyb_vector");
}

template<class Class>
static void _make_binding_bitvector(py::module &m, std::string typestr) {
    py::class_<Class>(m, typestr.c_str())

    .def(py::init<int>())

    // operator[]
    .def("__getitem__", [](const Class &a, size_t i) {
        return a[i];
    }, py::is_operator())
    .def("__setitem__", [](Class &a, size_t i, int value) {
        a[i] = value;
    }, py::is_operator())
    
    // Iterator
    .def("__iter__", [](const Class &a) {
        return py::make_iterator(a.begin(), a.end());
    })
    
    .def("size", &Class::size)
    .def("width", [](Class &a, size_t sz) {
        a.width(sz);
    });

    m.def("size_in_bytes", &sdsl::size_in_bytes<Class>);
}


template<class Class>
static void _make_binding_bitvector_im(py::module &m, std::string typestr) {
    py::class_<Class>(m, typestr.c_str())

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
