#ifndef LAYANAN_H
#define LAYANAN_H

#include "../bank/bank.h"
#include "../rekening/rekening.h"
#include "../transaksi/transaksi.h"
#include "../kartu/kartu.h"
#include "../penyimpanan/penyimpanan.h"

#include <memory>
#include <vector>

using namespace std;

// CLASS PENYIMPANAN BANK
class PenyimpananBank;

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

        PenyimpananBank* penyimpanan;

    public: 
        LayananBank(string namaBank);

        Bank& getBank();
        const Bank& getBank() const;

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
        void setPenyimpanan(PenyimpananBank* penyimpanan);
        const vector<unique_ptr<Rekening>>& getDaftarRekening() const;
        const vector<unique_ptr<KartuATM>>& getDaftarKartu() const;

        const vector<unique_ptr<Transaksi>>& getDaftarTransaksi() const;

        void tambahRekeningTersimpan(unique_ptr<Rekening> rekening);
        void tambahKartuTersimpan(unique_ptr<KartuATM> kartu);
        void tambahTransaksiTersimpan(unique_ptr<Transaksi> transaksi);
};

#endif 