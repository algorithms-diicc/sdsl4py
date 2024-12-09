import sdsl4py

# Crear un Wavelet Tree para enteros
wavelet_tree_int = sdsl4py.WaveletTreeInt()
wavelet_tree_int.load_from_file("data_int.wt")

# Obtener el tamaño en bytes
print("Size in bytes:", wavelet_tree_int.size_in_bytes())

# Guardar el Wavelet Tree en un archivo
wavelet_tree_int.store_to_file("output_int.wt")

# Crear instancia de wt_int
wt = sdsl4py.WaveletTreeInt()

# Llamar a range_search_2d
resultados = wt.range_search_2d(0, 10, 1, 5)
print(resultados)  # Esto debería imprimir los pares (índice, valor)
