import sdsl4py

# Representing the following tree as a balanced parentheses sequence
#     o
#    / \
#   o   o
#      / \
#     o   o
#    / \
#   o   o
#
# (()((()())()))
#

# Create a bit_vector representing the balanced parentheses sequence (1: open, 0: close)
bv = sdsl4py.bit_vector(14)
bv[0] = 1
bv[1] = 1
bv[2] = 0
bv[3] = 1
bv[4] = 1
bv[5] = 1
bv[6] = 0
bv[7] = 1
bv[8] = 0
bv[9] = 0
bv[10] = 1
bv[11] = 0
bv[12] = 0
bv[13] = 0

# Create the instance of bp_support_g
bp = sdsl4py.BPSupportSada()

# And initialize the data structure with the balanced parentheses sequence
bp.initialize(bv)

# Compute the Index of the open parenthesis matching bp[9]=')'
open_pos = bp.find_open(9)
# Compute the Index of the closing parenthesis matching bp[3]='('
close_pos = bp.find_close(3)

# Compute the number of open parentheses up to Index 10
rank_val = bp.rank(10)
# Compute the Index of the 4th open parenthesis
select_val = bp.select(4)

print("Index of the open parenthesis matching bp[9]=\')\':", open_pos)
print("Index of the closing parenthesis matching bp[3]=\'(\':", close_pos)
print("Rank of open parentheses up to Index 10:", rank_val)
print("Index of the fourth open parenthesis:", select_val)
