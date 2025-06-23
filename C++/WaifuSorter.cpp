#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct waifu {
    string nama;
    string asal;
    string ukuran;
};

vector<waifu> listwaifu;

void Add() {
    string confirm;
    string nama, asal;

    while(true) {
        cout << "Tambah waifu (Yes/No?): ";
        cin >> confirm;
        if(confirm == "Yes") {
            cout << "Nama Waifu: ";
            cin >> nama;
            cout << "Dari anime apa?" << endl;
            cin >> asal;

            waifu w;
            w.nama = nama;
            w.asal = asal;
            listwaifu.push_back(w);

            cout << "Waifu sudah ditambahkan kedalam list..." << endl;
            break;
        } else if(confirm == "No") {
            cout << "Kembali..." << endl;
            break;
        } else {
            cout << "Konfirmasi tidak dikenali." << endl;
        }
    }
}

void list() {
    if (listwaifu.empty()) {
        cout << "Belum Punya Waifu." << endl;
        return;
    } 

    cout << "===Daftar Waifu===" << endl;
    for (size_t i = 0; i < listwaifu.size(); i++) {
        cout << i + 1 << ". " << listwaifu[i].nama << ": " << listwaifu[i].asal << endl;
    }
}

void save(const  vector<waifu>& listwaifu) {
    ofstream file("Waifu.txt");

    if (!file) {
        cout << "File tidak bisa dibuka." << endl;
        return;
    }

    for (size_t i = 0; i < listwaifu.size(); i++) {
        file << i + 1 << ". " << listwaifu[1].nama << ": " << listwaifu[i].asal << endl;
    }

    file.close();
    cout << "Berhasil Menyimpan." << endl;
}

int main() {
    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Waifu\n";
        cout << "2. Lihat Daftar Waifu\n";
        cout << "3. Simpan ke File\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                Add();
                break;
            case 2:
                list();
                break;
            case 3:
                save(listwaifu);
                break;
            case 4:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);
}