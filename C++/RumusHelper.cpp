#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>

using namespace std;

void phitagoras() {
    string sa, sb, sc;
    double a, b, c;
    double aa, bb, cc;

    cout << "Phytagoras : a² + b² = c²" << endl;
    cout << "Masukkan nilai null apabila ingin dicari." << endl;
    cout << "Masukkan Nilai a & b: " << endl;
    cin >> sa >> sb;
    if (sa == "null") {
        cout << "masukkan nilai c: ";
        cin >> sc;
        b = stod(sb);
        c = stod(sc);
        a = sqrt(c * c - b * b);
        bb = b * b;
        cc = c * c;

        cout << "a² = c² - b²" << endl;
        cout << "a² = " << c << "² - " << b << "²" << endl;
        cout << "a² = " << cc << " - " << bb << endl;
        cout << "a² = " << cc - bb << endl;
        cout << "a = √(" << cc - bb << ")" << endl; 
        cout << "a = " << a << endl;
    } else if (sb == "null") {
        cout << "masukkan nilai c: ";
        cin >> sc;
        a = stod(sa);
        c = stod(sc);
        b = sqrt(c * c - a * a);
        aa = a * a;
        cc = c * c;

        cout << "b² = c² - a²" << endl;
        cout << "b² = " << c << "² - " << a << "²" << endl;
        cout << "b² = " << cc << " - " << aa << endl;
        cout << "b² = " << cc - aa << endl;
        cout << "b = √(" << cc - aa << ")" << endl; 
        cout << "b = " << b << endl;
    } else if (sa != "null" && sb != "null") {
        a = stod(sa);
        b = stod(sb);
        aa = a * a;
        bb = b * b;
        cc = aa + bb;
        c = sqrt(cc);

        cout << "a² + b² = c²" << endl;
        cout << a << "² + " << b << "² = c²" << endl;
        cout << aa << " + " << bb << " = c²" << endl;
        cout << "c = √" << cc << endl;
        cout << "c = " << c << endl;
    }
} 

void BangunRuang() {
    int perintah, tanya;
    double a;

    string bangun[] = {"persegi", "Persegi Panjang", "Segitiga", "Lingkaran", "Kubus", "Balok", "Prisma"};
    int Jbangun = sizeof(bangun) / sizeof(bangun[0]);

    for (int i = 0; i < Jbangun; i++) {
        cout << i + 1 << ". " << bangun[i] << endl;
    }
    cout << "Masukkan Perintah: ";
    cin >> perintah;

    if (perintah == 1) {
        cout << "Apa yang dicari?" << endl;
        cout << "1. Luas" << endl;
        cout << "2. Keliling" << endl;
        cout << "3. Sisi" << endl;
        cin >> tanya;
        if (tanya == 1) {
            cout << "Masukkan Panjang Sisi: ";
            cin >> a;
            cout << "L.Persegi = Sisi²" << endl;
            cout << "L.Persegi = " << a << "²" << endl;
            cout << "L.Persegi = " << a * a <<  endl;
        } else if (tanya == 2) {
            cout << "Masukkan Panjang Sisi: ";
            cin >> a;
            cout << "K.Persegi = Sisi x 4" << endl;
            cout << "K.Persegi = " << a << " x 4" << endl;
            cout << "K.Persegi = " << a * 4 <<  endl;
        } else if (tanya == 3) {
            string SKeliling, SLuas;
            double Keliling, Luas;
            cout << "Masukkan Keliling / Luas (Null untuk nilai masih belum diketahui.): " << endl;
            cin >> SKeliling >> SLuas;
            if (SKeliling == "Null") {
                Luas = stod(SLuas);
                cout << "S.Persegi = √Luas" << endl;
                cout << "S.Persegi = √" << Luas << endl;
                cout << "S.Persegi = " << sqrt(Luas) << endl;
            } else if (SLuas == "Null") {
                Keliling = stod (SKeliling);
                cout << "S.Persegi = Keliling / 4" << endl;
                cout << "S.Persegi = " << Keliling << "/ 4" << endl;
                cout << "S.Persegi = " << Keliling / 4 << endl;                
            } else if (SLuas != "Null" && SKeliling != "Null") {
                Luas = stod(SLuas);
                Keliling = stod (SKeliling);
                cout << "Metode 1(luas):" << endl;
                cout << "S.Persegi = √Luas" << endl;
                cout << "S.Persegi = √" << Luas << endl;
                cout << "S.Persegi = " << sqrt(Luas) << endl;
                cout << "Metode 2(keliling):" << endl;
                cout << "S.Persegi = Keliling / 4" << endl;
                cout << "S.Persegi = " << Keliling << "/ 4" << endl;
                cout << "S.Persegi = " << Keliling / 4 << endl;
            }
        }
    }
}
/*
    };
    cout << "Masukkan Perintah, panjang sisi A, B dan C." << endl;
    cin >> perintah >> a >> b >> c;
    if (perintah == 1) {
        for (int i = 0; i < Jtarget; i++) {
            cout << i + 1 << ". " << target[i] << endl;
        }
        cout << "Masukkan Target: ";
        cin >> tanya;
        if (tanya == 1) {
            hasil = a * a;
            cout << "L = a²" << endl;
            cout << "L = " << a << "²" << endl;
            cout << "L = " << hasil << endl;
        }
    }
*/
int main() {
    while(true) {
        SetConsoleOutputCP(CP_UTF8);
        
        string p1;
        cout << "What can i help you with, nino?" << endl;
        cout << "1. pythagoras" << endl;
        cout << "2. Bangun datar/ruang" << endl;
        cin >> p1;
        if (p1 == "1" || p1 == "pythagoras"){
            cout << "Sure..." << endl;
            Sleep(1000);
            phitagoras();
        } else if (p1 == "2" || p1 == "Bangun datar/ruang"){
            cout << "Sure..." << endl;
            Sleep(1000);
            BangunRuang();
        } else {
            cout << "Maaf, perintah anda belum kukenali." << endl;
            return 0;
        }
    }
} 