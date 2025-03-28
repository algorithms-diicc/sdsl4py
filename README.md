# SDSL4py: Python Bindings for SDSL
This repository is a Python library that provides bindings for the *Succinct Data Structure Library - [SDSL][SDSL]*, called `sdsl4py`. This project aims to provide an alternative to the project [pysdsl][pysdsl], a Python wrapper for the SDSL library, which is currently not receiving support.

## Installation         
We recommend to use a fresh Python environment to install sdsl4py:

1. Clone the repository
    ```sh
    git clone https://github.com/algorithms-diicc/sdsl4py.git --recursive
    cd sdsl4py
    ```
2. Install dependencies
    ```sh
    apt-get install libdivsufsort-dev
    ```
3. Install the Python environment
    ```sh
    python3 -m venv sdsl4py-env # Create the Python environment
    source sdsl4py-env/bin/activate # Active the Python environment
    pip install .
    ```


## First example
Here we have a example of the `int_vector`, `enc_vector`, `vlc_vector` and `dac_vector` classes. 

```python
import sdsl4py

v = sdsl4py.int_vector(size=100, default_value=0, int_width=8)
for i in range(100):
    v[i] = i

ev = sdsl4py.enc_vector_elias_delta(v)
vv = sdsl4py.vlc_vector_elias_delta(v)
dv = sdsl4py.dac_vector(v)

print(sdsl4py.size_in_bytes(v), "bytes")  # 113 bytes
print(sdsl4py.size_in_bytes(ev), "bytes") # 50 bytes
print(sdsl4py.size_in_bytes(vv), "bytes") # 161 bytes
print(sdsl4py.size_in_bytes(dv), "bytes") # 193 bytes
```

Data structures can be stored and loaded to/from using `store_to_file` and `load_from_file` functionalities
```python
sdsl4py.store_to_file(ev, "ev")

ev2 = sdsl4py.enc_vector_elias_delta()
sdsl4py.load_from_file(ev2, "ev")
```

## Combining sdsl4py with numpy/matplotlib
`sdsl4py` can be combined with well-known Python libraries as numpy and matplotlib

```python
import sdsl4py
import numpy as np # Probably you need to run 'pip install numpy'
import matplotlib.pyplot as plt # Probably you need to run 'pip install matplotlib'

# Create a random integer vector for testing
np_v = np.random.randint(low=10, high=100, size=512)
# Create the corresponding int_vector
v1 = sdsl4py.int_vector(np_v)

np_v += 10 # Increase all the values of the vector by 10

# Create a dac_vector for the updated np_v
v2 = sdsl4py.int_vector(np_v)
dv = sdsl4py.dac_vector(v2)

# Plot int_vector and dac_vector
plt.plot(v1, label='int_vector', color='blue')
plt.plot(dv, label='dac_vector', color='red', linestyle='--')
plt.ylabel('random numbers')
plt.legend()
plt.savefig('compact_vectors_plot.png')
```
The previous code generates this image

 ![Example of a plot using `sdsl4py` and matplotlib](img/compact_vectors_plot.png) 

## List of supported classes
List of available int_vector:
* `int_vector(contained)` default constructor
* `int_vector(size, default_value, width)` dynamic width
* `bit_vector(size, default_value)` static 1-bit width
* `int_vector_8(size, default_value)` static 8-bit width
* `int_vector_16(size, default_value)` static 16-bit width
* `int_vector_32(size, default_value)` static 32-bit width
* `int_vector_64(size, default_value)` static 64-bit width

List of compressed integer vectors:
* `enc_vector_elias_delta(container)`: binding of `enc_vector` with elias-delta encoding and sampling of 128
* `enc_vector_elias_gamma(container)`: binding of `enc_vector` with elias-gamma encoding and sampling of 128
* `enc_vector_fibonacci(container)`: binding of `enc_vector` with fibonacci encoding and sampling of 128
* `enc_vector_comma_2(container)`: binding of `enc_vector` with comma-2 encoding and sampling of 128
* `vlc_vector_elias_delta(container)`: binding of `vlc_vector` with elias-delta encoding and sampling of 128
* `vlc_vector_elias_gamma(container)`: binding of `vlc_vector` with elias-gamma encoding and sampling of 128
* `vlc_vector_fibonacci(container)`: binding of `vlc_vector` with fibonacci encoding and sampling of 128
* `vlc_vector_comma_2(container)`: binding of `vlc_vector` with comma 2 encoding and density 128
* `dac_vector(container)`: binding of `dac_vector`

List of utility methods:
* `store_to_file(v, file)`: serialize vector v to file
* `load_from_file(v, file)`: load vector v from file
* `size_in_bytes(v)`: returns size in bytes
* `size_in_mega_bytes(v)`: returns size in mega bytes

List of other implemented bindings (see examples of how to use them [here](examples):
* `Rank data structures` for bitvectors, supporting `rank_support_v<0>` and `rank_support_v<1>` versions
* `Select data structures` for bitvectors, supporting `rank_support_mcl<0>` and `rank_support_mcl<1>` versions
* *Wavelet Trees*, supporting `wt_int`, `wt_huff`, `wt_huff_int` and `wt_gmr` versions
* *Compresed Suffix Array*, supporting `csa_wt` and `csa_sada` versions
* *Largest Common Prefix*, supporting `lcp_wt` and `lcp_bitcompressed` versions
* *Balanced Parenthesis Support*, supporting `bp_support_sada`, `bp_support_g` and `bp_support_gg` versions

## How to add more bindings to the library
This implementation is modular and designed to facilitate extensions with new bindings. If you want to add more bindings, follow the steps below:
* **Step 0.**  Make sure you have the following tools installed and cloned correctly the repository using the installation guide:
    * `pybind11`: A library for creating Python bindings in C++.
    * `SDSL`: Succinct Data Structures Library.
    * A compiler compatible with C++14 or later (such as g++ or clang).
    * Python 3.x and development tools (e.g., python3-dev or equivalent).
* **Step 1.** Create a new file in the `sdsl4py` folder with your binding implementation. For example, to add a wrapper for *rank support*, create the file rank_support.cpp.
* **Step 2.** Include the necessary pybind11 and SDSL headers in the .cpp file. For instance:
    ```cpp
    #include <pybind11/pybind11.h>
    #include <sdsl/rank_support.hpp>
    #include <sdsl/vectors.hpp>
    ```
* **Step 3.** Define the classes and functions that you want to bind. For example:
```cpp
template <typename T>
void add_rank_support(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>())  // Default constructor
        .def("rank", [](const T& rs, size_t idx) { return rs.rank(idx); }, R"pbdoc(
            Returns the rank of the index in the data structure.
        )pbdoc")
        .def("size_in_bytes", [](const T& rs) { return sdsl::size_in_bytes(rs); }, R"pbdoc(
            Returns the size in bytes of the rank support.
        )pbdoc");
}
```
* **Step 4.** Use the `PYBIND11 MODULE` macro to make visible the SDSL classes to the Python module:
```cpp
PYBIND11_MODULE(sdsl4py, m) {
    m.doc() = "Python bindings for SDSL Rank Support";

    // Add rank support
    add_rank_support<sdsl::rank_support_v<1>>(m, "RankSupportV1");
}
```
* **Step 5.** Build again the project
in the sdsl4py directory:
```bash
pip install .
```

* **Step 6.** Test in Python. For example
```python
import sdsl_rank_support

rank_support = sdsl_rank_support.RankSupportV1()
print("Size in bytes:", rank_support.size_in_bytes())

```
## Troubleshooting
* If during the installation you get this (or similar) error:
    ```sh
    CMake Error at sdsl-lite/CMakeLists.txt:1 (cmake_minimum_required):
            Compatibility with CMake < 3.5 has been removed from CMake.
    ```
    The solution is to update `cmake_minimum_required(VERSION 3.15)` in the files `sdsl-lite/CMakeLists.txt`, `sdsl-lite/external/libdivsufsort/CMakeLists.txt` and `sdsl-lite/external/googletest/googletest/CMakeLists.txt`.

## Contributors
- José Fuentes (https://github.com/jfuentess)
- Pedro Paris (https://github.com/soyantouwu)
- Sebastián Aguayo (https://github.com/sherlock898)
- Gaspar Jiménez (https://github.com/Gaspinho)

## License
'sdsl4py' is distributed under the GNU General Public License (GPLv3) 
license. For more details see [LICENSE][LICENSE] file

## Acknowledgments
* The original SDSL library
* The authors of 'pysdsl' for laying the groundwork

[SDSL]: https://github.com/simongog/sdsl-lite
[pysdsl]: https://github.com/QratorLabs/pysdsl.git
[LICENSE]: https://github.com/algorithms-diicc/sdsl4py/blob/main/LICENSE
