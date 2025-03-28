import sdsl4py

# Create the Suffix array from this Python file
sa = sdsl4py.SuffixArrayWT()
sa.construct1("suffix_array_example.py")

# Compute the size in bytes
print("Suffix Array size (bytes):", sa.size_in_bytes())

# Get the 11th entry of the suffix array
print("Suffix at index 10:", sa.get(10))
