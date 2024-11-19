import sdsl4py

# Crear un bit_vector de sdsl4py
bv = sdsl4py.bit_vector(8)  # Inicializar un bit_vector de longitud 8
bv[0] = 0
bv[1] = 1
bv[2] = 0
bv[3] = 1
bv[4] = 1
bv[5] = 0
bv[6] = 1
bv[7] = 0

# Crear una instancia de bp_support_g o el tipo correspondiente
bp = sdsl4py.BPSupportSada()

# Inicializar la estructura con el bit_vector de sdsl4py
bp.initialize(bv)

# Realizar operaciones
open_pos = bp.find_open(5)  # Encuentra la posición de apertura
close_pos = bp.find_close(5)  # Encuentra la posición de cierre
rank_val = bp.rank(3)  # Obtiene el rank para la posición 3
select_val = bp.select(2)  # Obtiene el select para la posición 2

print(f"Posición de apertura: {open_pos}")
print(f"Posición de cierre: {close_pos}")
print(f"Rank de 3: {rank_val}")
print(f"Select de 2: {select_val}")
