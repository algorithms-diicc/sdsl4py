import sdsl4py
import numpy as np
import matplotlib.pyplot as plt

l = np.random.randint(0, 512, 100, dtype=np.uint32)

v = sdsl4py.int_vector(l)

plt.hist(v, bins=20);
plt.show();
