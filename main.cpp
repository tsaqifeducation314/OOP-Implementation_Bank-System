
#include <iostream>

#include "layanan/layanan.h"
#include "penyimpanan/penyimpanan.h"
#include "autentikasi/autentikasi.h"
#include "menu/menu.h"

using namespace std;

int main() {
    LayananBank layanan("Bank Indonesia");
    PenyimpananBank penyimpanan("data");
    Autentikasi autentikasi("admin", "admin123");

    layanan.setPenyimpanan(&penyimpanan);
    layanan.setAutentikasi(&autentikasi);

    cout << "===== SISTEM BANK INDONESIA =====" << endl;

    if (!penyimpanan.muatNasabah(layanan)) {
        cout << "Data nasabah belum tersedia atau gagal dimuat."
             << endl;
        return 1;
    }

    cout << "Data nasabah berhasil dimuat." << endl;

    if (penyimpanan.muatRekening(layanan)) {
        cout << "Data rekening berhasil dimuat." << endl;
    } else {
        cout << "Data rekening belum tersedia atau gagal dimuat."
             << endl;
    }

    if (penyimpanan.muatKartu(layanan)) {
        cout << "Data kartu ATM berhasil dimuat." << endl;
    } else {
        cout << "Data kartu ATM belum tersedia atau gagal dimuat."
             << endl;
    }

    if (penyimpanan.muatTransaksi(layanan)) {
        cout << "Data transaksi berhasil dimuat." << endl;
    } else {
        cout << "Data transaksi belum tersedia atau gagal dimuat."
             << endl;
    }

    MenuCLI menu(layanan, autentikasi, penyimpanan);
    menu.jalankan();

    return 0;
}
