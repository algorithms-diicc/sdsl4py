# sdsl4py: Python Bindings for SDSL
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

## List of supported classes
List of all available vectors:
Integer Vectors:
* `int_vector(size, default_value, width)` dynamic width
* `bit_vector(size, default_value)` static 1bit width
* `int_vector_8(size, default_value)` static 8bit width
* `int_vector_16(size, default_value)` static 16bit width
* `int_vector_32(size, default_value)` static 32bit width
* `int_vector_64(size, default_value)` static 64bit width

Compressed Integer Vectors:
* `enc_vector_elias_delta(container)` enc vector, elias delta encoding, density 128
* `enc_vector_elias_gamma(container)` enc vector, elias gamma encoding, density 128
* `enc_vector_fibonacci(container)` enc vector, fibonacci encoding, density 128
* `enc_vector_comma_2(container)` enc vector, comma 2 encoding, density 128
* `vlc_vector_elias_delta(container)` vlc vector, elias delta encoding, density 128
* `vlc_vector_elias_gamma(container)` vlc vector, elias gamma encoding, density 128
* `vlc_vector_fibonacci(container)` vlc vector, fibonacci encoding, density 128
* `vlc_vector_comma_2(container)` vlc vector, comma 2 encoding, density 128
* `dac_vector(container)` dac vector


List of utility methods:
* `store_to_file(v, file)` serialize vector v to file
* `load_from_file(v, file)` load vector v to file
* `size_in_bytes(v)` returns size in bytes
* `size_in_mega_bytes(v)` returns size in mega bytes

Recently Succint Data Structures added:
* `Wavelet Trees` int, huff, huff_int, gmr
* `Suffix Array` wt and sada
* `Largest Common Prefix` wt and bit compressed
* `Balanced Parenthesis Support` sada g and gg
* `Rank Support` v0 and v1 
* `Select Support` mcl0 and mcl1

## How to add a implentation to the library
This project provides Python bindings for the compact data structures in the SDSL library using pybind11. It is modular and designed to facilitate extensions with new implementations.
# Step 0:
Make sure you have the following tools installed and cloned correctly the repository using the installation guide:
* `Pybind11`: A library for creating Python bindings in C++.
* `SDSL`: Succinct Data Structures Library.
* A compiler compatible with C++14 or later (such as g++ or clang).
* Python 3.x and development tools (e.g., python3-dev or equivalent).
# Step 1: Create a .cpp File
Create a new file in the src/ directory for your implementation. For example, to add a wrapper for Rank Support, create the file rank_support.cpp.
# Step 2: Include Required Dependencies
Include the necessary pybind11 and SDSL headers in the .cpp file:
```cpp
#include <pybind11/pybind11.h>
#include <sdsl/rank_support.hpp>
#include <sdsl/vectors.hpp>
```
# Step 3: Define Functions and Classes
Define the classes and functions needed to expose the features of the data structure. For example:
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
# Step 4: Expose Classes to the Module
Use the `PYBIND11 MODULE` macro to expose the classes to the Python module:
```cpp
PYBIND11_MODULE(sdsl4py, m) {
    m.doc() = "Python bindings for SDSL Rank Support";

    // Add rank support
    add_rank_support<sdsl::rank_support_v<1>>(m, "RankSupportV1");
}
```
# Step 5: Building
in the sdsl4py directory:
```bash
pip install .
```

# Step 6: Test in python
```python
import sdsl_rank_support

rank_support = sdsl_rank_support.RankSupportV1()
print("Size in bytes:", rank_support.size_in_bytes())
```


## License
'sdsl4py' is distributed under the GNU General Public License (GPLv3) 
license. For more details see [LICENSE][LICENSE] file

## Acknowledgments
* The original SDSL library
* The authors of 'pysdsl' for laying the groundwork

[SDSL]: https://github.com/simongog/sdsl-lite
[pysdsl]: https://github.com/QratorLabs/pysdsl.git
[LICENSE]: https://github.com/algorithms-diicc/sdsl4py/blob/main/LICENSE
