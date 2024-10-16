import sdsl4py

v = sdsl4py.int_vector(size=100, default_value=0, int_width=8)
for i in range(100):
    v[i] = i

ev = sdsl4py.enc_vector_elias_delta(v)

print(sdsl4py.size_in_bytes(v))
print(sdsl4py.size_in_bytes(ev))
