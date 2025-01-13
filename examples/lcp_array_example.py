import sdsl4py

# Crear un objeto de SuffixArray y LCPArray
lcp_array = sdsl4py.LCPArrayWT()

# Cargar datos desde un archivo
lcp_array.load_from_file("lcp_array_file")

# Obtener el tamaño en bytes
print("LCP Array size (bytes):", lcp_array.size_in_bytes())
# Acceder a elementos individuales
print("LCP at index 10:", lcp_array.get_lcp(10))