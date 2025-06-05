import numpy as np
import matplotlib.pyplot as plt

a = 8
b = 4
t = np.linspace(0, 2 * np.pi, 100)

X = a * np.cos(t)
Y = b * np.cos(t)

plt.axis("equal")

plt.show()