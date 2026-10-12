#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <string>
using namespace std;

// CLASS REKENING 
class Rekening; 

// CLASS TRANSAKSI 
class Transaksi {
    private: 
        string idTransaksi; 
        string tanggal; 
        double jumlah;
        string jenis;
        string status; 
        string keterangan; 

        Rekening* rekening; 
        Rekening* rekeningPengirim; 
        Rekening* rekeningPenerima; 
    
    public: 
        Transaksi(string id, string tanggal, double nominal, string tipe, string status, string keterangan);
        
        void lihatDetailTransaksi();

        void setRekening(Rekening* rekening);
        void setRekeningPengirim(Rekening* rekening);
        void setRekeningPenerima(Rekening* rekening);
        string getIdTransaksi() const;
        string getTanggal() const;
        double getJumlah() const;
        string getJenis() const;
        string getStatus() const;
        string getKeterangan() const;
        Rekening* getRekening() const;
        Rekening* getRekeningPengirim() const;
        Rekening* getRekeningPenerima() const;
};

#endif