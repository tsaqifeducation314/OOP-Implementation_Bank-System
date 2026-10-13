#include "kartu.h"
#include "../rekening/rekening.h"

#include <iostream>
#include <cctype>

using namespace std;

// constructor class kartu ATM 
KartuATM :: KartuATM(string nomorKartu, string tanggalTerbit, string tanggalKadaluarsa, string pin, Rekening* rekening) {
    this->nomorKartu = nomorKartu;
    this->tanggalTerbit = tanggalTerbit;
    this->tanggalKadaluarsa = tanggalKadaluarsa;
    this->pin = pin;
    this->rekening = rekening;
    this->status = true;
    this->percobaanPIN = 0;
}

// fungsi untuk verifikasi pin
bool KartuATM :: verifikasiPIN(const string& pinInput) {
    if (!status) {
        cout << "Kartu ATM tidak aktif atau telah diblokir." << endl;
        return false;
    }

    if (pinInput == pin) {
        percobaanPIN = 0;
        return true;
    }

    percobaanPIN++;

    cout << "PIN salah. Sisa percobaan: "
         << 3 - percobaanPIN << endl;

    if (percobaanPIN >= 3) {
        blokirKartu();
    }

    return false;
}

// fungsi untuk mengubah pin 
bool KartuATM :: ubahPIN(const string& pinLama, const string& pinBaru) {
    if (!status) {
        cout << "Kartu ATM tidak aktif atau telah diblokir." << endl;
        return false;
    }

    if (!verifikasiPIN(pinLama)) {
        return false;
    }

    if (pinBaru.length() != 6) {
        cout << "PIN baru harus terdiri dari 6 digit." << endl;
        return false;
    }

    for (char digit : pinBaru) {
        if (!isdigit(static_cast<unsigned char>(digit))) {
            cout << "PIN baru hanya boleh berisi angka." << endl;
            return false;
        }
    }

    pin = pinBaru;

    cout << "PIN berhasil diubah." << endl;
    return true;
}

// fungsi untuk memblokir kartu
void KartuATM :: blokirKartu() {
    status = false;
    cout << "Kartu ATM telah diblokir." << endl;
}

// getter nomor kartu 
string KartuATM :: getNomorKartu() const {
    return nomorKartu;
}

// getter status kartu
bool KartuATM :: getStatusKartu() const {
    return status;
}

// getter rekening 
Rekening* KartuATM :: getRekening() const {
    return rekening;
}

// getter tanggal terbit kartu ATM 
string KartuATM :: getTanggalTerbit() const {
    return tanggalTerbit;
}

// getter tanggal kadaluarsa kartu ATM 
string KartuATM :: getTanggalKadaluarsa() const {
    return tanggalKadaluarsa;
}

// getter pin kartu ATM 
string KartuATM :: getPIN() const {
    return pin;
}