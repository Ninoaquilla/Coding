import numpy as np
import matplotlib.pyplot as plt

# Parameter orbit
a = 8  # Sumbu semi-mayor
b = 4  # Sumbu semi-minor
t = np.linspace(0, 2 * np.pi, 100)  # Sudut dari 0 hingga 2π

# Persamaan elips
x = a * np.cos(t)
y = b * np.sin(t)

# Plot orbit
plt.figure(figsize=(6,6))
plt.plot(x, y, label="Orbit Planet")
plt.scatter(0, 0, color="yellow", s=200, label="Matahari")  # Matahari di pusat
plt.xlabel("Jarak X (AU)")
plt.ylabel("Jarak Y (AU)")
plt.title("Simulasi Orbit Sederhana")
plt.legend()
plt.grid()
plt.axis("equal")  # Skala sumbu sama

# Tampilkan grafik
plt.show()