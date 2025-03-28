import sdsl4py

# Construct a int_vector of 100 0-value symbol using 1 byte per symbol
v = sdsl4py.int_vector(size=100, default_value=0, int_width=8)

# Fill the vector with increasing values
for i in range(100):
    v[i] = i

# Construct an enc_vector with Elias-delta codes
ev = sdsl4py.enc_vector_elias_delta(v)

# Print the size in bytes
print("int_vector size: ", sdsl4py.size_in_bytes(v), "bytes")
print("enc_vector size: ", sdsl4py.size_in_bytes(ev), "bytes")
