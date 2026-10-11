#ifndef NASABAH_H
#define NASABAH_H

#include <string>
using namespace std; 

class Rekening;

class Nasabah {
    private: 
        string idNasabah;
        string nama;
        string tanggalLahir;
        string alamat;
        string nomorTelepon;
        string email;
        Rekening* rekening;

    public: 
        Nasabah(string id, string nama, string tanggalLahir, string alamat, string nomorTelepon, string email); 

        ~Nasabah();

        void lihatInformasiPribadi();
        void lihatRekening();
        void perbaruiInformasiPribadi();

        void setRekening(Rekening* rekening);
};

#endif 