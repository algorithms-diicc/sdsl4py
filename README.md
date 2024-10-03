# sdsl4py: Python Bindings for SDSL
`sdsl4py` is a Python library that provides bindings for the [SDSL][SDSL](Succinct Data Structure Library).
This project is based on [pysdsl][pysdsl] the reason of this project is because pysdsl stop recieving support.

## Installation         
Installation using pip:

```sh
git clone https://github.com/diicc-udec/sdsl4py.git --recursive
cd sdsl4py
pip install .
```

## Getting Started
The core class is the library is the `int_vector` it support almost all 
of the sdsl int_vector functions. 

The vectors can be compressed into enc, vlc or dac vectors.

```python
import sdsl4py

v = sdsl4py.int_vector(size=100, default_value=0, int_width=8)
for i in range(100):
    v[i] = i

ev = sdsl4py.enc_vector_elias_delta(v)

print(sdsl4py.size_in_bytes(v))
print(sdsl4py.size_in_bytes(ev))
```

Data structures can be load and saved to a file with the utility function
```python
store_to_file(ev, "ev")

ev2 = sdsl.enc_vector_elias_delta()
load_from_fike(ev2, "ev")
```

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


## License
'sdsl4py' is distributed under the GNU General Public License (GPLv3) 
license. For more details see [LICENSE][LICENSE] file

## Acknowledgments
* The original SDSL library
* The authors of 'pysdsl' for laying the groundwork

[SDSL]: https://github.com/simongog/sdsl-lite
[pysdsl]: https://github.com/QratorLabs/pysdsl.git
[LICENSE]: https://github.com/Sherlock898/sdsl4py/blob/main/LICENSE
