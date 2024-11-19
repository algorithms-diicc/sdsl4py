import sdsl4py

# Crear un objeto de SuffixArray y LCPArray
suffix_array = sdsl4py.SuffixArrayWT()

# Cargar datos desde un archivo
suffix_array.load_from_file("suffix_array_file")

# Obtener el tamaño en bytes
print("Suffix Array size (bytes):", suffix_array.size_in_bytes())
# Acceder a elementos individuales
print("Suffix at index 10:", suffix_array.get_suffix(10))
