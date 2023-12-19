#include "bit_vector.h"

void make_binding_bitvector(py::module &m) {
    using Class = sdsl::bit_vector;
    std::string class_name = std::string("bit_vector");
    py::class_<Class>(m, class_name.c_str())

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
