
#ifndef PENYIMPANAN_H
#define PENYIMPANAN_H

#include <string>

using namespace std;

// CLASS LAYANAN BANK
class LayananBank;

// CLASS PENYIMPANAN BANK 
class PenyimpananBank {
    private:
        string folderData;

    public:
        PenyimpananBank(const string& folder = "data");

        bool simpanNasabah(const LayananBank& layanan);
        bool simpanRekening(const LayananBank& layanan);
        bool simpanKartu(const LayananBank& layanan);
        bool simpanTransaksi(const LayananBank& layanan);

        bool simpanSemuaData(const LayananBank& layanan);

        bool muatNasabah(LayananBank& layanan);
        bool muatRekening(LayananBank& layanan);
        bool muatKartu(LayananBank& layanan);
        bool muatTransaksi(LayananBank& layanan);
        bool muatSemuaData(LayananBank& layanan);
};

#endif
