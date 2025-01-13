import sdsl4py

# Crear un Rank Support sobre un bitvector
bit_vector = sdsl4py.bit_vector([0, 1, 0, 1, 1, 0, 1])
rank_support = sdsl4py.RankSupportV0(bit_vector)

# Calcular el rank de la posición 4
print("Rank at position 4:", rank_support.rank(4))

# Guardar y cargar desde archivo
rank_support.store_to_file("rank_support.bin")
rank_support.load_from_file("rank_support.bin")
