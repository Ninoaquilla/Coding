def new_func(X, Y=0):
    Z = (X + Y)
    S = (X * Y)
    if Y != 0:
        H = (X / Y)
        return Z, S, H
    return Z, S

Hasil = new_func(9)
if Hasil[1] is not None:
    print("Z =", Hasil[0], "S =", Hasil[1], "H =", Hasil[1])
else:
    print("Z =", Hasil[0], "H =", Hasil[1])