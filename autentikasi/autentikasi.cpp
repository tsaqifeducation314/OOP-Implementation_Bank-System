#include "autentikasi.h"
#include "../kartu/kartu.h"

#include <iostream>

using namespace std;

// constructor class autentikasi
Autentikasi :: Autentikasi(string usernameAdmin, string passwordAdmin) {
    this->usernameAdmin = usernameAdmin;
    this->passwordAdmin = passwordAdmin;
    this->kartuAktif = nullptr;
    this->adminAktif = false;
}

// fungsi untuk mendaftarkan kartu 
void Autentikasi :: daftarkanKartu(KartuATM* kartu) {
    if (kartu == nullptr) {
        return;
    }

    for (KartuATM* data : daftarKartu) {
        if (data->getNomorKartu() == kartu->getNomorKartu()) {
            cout << "Nomor kartu sudah terdaftar." << endl;
            return;
        }
    }

    daftarKartu.push_back(kartu);
}

// fungsi untuk login nasabah
bool Autentikasi :: loginNasabah(const string& nomorKartu, const string& pin) {
    for (KartuATM* kartu : daftarKartu) {
        if (kartu->getNomorKartu() == nomorKartu) {
            if (!kartu->verifikasiPIN(pin)) {
                return false;
            }

            kartuAktif = kartu;
            adminAktif = false;

            cout << "Login nasabah berhasil." << endl;
            return true;
        }
    }

    cout << "Nomor kartu tidak ditemukan." << endl;
    return false;
}

// fungsi untuk login admin
bool Autentikasi :: loginAdmin(const string& username, const string& password) {
    if (username == usernameAdmin &&
        password == passwordAdmin) {
        kartuAktif = nullptr;
        adminAktif = true;

        cout << "Login admin berhasil." << endl;
        return true;
    }

    cout << "Username atau password admin salah." << endl;
    return false;
}

// fungsi untuk logout 
void Autentikasi :: logout() {
    kartuAktif = nullptr;
    adminAktif = false;

    cout << "Logout berhasil." << endl;
}

// getter status login
bool Autentikasi :: getStatusLogin() const {
    return kartuAktif != nullptr || adminAktif;
}

// getter status kartu 
KartuATM* Autentikasi :: getKartuAktif() const {
    return kartuAktif;
}

bool Autentikasi :: getStatusAdmin() const {
    return adminAktif;
}