#ifndef KARTU_H
#define KARTU_H

#include <string>
using namespace std;

// CLASS REKENING 
class Rekening;

// CLASS KARTU ATM
class KartuATM {
private:
    string nomorKartu;
    string tanggalTerbit;
    string tanggalKadaluarsa;
    string pin;
    bool status;
    int percobaanPIN;
    Rekening* rekening;

public:
    KartuATM(string nomorKartu,
             string tanggalTerbit,
             string tanggalKadaluarsa,
             string pin,
             Rekening* rekening);

    bool verifikasiPIN(const string& pinInput);

    bool ubahPIN(const string& pinLama,
                 const string& pinBaru);

    void blokirKartu();

    string getNomorKartu() const;
    bool getStatusKartu() const;
    Rekening* getRekening() const;
    string getTanggalTerbit() const;
    string getTanggalKadaluarsa() const;
    string getPIN() const;
    int getPercobaanPIN() const;

    void setStatusKartu(bool status);
    void setPercobaanPIN(int percobaan);
};

#endif