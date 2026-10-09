#ifndef REKENING_H
#define REKENING_H

#include <string>
using namespace std; 

// PARENT CLASS REKENING
class Rekening {
    public: 
        Rekening(string pemilik, string nomor, string tanggal, double saldoAwal);

        double lihatSaldo();
        virtual void lihatInformasiRekening();
        void ubahStatus();
        virtual double hitungBunga();

        virtual ~Rekening() {};

    private:
        string nomorRekening; 
        string tanggalDibuka;

    protected:
        double saldo;
        bool statusRekening; 
        string nama; 

        bool validasiStatusAktif();
};

// CHILD CLASS REKENING TABUNGAN 
class RekeningTabungan : public Rekening {
    public: 
        RekeningTabungan::RekeningTabungan(string pemilik, string nomor, string tanggal, double saldoAwal);

        double hitungBunga() override;
        void lihatInformasiRekening() override;

    private:
        double sukuBunga = 0.5; 
        double saldoMinimum = 50000; 
};

#endif