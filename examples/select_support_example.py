import sdsl4py  # El nombre de tu módulo después de compilarlo

# Crear un bit_vector y establecer algunos bits a 1
bv = sdsl4py.bit_vector(8)  # Crear un bit_vector de longitud 8
bv[1] = 1
bv[3] = 1
bv[5] = 1
bv[7] = 1

# Crear una instancia de select_support sobre el bit_vector
select_support = sdsl4py.SelectSupportMCL0(bv)

# Utilizar la función select para encontrar la posición del i-ésimo 1
pos_1 = select_support.select(1)  # Debe retornar la posición del primer 1, que es 1
pos_2 = select_support.select(2)  # Debe retornar la posición del segundo 1, que es 3
pos_3 = select_support.select(3)  # Debe retornar la posición del tercer 1, que es 5

# Consultar el tamaño en bytes de la estructura select_support
size = select_support.size_in_bytes()

# Almacenar la estructura en un archivo
select_support.store_to_file("select_support_data.sdsl")

# Cargar la estructura desde un archivo
select_support.load_from_file("select_support_data.sdsl")

# Mostrar los resultados
print(f"Posición del primer 1: {pos_1}")
print(f"Posición del segundo 1: {pos_2}")
print(f"Posición del tercer 1: {pos_3}")
print(f"Tamaño en bytes: {size}")
