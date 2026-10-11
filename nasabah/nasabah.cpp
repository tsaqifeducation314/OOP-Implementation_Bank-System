#include "nasabah.h"
#include "rekening.h"
#include <iostream> 
using namespace std; 

// constructor class nasabah 
Nasabah :: Nasabah(string id, string nama, string tanggalLahir, string alamat, string nomorTelepon, string email) {
    this->idNasabah = id; 
    this->nama = nama; 
    this->tanggalLahir = tanggalLahir; 
    this->alamat = alamat;
    this->nomorTelepon = nomorTelepon; 
    this->email = email;
    this->rekening = nullptr;
}

// fungsi untuk melihat informasi pribadi nasabah 
void Nasabah :: lihatInformasiPribadi() {
    cout << "ID Nasabah      : " << idNasabah << endl; 
    cout << "Nama            : " << nama << endl; 
    cout << "Tanggal Lahir   : " << tanggalLahir << endl; 
    cout << "Alamat          : " << alamat << endl; 
    cout << "Nomor Telepon   : " << nomorTelepon << endl; 
    cout << "Email           : " << email << endl;        
}

// fungsi untuk melihat rekening 
void Nasabah :: lihatRekening() {
    if (rekening == nullptr) {
        cout << "Nasabah belum memiliki rekening" << endl;
        return; 
    }

    rekening->lihatInformasiRekening(); 
}

// fungsi untuk memperbarui informasi pribadi nasabah 
void Nasabah :: perbaruiInformasiPribadi() {
    cout << "Alamat baru     : "; 
    getline(cin >> ws, alamat); 

    cout << "No telepon baru : "; 
    getline(cin, nomorTelepon); 

    cout << "Email baru      : "; 
    getline(cin, email); 

}

// setter untuk rekening 
void Nasabah :: setRekening(Rekening* rekening) {
    this->rekening = rekening; 
}