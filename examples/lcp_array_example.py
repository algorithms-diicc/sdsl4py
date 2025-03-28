import sdsl4py

# Create the LCP array from this Python file
lcp_array = sdsl4py.LCPArrayWT()
lcp_array.construct1("lcp_array_example.py")

# Compute the size in bytes
print("LCP Array size (bytes):", lcp_array.size_in_bytes())

# Get the LCP at index 10
print("LCP at index 10:", lcp_array.get(10))
