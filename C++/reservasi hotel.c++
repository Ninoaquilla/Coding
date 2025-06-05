#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Reservation {
public:
    string name;
    string check_in;
    string check_out;

    Reservation(string n, string ci, string co) : name(n), check_in(ci), check_out(co) {}
};

class Hotel {
private:
    vector<Reservation> reservations;

public:
    void addReservation(const string& name, const string& check_in, const string& check_out) {
        reservations.emplace_back(name, check_in, check_out);
        cout << "Reservasi berhasil untuk " << name << " dari " << check_in << " hingga " << check_out << "." << endl;
    }

    void viewReservations() {
        if (reservations.empty()) {
            cout << "Tidak ada reservasi saat ini." << endl;
            return;
        }
        cout << "Daftar Reservasi:" << endl;
        for (size_t i = 0; i < reservations.size(); ++i) {
            cout << i + 1 << ". Nama: " << reservations[i].name 
                 << ", Check-in: " << reservations[i].check_in 
                 << ", Check-out: " << reservations[i].check_out << endl;
        }
    }

    void cancelReservation(size_t index) {
        if (index < reservations.size()) {
            cout << "Reservasi untuk " << reservations[index].name << " berhasil dibatalkan." << endl;
            reservations.erase(reservations.begin() + index);
        } else {
            cout << "Indeks reservasi tidak valid." << endl;
        }
    }
};

int main() {
    Hotel hotel;
    int choice;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Reservasi" << endl;
        cout << "2. Lihat Reservasi" << endl;
        cout << "3. Batalkan Reservasi" << endl;
        cout << "4. Keluar" << endl;

        cout << "Pilih opsi (1-4): ";
        cin >> choice;

        if (choice == 1) {
            string name, check_in, check_out;
            cout << "Masukkan nama: ";
            cin.ignore(); // Membersihkan buffer
            getline(cin, name);
            cout << "Masukkan tanggal check-in (YYYY-MM-DD): ";
            getline(cin, check_in);
            cout << "Masukkan tanggal check-out (YYYY-MM-DD): ";
            getline(cin, check_out);
            hotel.addReservation(name, check_in, check_out);
        } else if (choice == 2) {
            hotel.viewReservations();
        } else if (choice == 3) {
            hotel.viewReservations();
            size_t index;
            cout << "Masukkan nomor reservasi yang ingin dibatalkan: ";
            cin >> index;
            hotel.cancelReservation(index - 1); // Mengurangi 1 untuk indeks 0
        } else if (choice == 4) {
            cout << "Terima kasih! Sampai jumpa." << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 4);

    return 0;
}