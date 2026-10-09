#ifndef REKENING_H
#define REKENING_H

#include <string>
using namespace std; 

// class induk rekening 
class Rekening {
    public: 
        Rekening(string pemilik, string nomor, string tanggal, double saldoAwal);

        double lihatSaldo();
        void lihatInformasiRekening();
        void ubahStatus();
        double hitungBunga();

    private:
        string nomorRekening; 
        string tanggalDibuka;

    protected:
        double saldo;
        bool statusRekening; 
        string nama; 

        bool validasiStatusAktif();
};

#endif