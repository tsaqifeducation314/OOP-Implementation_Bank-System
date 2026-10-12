#ifndef BANK_H
#define BANK_H

#include "../nasabah/nasabah.h"
#include <string>
#include <vector>
using namespace std; 


// CLASS BANK 
class Bank {
    private: 
        string namaBank;
        vector<Nasabah> daftarNasabah; 
    
    public: 
        Bank(string nama);

        void tambahNasabah(const Nasabah& nasabah);
        void hapusNasabah(const string& idNasabah);
        void lihatDaftarNasabah();

        Nasabah* cariNasabah(const string& idNasabah);

        const vector<Nasabah>& getDaftarNasabah() const;
};

#endif