#include "layanan.h"
#include "../nasabah/nasabah.h"

#include <iostream>
#include <string>
#include <limits>
#include <memory>

using namespace std;

// constructor class layanan bank 
LayananBank :: LayananBank(string namaBank)
    : bank(namaBank), nasabahAktif(nullptr) {
}

// fungsi registrasi nasabah
void LayananBank :: registrasiNasabah() {
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
void LayananBank :: lihatDataNasabah() {
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
void LayananBank :: ubahDataNasabah() {
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

// fungsi untuk membuat rekening 
void LayananBank::buatRekening() {
    string idNasabah;
    string jenisRekening;
    string nomorRekening;
    string tanggalDibuka;
    double saldoAwal;

    cout << "\n----- PEMBUKAAN REKENING -----" << endl;
    cout << "ID Nasabah: ";
    getline(cin >> ws, idNasabah);

    Nasabah* nasabah = bank.cariNasabah(idNasabah);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    if (nasabah->getRekening() != nullptr) {
        cout << "Nasabah sudah memiliki rekening." << endl;
        return;
    }

    cout << "\nPilih jenis rekening:" << endl;
    cout << "1. Rekening Tabungan" << endl;
    cout << "2. Rekening Giro" << endl;
    cout << "3. Rekening Deposito" << endl;
    cout << "Pilihan: ";
    getline(cin, jenisRekening);

    if (jenisRekening != "1" &&
        jenisRekening != "2" &&
        jenisRekening != "3") {
        cout << "Jenis rekening tidak valid." << endl;
        return;
    }

    cout << "Nomor Rekening: ";
    getline(cin, nomorRekening);

    cout << "Tanggal Pembukaan (DD-MM-YYYY): ";
    getline(cin, tanggalDibuka);

    cout << "Saldo Awal: ";
    if (!(cin >> saldoAwal) || saldoAwal < 0) {
        cout << "Saldo awal tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize> :: max(), '\n');

    unique_ptr<Rekening> rekeningBaru;

    if (jenisRekening == "1") {
        rekeningBaru = make_unique<RekeningTabungan>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    } else if (jenisRekening == "2") {
        rekeningBaru = make_unique<RekeningGiro>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    } else {
        rekeningBaru = make_unique<RekeningDeposito>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    }

    Rekening* ptrRekening = rekeningBaru.get();

    daftarRekening.push_back(move(rekeningBaru));
    nasabah->setRekening(ptrRekening);

    cout << "\nRekening berhasil dibuat!" << endl;
    ptrRekening->lihatInformasiRekening();
}
