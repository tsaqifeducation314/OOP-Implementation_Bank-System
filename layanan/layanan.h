#ifndef LAYANAN_H
#define LAYANAN_H

#include "../bank/bank.h"
#include "../rekening/rekening.h"
#include "../transaksi/transaksi.h"
#include "../kartu/kartu.h"
#include <memory>
#include <vector>

// CLASS BANK 
class Bank; 

// CLASS NASABAH 
class Nasabah;

// CLASS AUTENTIKASI
class Autentikasi;

// CLASS LAYANAN BANK 
class LayananBank {
    private:
        Bank bank; 
        Nasabah* nasabahAktif; 
        
        vector<unique_ptr<Rekening>> daftarRekening;
        vector<unique_ptr<Transaksi>> daftarTransaksi;
        vector<unique_ptr<KartuATM>> daftarKartu;
        
        Autentikasi* autentikasi; 

    public: 
        LayananBank(string namaBank);

        void registrasiNasabah(); 
        void ubahDataNasabah(); 
        void lihatDataNasabah();

        void buatRekening();
        void tutupRekening(); 
        void aktifkanRekening(); 

        void setor(); 
        void tarik();
        void transfer(); 

        void buatKartuATM(); 

        void setAutentikasi(Autentikasi* autentikasi);
};

#endif 