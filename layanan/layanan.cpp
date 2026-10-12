#include "layanan.h"
#include "../nasabah/nasabah.h"

#include <iostream>
#include <string>

using namespace std;

// constructor class layanan bank 
LayananBank::LayananBank(string namaBank)
    : bank(namaBank), nasabahAktif(nullptr) {
}

// fungsi registrasi nasabah
void LayananBank::registrasiNasabah() {
    string id;
    string nama;
    string tanggalLahir;
    string alamat;
    string nomorTelepon;
    string email;

    cout << "\n===== REGISTRASI NASABAH =====" << endl;

    cout << "ID Nasabah       : ";
    getline(cin >> ws, id);

    cout << "Nama             : ";
    getline(cin, nama);

    cout << "Tanggal Lahir    : ";
    getline(cin, tanggalLahir);

    cout << "Alamat           : ";
    getline(cin, alamat);

    cout << "Nomor Telepon    : ";
    getline(cin, nomorTelepon);

    cout << "Email            : ";
    getline(cin, email);

    Nasabah nasabah(
        id,
        nama,
        tanggalLahir,
        alamat,
        nomorTelepon,
        email
    );

    bank.tambahNasabah(nasabah);
}

// fungsi untuk melihat data nasabah
void LayananBank::lihatDataNasabah() {
    string id;

    cout << "\n===== LIHAT DATA NASABAH =====" << endl;
    cout << "Masukkan ID Nasabah: ";
    getline(cin >> ws, id);

    Nasabah* nasabah = bank.cariNasabah(id);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    nasabah->lihatInformasiPribadi();
}

// fungsi untuk mengubah data nasabah
void LayananBank::ubahDataNasabah() {
    string id;

    cout << "\n===== UBAH DATA NASABAH =====" << endl;
    cout << "Masukkan ID Nasabah: ";
    getline(cin >> ws, id);

    Nasabah* nasabah = bank.cariNasabah(id);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    nasabah->perbaruiInformasiPribadi();
}