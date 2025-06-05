#include <iostream>


using namespace std;

int x, y;

void Pertambahan() {
    int z;
    z = x + y;
    cout << "--------------------" << endl;
    cout << "Hasil dari " << x << " + " << y << " adalah " << z << endl;
    cout << "--------------------" << endl;
}

void Pengurangan() {
    int z;
    z = x - y;
    cout << "--------------------" << endl;
    cout << "Hasil dari " << x << " - " << y << " adalah " << z << endl;
    cout << "--------------------" << endl;
}

void Perkalian() {
    int z;
    z = x * y;
    cout << "--------------------" << endl;
    cout << "Hasil dari " << x << " x " << y << " adalah " << z << endl;
    cout << "--------------------" << endl;
}

void Pembagian() {
    float z;
    z = (float)x / y;
    cout << "--------------------" << endl;
    cout << "Hasil dari " << x << " : " << y << " adalah " << z << endl;
    cout << "--------------------" << endl;
}

bool Berhenti() {
    char jawab;
    cout << "Apakah anda ingin lanjut?? (Y?N)." << endl;
    cin >> jawab;

    if (jawab == 'Y' || jawab == 'y') {
        cout << "Melanjutkan..." << endl;
        return true;
    } else if (jawab == 'N' || jawab == 'n') {
        break;
    } else {
        cout << "Perintah tak ditemukan" << endl;
        return Berhenti();
    }
}

int main() {
    while (true) {
        int perintah;
        cout << "--------------------" << endl;
        cout << "1. Pertambahan......" << endl;
        cout << "2. Pengurangan......" << endl;
        cout << "3. Perkalian........" << endl;
        cout << "4. Pembagian........" << endl;
        cout << "5. Keluar..........." << endl;
        cout << "--------------------" << endl;
        cout << "" << endl;
        cout << "Masukkan Perintah (1/2/3/4)." << endl;
        cin >> perintah;

        cout << "Masukkan Nilai X: " << endl;
        cin >> x;
        cout << "Masukkan Nilai Y: " << endl;
        cin >> y;
    
        if (perintah == 1) {
            Pertambahan();
            Berhenti();
        } else if (perintah == 2) {
            Pengurangan();
            Berhenti();
        } else if (perintah == 3) {
            Perkalian();
            Berhenti();
        } else if (perintah == 4) {
            Pembagian();
            Berhenti();
        } else if (perintah == 5) {
            char Yakin;
            cout << "Anda Yakin Untuk Keluar?? (Y/N)";
            cin >> Yakin;

            if (Yakin == 'Y') {
                return 0;
            } else if (Yakin == 'N') {
                cout << " " << endl;
            } else {
                cout << "Perintah Tak Dimengerti." << endl;
            }

        } else {
            cout << perintah << " tidak dimengerti, tolong ulangi." << endl;
        }
    }
}