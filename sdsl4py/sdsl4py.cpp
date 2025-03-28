#include <pybind11/pybind11.h>

#include <sdsl/int_vector.hpp>
#include <sdsl/enc_vector.hpp>
#include <sdsl/wavelet_trees.hpp>
#include <sdsl/vectors.hpp>
#include <sdsl/rank_support.hpp>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/select_support.hpp>
#include <pybind11/stl.h>
#include <sdsl/lcp_bitcompressed.hpp>
#include <sdsl/lcp_dac.hpp>
#include <sdsl/lcp_wt.hpp>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/bp_support.hpp>
#include <sdsl/bp_support_sada.hpp>
#include <sdsl/bp_support_g.hpp>
#include <sdsl/bp_support_gg.hpp>
#include "sdsl/util.hpp"
#include "int_vector.cpp"
#include "compressed_int_vector.cpp"
#include "wavelet_trees.cpp"
#include "rank_support_v.cpp"
#include "select_support_mcl.cpp"
#include "lcp_array.cpp"
#include "suffix_array.cpp"
#include "balanced_parenthesis_support.cpp"



namespace py = pybind11;

PYBIND11_MODULE(sdsl4py, m){
    m.doc() = "Python bindings for sdsl";

    int_vector_wrapper(m);
    enc_vector_wrapper(m);
    // Add wavelet trees to the Python module
    add_wavelet_tree2D<wt_int<>>(m, "WaveletTreeInt");// Note: add_wavelet_tree2D only works for wt_int
    add_wavelet_tree<wt_huff<>>(m, "WaveletTreeHuff");
    add_wavelet_tree<wt_huff_int<>>(m, "WaveletTreeHuffInt");
    add_wavelet_tree<wt_gmr<>>(m, "WaveletTreeGMR");

    // Add rank support to the Python module
    add_rank_support<sdsl::rank_support_v<1>>(m, "RankSupportV1");  // Rank support para bits de valor 1
    add_rank_support<sdsl::rank_support_v<0>>(m, "RankSupportV0");  // Rank support para bits de valor 0

    // Add select support to the Python module
    add_select_support<sdsl::select_support_mcl<1>>(m, "SelectSupportMCL1");  // Select support para bits de valor 1
    add_select_support<sdsl::select_support_mcl<0>>(m, "SelectSupportMCL0");  // Select support para bits de valor 0

    // Add the compressed suffix array to the Python module
    add_suffix_array<sdsl::csa_wt<>>(m, "SuffixArrayWT");
    add_suffix_array<sdsl::csa_sada<>>(m, "SuffixArraySada");

    // Add the longest common prefix array to the Python module
    add_lcp_array<sdsl::lcp_wt<>>(m, "LCPArrayWT");
    add_lcp_array<sdsl::lcp_bitcompressed<>>(m, "LcpBitCompressed");

    //Add balanced parentheses support to the Python module
    add_bp_support<sdsl::bp_support_sada<>>(m, "BPSupportSada");
    add_bp_support<sdsl::bp_support_g<>>(m, "BPSupportG");
    add_bp_support<sdsl::bp_support_gg<>>(m, "BPSupportGG");
   
    m.attr("__version__") = "1.0";
}
