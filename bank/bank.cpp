#include "bank.h"
#include <iostream>
#include <string>
#include<vector>
using namespace std; 

// constructor class bank 
Bank :: Bank(string nama) {
    namaBank = nama; 
}

// fungsi untuk menambah nasabah 
void Bank :: tambahNasabah(const Nasabah& nasabah) {
    for (const Nasabah& data : daftarNasabah) {
        if (data.getIdNasabah() == nasabah.getIdNasabah()) {
            cout << "ID nasabah sudah terdaftar." << endl;
            return;
        }
    }

    daftarNasabah.push_back(nasabah); 
    cout << "Nasabah berhasil ditambahkan ke bank " << namaBank << "." << endl;
}

// fungsi untuk menghapus nasabah 
void Bank :: hapusNasabah(const string& idNasabah) {
    for (auto it = daftarNasabah.begin(); it != daftarNasabah.end(); ++it) {
        if (it->getIdNasabah() == idNasabah) {
            daftarNasabah.erase(it); 
            cout << "Nasabah berhasil dihapus." << endl;
            return;
        }
    }

    cout << "Nasabah dengan ID tersebut tidak ditemukan." << endl;
}

// fungsi untuk melihat daftar nasabah 
void Bank :: lihatDaftarNasabah() {
    if (daftarNasabah.empty()) {
        cout << "Belum ada nasabah yang terdaftar." << endl;
        return;
    }

    cout << "----- DAFTAR NASABAH -----" << endl;
    
    for (const Nasabah& nasabah : daftarNasabah) {
        nasabah.lihatInformasiPribadi();
        cout << "-------------------------" << endl;
    }
}

// fungsi untuk mencari nasabah berdasarkan ID 
Nasabah* Bank :: cariNasabah(const string& idNasabah) {
    for (Nasabah& nasabah : daftarNasabah) {
        if (nasabah.getIdNasabah() == idNasabah) {
            return &nasabah; 
        }
    }

    return nullptr; 
}

// getter daftar nasabah
const vector<Nasabah>& Bank :: getDaftarNasabah() const {
    return daftarNasabah;
}
