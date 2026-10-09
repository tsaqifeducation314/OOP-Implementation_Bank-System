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
        RekeningTabungan(string pemilik, string nomor, string tanggal, double saldoAwal);

        double hitungBunga() override;
        void lihatInformasiRekening() override;

    private:
        double sukuBunga = 0.5; 
        double saldoMinimum = 50000; 
};

// CHILD CLASS REKENING GIRO 
class RekeningGiro : public Rekening {
    public: 
        RekeningGiro(string pemilik, string nomor, string tanggal, double saldoAwal);

        bool bayarBiayaAdministrasi();
        void lihatInformasiRekening() override;

    private: 
        double biayaAdministrasi = 180000;
};


// CHILD CLASS REKENING DEPOSITO 
class RekeningDeposito : public Rekening {
        public: 
            RekeningDeposito(string pemilik, string nomor, string tanggal, double saldoAwal);

            double hitungBunga() override;
            bool cekJatuhTempo();
            void lihatInformasiRekening() override;

        private:
            double nominalAwal; 
            int jangkaWaktu;
            double sukuBunga = 5; 
            string tanggalJatuhTempo; 
};

#endif