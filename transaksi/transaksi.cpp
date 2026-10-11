#include "transaksi.h"
#include "../rekening/rekening.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std; 

// constructor class transaksi 
Transaksi :: Transaksi(string id, string tanggal, double nominal, string tipe, string status, string keterangan) {
    this->idTransaksi = id; 
    this->tanggal = tanggal; 
    this->jumlah = nominal; 
    this->jenis = tipe; 
    this->status = status; 
    this->keterangan = keterangan; 

    this->rekening = nullptr; 
    this->rekeningPengirim = nullptr; 
    this->rekeningPenerima = nullptr; 
}

// fungsi untuk melihat detail transaksi 
void Transaksi :: lihatDetailTransaksi() {
    cout << "----- DETAIL TRANSAKSI -----" << endl;
    cout << "ID Transaksi     : " << idTransaksi << endl;
    cout << "Tanggal          : " << tanggal << endl;
    cout << "Jenis            : " << jenis << endl;
    cout << "Jumlah           : " << fixed << setprecision(2)
         << jumlah << endl;
    cout << "Status           : " << status << endl;
    cout << "Keterangan       : " << keterangan << endl;

    if (jenis == "1" || jenis == "2") {
        if (rekening != nullptr) {
            cout << "Nomor Rekening   : "
                 << rekening->getNomorRekening() << endl;
        } else {
            cout << "Rekening terkait belum terhubung." << endl;
        }

    } else if (jenis == "3") {
        if (rekeningPengirim != nullptr) {
            cout << "Rekening Pengirim: "
                 << rekeningPengirim->getNomorRekening() << endl;
        } else {
            cout << "Rekening pengirim belum terhubung." << endl;
        }

        if (rekeningPenerima != nullptr) {
            cout << "Rekening Penerima: "
                 << rekeningPenerima->getNomorRekening() << endl;
        } else {
            cout << "Rekening penerima belum terhubung." << endl;
        }
    }

    cout << "-----------------------------" << endl;
}

// setter untuk rekening 
void Transaksi :: setRekening(Rekening* rekening) {
    this->rekening = rekening; 
}

// setter untuk rekening 
void Transaksi :: setRekeningPengirim(Rekening* rekeningPengirim) {
    this->rekeningPengirim = rekeningPengirim; 
}

// setter untuk rekening penerima
void Transaksi :: setRekeningPenerima(Rekening* rekeningPenerima) {
    this->rekeningPenerima = rekeningPenerima; 
}

