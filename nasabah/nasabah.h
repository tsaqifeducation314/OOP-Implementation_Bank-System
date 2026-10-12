#ifndef NASABAH_H
#define NASABAH_H

#include <string>
using namespace std; 

// CLASS REKENING
class Rekening;

// CLASS NASABAH
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

        void lihatInformasiPribadi() const;
        void lihatRekening();
        void perbaruiInformasiPribadi();

        void setRekening(Rekening* rekening);
        string getIdNasabah() const;
        string getNama() const;
        string getTanggalLahir() const;
        string getAlamat() const;
        string getNomorTelepon() const;
        string getEmail() const;
        Rekening* getRekening() const;
};

#endif 