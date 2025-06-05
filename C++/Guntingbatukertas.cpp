#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int main() {
    srand(time(0));
    while(true) {
        string pemain;

        string random[] = {"Gunting", "Batu", "Kertas"};
        int comp = rand() % 3;
        
        cout << "\nMAIN GUNTING-BATU-KERTAS" << endl;
        cout << "1. Gunting--------------" << endl;
        cout << "2. Batu-----------------" << endl;
        cout << "3. Kertas---------------" << endl;
        cout << "4. Keluar---------------" << endl;

        cout << "Masukkan Pilihanmu: ";
        cin >> pemain;

        if (pemain == "Keluar" || pemain == "4") {
            cout << "Keluar dari game..." << endl;
            return 0;
        }
        
        if (pemain == "1") {
            pemain = "Gunting";
        } else if (pemain == "2") {
            pemain = "Batu";
        } else if (pemain == "3") {
            pemain = "Kertas";
        }

        cout << "Komputer sedang Memilih..." << endl;
        Sleep(2000);
        cout << "Komputer Memilih: " << random[comp] << endl;
        cout << "Kamu Memilih: " << pemain << endl;
        Sleep(1000);

        if (pemain == "Gunting" || pemain == "1") {
            if (random[comp] == "Gunting") {
                cout << "Kamu Seri!!" << endl;
            } else if (random[comp] == "Batu") {
                cout << "Kamu kalah!!" << endl;
            } else if (random[comp] == "Kertas") {
                cout << "Kamu menang!!" << endl;
            }
        } else if (pemain == "Batu" || pemain == "2") {
            if (random[comp] == "Gunting") {
                cout << "Kamu menang!!" << endl; 
            } else if (random[comp] == "Batu") {
                cout << "Kamu seri!!" << endl;
            } else if (random[comp] == "Kertas") {
                cout << "Kamu kalah!!" << endl;
            }
        } else if (pemain == "Kertas" || pemain == "3") {
            if (random[comp] == "Gunting") {
                cout << "Kamu kalah!!" << endl; 
            } else if (random[comp] == "Batu") {
                cout << "Kamu menang!!" << endl;
            } else if (random[comp] == "Kertas") {
                cout << "Kamu seri!!" << endl;
            }
        } else {
            cout << "Pilihan tidak valid, coba lagi!" << endl;
        }
    }
}
