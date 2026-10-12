#include "rekening.h"
#include <iostream>
using namespace std;

// PARENT CLASS REKENING  

//constructor class rekening 
Rekening :: Rekening(string pemilik, string nomor, string tanggal, double saldoAwal) {
    nama = pemilik;
    nomorRekening = nomor;
    tanggalDibuka = tanggal;
    saldo = saldoAwal;
    statusRekening = true;
}

// fungsi untuk melihat saldo
double Rekening :: lihatSaldo() {
    return saldo;
}

// fungsi untuk melihat informasi rekening 
void Rekening :: lihatInformasiRekening() {
    cout << "Nama            : " << nama << endl;
    cout << "Nomor Rekening  : " << nomorRekening << endl;
    cout << "Tanggal Dibuka  : " << tanggalDibuka << endl;
    cout << "Status Rekening : ";
    if (statusRekening == true) {
        cout << "Aktif" << endl;
    } else {
        cout << "Tidak Aktif" << endl;
    }
    cout << "Saldo           : " << saldo << endl; 
}

// fungsi untuk mengubah status rekening 
void Rekening :: ubahStatus() {
    statusRekening = !statusRekening;
}

// fungsi untuk menghitung bunga tahunan, bernilai 0 karena 
double Rekening :: hitungBunga() {
    return 0;
}

// fungsi untuk memvalidasi status aktif rekening 
bool Rekening :: validasiStatusAktif() {
    return statusRekening;
}

// fungsi untuk menampilkan ringkasan rekening 
void tampilkanRingkasanRekening(const Rekening& rekening) {
     cout << "Nomor Rekening  : " << rekening.nomorRekening << endl;
     cout << "Saldo           : " << rekening.saldo << endl;
     cout << "Status          : " << rekening.statusRekening << endl;
}

// getter untuk nomor rekening 
string Rekening :: getNomorRekening() const {
    return nomorRekening;
}


// CHILD CLASS REKENING TABUNGAN 

// constructor class rekening tabungan
RekeningTabungan :: RekeningTabungan(string pemilik, string nomor, string tanggal, double saldoAwal) : Rekening(pemilik, nomor, tanggal, saldoAwal) {}

// fungsi untuk menghitung bunga tahunan pada rekening tabungan 
double RekeningTabungan::hitungBunga() {
    return saldo * sukuBunga / 100;
}

// fungsi untuk melihat informasi rekening tabungan  
void RekeningTabungan :: lihatInformasiRekening() {
    Rekening :: lihatInformasiRekening();
    cout << "Suku Bunga      : " << sukuBunga << endl;
    cout << "Saldo Minimum   : " << saldoMinimum << endl;
}


// CHILD CLASS REKENING GIRO 

// constructor class rekening giro 
RekeningGiro :: RekeningGiro(string pemilik, string nomor, string tanggal, double saldoAwal) : Rekening(pemilik, nomor, tanggal, saldoAwal) {}

// fungsi untuk menghitung biaya administrasi yang harus dibayarkan
bool RekeningGiro :: bayarBiayaAdministrasi() {
    if (!validasiStatusAktif()) {
        return false;
    }
    if (lihatSaldo() < biayaAdministrasi) {
        return false; 
    }
    saldo -= biayaAdministrasi;
    return true;
}

// fungsi untuk melihat informasi rekening giro  
void RekeningGiro :: lihatInformasiRekening() {
    Rekening :: lihatInformasiRekening();
    cout << "Biaya Admin     : " << biayaAdministrasi << endl;
}


// CHILD CLASS REKENING DEPOSITO 

// constructor class rekening giro 
RekeningDeposito :: RekeningDeposito(string pemilik, string nomor, string tanggal, double saldoAwal) : Rekening(pemilik, nomor, tanggal, saldoAwal) {}

// fungsi untuk menghitung bunga tahunan pada rekening tabungan
double RekeningDeposito :: hitungBunga() {
    return saldo * sukuBunga / 100;
}

// fungsi untuk melihat informasi rekening deposito  
void RekeningDeposito :: lihatInformasiRekening() {
    Rekening :: lihatInformasiRekening();
    cout << "Nominal Awal    : " << nominalAwal << endl; 
    cout << "Jangka Waktu    : " << jangkaWaktu << endl; 
    cout << "Suku Bunga      : " << sukuBunga << endl;
    cout << "Jatuh Tempo     : " << tanggalJatuhTempo << endl;
}

// fungsi untuk setor dana 
bool Rekening :: setorDana(double jumlah) {
    if (!statusRekening) {
        cout << "Rekening tidak aktif." << endl;
        return false;
    }

    if (jumlah <= 0) {
        cout << "Jumlah setoran harus lebih dari nol." << endl;
        return false;
    }

    saldo += jumlah;
    cout << "Setoran berhasil." << endl;
    return true;
}

// fungsi untuk tarik dana 
bool Rekening :: tarikDana(double jumlah) {
    if (!statusRekening) {
        cout << "Rekening tidak aktif." << endl;
        return false;
    }

    if (jumlah <= 0) {
        cout << "Jumlah penarikan harus lebih dari nol." << endl;
        return false;
    }

    if (jumlah > saldo) {
        cout << "Saldo tidak mencukupi." << endl;
        return false;
    }

    saldo -= jumlah;
    cout << "Penarikan berhasil." << endl;
    return true;
}

// getter status rekening
bool Rekening :: getStatusRekening() const {
    return statusRekening;
}

// setter status rekening 
void Rekening :: setStatusRekening(bool status) {
    statusRekening = status;
}

// getter untuk nama
string Rekening :: getNama() const {
    return nama;
}

// getter untuk tanggal buka 
string Rekening :: getTanggalDibuka() const {
    return tanggalDibuka;
}

// getter untuk saldo 
double Rekening :: getSaldo() const {
    return saldo;
}