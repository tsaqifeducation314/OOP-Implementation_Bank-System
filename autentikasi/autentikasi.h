#ifndef AUTENTIKASI_H
#define AUTENTIKASI_H

#include <string>
#include <vector>

using namespace std;

// CLASS KARTU ATM  
class KartuATM;

// CLASS AUTENTIKASI
class Autentikasi {
    private:
        vector<KartuATM*> daftarKartu;
        string usernameAdmin;
        string passwordAdmin;

        KartuATM* kartuAktif;
        bool adminAktif;

    public:
        Autentikasi(string usernameAdmin, string passwordAdmin);

        void daftarkanKartu(KartuATM* kartu);
        
        bool loginNasabah(const string& nomorKartu, const string& pin);
        bool loginAdmin(const string& username, const string& password);
        void logout();

        bool getStatusLogin() const;
        KartuATM* getKartuAktif() const;
        bool getStatusAdmin() const;
};

#endif