#include <pybind11/pybind11.h>
#include <sdsl/int_vector.hpp>

namespace py = pybind11;

template<char T>
void make_binding_intvector(py::module &m, std::string typestr) {
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
}

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

PYBIND11_MODULE(pysdsl2, m) {
    m.doc() = R"pbdoc(
        libsdsl pybind11 based bindings
    )pbdoc";
    
    make_binding_intvector<0>(m, std::string(""));
    make_binding_intvector<1>(m, std::string("1"));
    make_binding_intvector<2>(m, std::string("2"));
    make_binding_intvector<4>(m, std::string("4"));
    make_binding_intvector<8>(m, std::string("8"));
    make_binding_intvector<16>(m, std::string("16"));
    make_binding_intvector<32>(m, std::string("32"));
    make_binding_intvector<64>(m, std::string("64"));
    
    //make_binding_bitvector(m);
}
