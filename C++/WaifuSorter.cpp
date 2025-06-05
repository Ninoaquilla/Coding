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
    string pilihan;
    do {
        cout << "-----------------------------------" << endl;
        cout << "-----------WAIFU LIST--------------" << endl;
        cout << "----------Tambah Waifu(1)-------------" << endl;
        cout << "--------Lihat List Waifu(2)-----------" << endl;
        cout << "------Simpan Waifu saat ini(3)--------" << endl;
        cin >> pilihan;
    } while (pilihan != "4");

}
