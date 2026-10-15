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
        virtual double hitungBunga();

        virtual ~Rekening() {};

        string getNomorRekening() const; 
        bool getStatusRekening() const; 
        void setStatusRekening(bool status);
        string getNama() const;
        string getTanggalDibuka() const;
        double getSaldo() const;

        virtual bool setorDana(double jumlah);
        virtual bool tarikDana(double jumlah);

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
        double biayaAdministrasi = 600000;
};


// CHILD CLASS REKENING DEPOSITO 
class RekeningDeposito : public Rekening {
        public: 
            RekeningDeposito(string pemilik, string nomor, string tanggal, double saldoAwal);

            double hitungBunga() override;
            void lihatInformasiRekening() override;

        private:
            double nominalAwal; 
            int jangkaWaktu = 1;
            double sukuBunga = 5; 
            string tanggalJatuhTempo; 
};

#endif