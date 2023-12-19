#include "int_vector.h"

template<char T>
static void _make_binding_intvector(py::module &m, std::string typestr);

void make_binding_intvector(py::module &m) {
    _make_binding_intvector<0>(m, std::string(""));
    _make_binding_intvector<2>(m, std::string("2"));
    _make_binding_intvector<4>(m, std::string("4"));
    _make_binding_intvector<8>(m, std::string("8"));
    _make_binding_intvector<16>(m, std::string("16"));
    _make_binding_intvector<32>(m, std::string("32"));
    _make_binding_intvector<64>(m, std::string("64"));
}

template<char T>
static void _make_binding_intvector(py::module &m, std::string typestr) {
    using Class = sdsl::int_vector<T>;
    std::string class_name = std::string("int_vector") + typestr;
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
    m.def("bit_compress", &sdsl::util::bit_compress<Class>);
}
