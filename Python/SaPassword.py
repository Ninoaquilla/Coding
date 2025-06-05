def perintah():
    while True:
        print("1. Add Password.")
        print("2. Remove Password.")
        print("3. Replace Password.")
        print("4. Exit")

        Command = input("Masukkan Perintah[1/2/3/4]: ")
        if Command == '1':
            Meminta()
        elif Command == '2':
            print("nunggu update dulu :V")
        elif Command == '3':
            print("nunggu update dulu :V")
        elif Command == 'Baca':
            with open('Test.txt', 'r') as file:
                Isi = file.read()
                print(Isi)
        elif Command == '4':
           break
        else:
           print("Perintah tidak valid")
           continue
            
         

def Meminta():
    Akun = input("Masukkan Nama Akun: ")
    Password = input("Masukkan Password: ")

    if Akun == "EXIT!" or Password == "EXIT!":
        exit()
    else:
        print(f"Password {Akun} Anda Adalah {Password}.")

        with open("Akun.txt", "a") as file:
            file.write(f"{Akun} : {Password}.\n")

        print("Password Tersimpan...")


perintah()