#ifndef REKENING_H
#define REKENING_H

#include <string>
using namespace std; 

// class induk rekening 
class Rekening {
    public: 
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
        string pemilik; 

        bool validasiStatusAktif();
};

#endif