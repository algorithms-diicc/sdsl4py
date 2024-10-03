#ifndef ENC_VECTOR_CPP
#define ENC_VECTOR_CPP

#include <pybind11/pybind11.h>
#include <sdsl/vectors.hpp>
#include <sdsl/coder.hpp>

namespace py = pybind11;

using sdsl::enc_vector;
using sdsl::vlc_vector;
using sdsl::dac_vector;


template <class T>
inline auto add_compressed_vector(py::module &m, const char* name){

    m.def("size_in_bytes", &sdsl::size_in_bytes<T>, py::arg("v"), R"doc(
        Returns the size of the data structure in bytes.

        Parameters:
            v: Data structure to get the size of.

        Returns:
            The size of the data structure in bytes.)doc");
    m.def("size_in_mega_bytes", &sdsl::size_in_mega_bytes<T>, py::arg("v"), R"doc(
        Returns the size of the data structure in megabytes.

        Parameters:
            v: Data structure to get the size of.

        Returns:
            The size of the data structure in megabytes.)doc");
    m.def("store_to_file", &sdsl::store_to_file<T>, py::arg("v"), py::arg("file"), R"doc(
        Store the data structure to a file.

        Parameters:
            v: Data structure to store.
            file (str): Name of the file where to store the data structure.

        Returns:
            True if the data structure was successfully stored, otherwise False.
    )doc");
    m.def("load_from_file", &sdsl::load_from_file<T>, py::arg("v"), py::arg("file"), R"doc(
        Load the data structure from a file.

        Parameters:
            v: Data structure to load.
            file (str): Name of the file where to load the data structure from.

        Returns:
            True if the data structure was successfully loaded, otherwise False.
        )doc");


    return py::class_<T>(m, name)
    .def(py::init([](const sdsl::int_vector<0> container){
        return new T(container);
    }), py::arg("container"))
    .def(py::init([](const sdsl::int_vector<8> container){
        return new T(container);
    }), py::arg("container"))
    .def(py::init([](const sdsl::int_vector<16> container){
        return new T(container);
    }), py::arg("container"))
    .def(py::init([](const sdsl::int_vector<32> container){
        return new T(container);
    }), py::arg("container"))
    .def(py::init([](const sdsl::int_vector<64> container){
        return new T(container);
    }), py::arg("container"))
    .def(py::init<>())
    .def("__getitem__", [](const T v, int index){
        return v[index];
    })
    .def("size", &T::size)
    .def("__len__", &T::size)
    .def("max_size", &T::max_size)
    .def("empty", &T::empty)
    .def("__bool__", [](const T &self){
        return !self.empty();
    })
    //TODO: swap method
    //TODO: serialiize
    //TODO: sample
    //TODO: get_inter_sampled_values
    .def("__iter__", [](const py::sequence &self){
            return py::make_iterator(self.begin(), self.end());
        },
    py::keep_alive<0, 1>(), py::is_operator());
}

template <class T>
inline auto add_enc_vlc_vector(py::module &m, const char* name){
    add_compressed_vector<T>(m, name).def("get_sample_dens", &T::get_sample_dens);
}

void enc_vector_wrapper(py::module &m){
    //TODO: Support variable density
    add_enc_vlc_vector<enc_vector<sdsl::coder::elias_delta, 128, 0>>(m, "enc_vector_elias_delta");
    add_enc_vlc_vector<enc_vector<sdsl::coder::elias_gamma, 128, 0>>(m, "enc_vector_elias_gamma");
    add_enc_vlc_vector<enc_vector<sdsl::coder::fibonacci, 128, 0>>(m, "enc_vector_fibonacci");
    add_enc_vlc_vector<enc_vector<sdsl::coder::comma<2>, 128, 0>>(m, "enc_vector_comma_2");

    add_enc_vlc_vector<vlc_vector<sdsl::coder::elias_delta, 128, 0>>(m, "vlc_vector_elias_delta");
    add_enc_vlc_vector<vlc_vector<sdsl::coder::elias_gamma, 128, 0>>(m, "vlc_vector_elias_gamma");
    add_enc_vlc_vector<vlc_vector<sdsl::coder::fibonacci, 128, 0>>(m, "vlc_vector_fibonacci");
    add_enc_vlc_vector<vlc_vector<sdsl::coder::comma<2>, 128, 0>>(m, "vlc_vector_comma_2");

    add_compressed_vector<dac_vector<>>(m, "dac_vector");
}


#endif //ENC_VECTOR_CPP
