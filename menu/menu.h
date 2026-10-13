
#ifndef MENU_H
#define MENU_H

#include <string>
#include "../layanan/layanan.h"
#include "../autentikasi/autentikasi.h"
#include "../penyimpanan/penyimpanan.h"

using namespace std;

class MenuCLI {
private:
    LayananBank& layananBank;
    Autentikasi& autentikasi;
    PenyimpananBank& penyimpanan;
    bool running;

    void menuLogin();
    void menuAdmin();
    void menuNasabah();

    void menuNasabahAdmin();
    void menuRekeningAdmin();
    void menuATMAdmin();
    void menuTransaksiAdmin();

    void menuTransaksiNasabah();

    void lihatDaftarRekening();
    void lihatDaftarKartu();
    void ubahPINNasabah();
    void lihatTransaksiNasabah();
    void simpanSemuaData();
    void tampilkanMenuUtama();

public:
    MenuCLI(
        LayananBank& layananBank,
        Autentikasi& autentikasi,
        PenyimpananBank& penyimpanan
    );

    void jalankan();
};

#endif
