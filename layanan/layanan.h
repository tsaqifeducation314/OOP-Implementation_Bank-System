#ifndef LAYANAN_H
#define LAYANAN_H

#include "../bank/bank.h"

// CLASS BANK 
class Bank; 

// CLASS NASABAH 
class Nasabah;

// CLASS LAYANAN BANK 
class LayananBank {
    private:
        Bank bank; 
        Nasabah* nasabahAktif; 

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
};

#endif 