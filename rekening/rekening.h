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
        RekeningTabungan :: RekeningTabungan(string pemilik, string nomor, string tanggal, double saldoAwal);

        double hitungBunga() override;
        void lihatInformasiRekening() override;

    private:
        double sukuBunga = 0.5; 
        double saldoMinimum = 50000; 
};

// CHILD CLASS REKENING GIRO 
class RekeningGiro : public Rekening {
    public: 
        RekeningGiro :: RekeningGiro(string pemilik, string nomor, string tanggal, double saldoAwal);

        bool bayarBiayaAdministrasi();
        void lihatInformasiRekening();

    private: 
        double biayaAdministrasi = 180000;
};


// CHILD CLASS REKENING DEPOSITO 
class RekeningDeposito : public Rekening {
        public: 
            RekeningDeposito :: RekeningDeposito(string pemilik, string nomor, string tanggal, double saldoAwal);

            double hitungBunga();
            bool cekJatuhTempo();
            void lihatInformasiRekening();

        private:
            double nominalAwal; 
            int jangkaWaktu;
            double sukuBunga = 5; 
            string tanggalJatuhTempo; 
};

#endif