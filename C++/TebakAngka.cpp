#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void TebakAngka() {
    int tebakan;
    srand(time(0)); // Seed random
    int angka = rand() % 100 + 1;

    cout << "Selamat datang di permainan Tebak Angka" << endl;
    cout << "Komputer telah memilih angka 1 - 100, tebak angkanya!" << endl;

    do {
        cout << "Tebakanmu: ";
        cin >> tebakan;

        if(tebakan < angka) {
            cout << "Angka terlalu rendah." << endl;
        } else if(tebakan > angka) {
            cout << "Angka terlalu tinggi." << endl;
        } else {
            cout << "Tebakanmu benar!" << endl;
        }
    } while(tebakan != angka);
}

int main() {
    TebakAngka();
    return 0;
}
    