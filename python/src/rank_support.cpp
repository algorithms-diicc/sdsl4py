#include "rank_support.h"

template<class Class>
void _make_binding_rank_support(py::module &m, std::string typestr) {
    std::string class_name = std::string("rank_support_") + typestr;
    py::class_<Class>(m, class_name.c_str())
    
    .def(py::init<sdsl::bit_vector>())
    
    .def("rank", &Class::rank)
    .def("__call__", &Class::operator());
}

void make_binding_rank_support(py::module &m) {
    // TODO
}
