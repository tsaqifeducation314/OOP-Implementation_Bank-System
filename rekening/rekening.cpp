#include "rekening.h"
#include <iostream>
using namespace std;

// fungsi untuk melihat saldo
double Rekening::lihatSaldo() {
    return saldo;
}

// fungsi untuk melihat informasi rekening 
void Rekening::lihatInformasiRekening() {
    cout << "Nomor           : " << nomorRekening << endl;
    cout << "Tanggal Dibuka  : " << tanggalDibuka << endl;
    cout << "Status Rekening : " << boolalpha << statusRekening << endl;
    cout << "Saldo           : " << saldo << endl; 
}

// fungsi untuk mengubah status rekening 
void Rekening::ubahStatus() {
    statusRekening = !statusRekening;
}

// fungsi untuk menghitung bunga tahunan dengan asumsi suku bunga 0.5%  
double Rekening::hitungBunga() {
    return saldo * 0.5 / 100;
}

// fungsi untuk memvalidasi status aktif rekening 
bool Rekening::validasiStatusAktif() {
    return statusRekening;
}