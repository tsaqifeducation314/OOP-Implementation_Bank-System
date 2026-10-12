
#include "menu.h"

#include "../nasabah/nasabah.h"
#include "../rekening/rekening.h"
#include "../kartu/kartu.h"
#include "../transaksi/transaksi.h"

#include <iostream>
#include <limits>

using namespace std;

MenuCLI::MenuCLI(
    LayananBank& layananBank,
    Autentikasi& autentikasi,
    PenyimpananBank& penyimpanan
) : layananBank(layananBank),
    autentikasi(autentikasi),
    penyimpanan(penyimpanan),
    running(true) {
}

void MenuCLI::tampilkanMenuUtama() {
    cout << "\n==================================" << endl;
    cout << "       SISTEM BANK INDONESIA      " << endl;
    cout << "==================================" << endl;
    cout << "1. Login Admin" << endl;
    cout << "2. Login Nasabah" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

void MenuCLI::jalankan() {
    while (running) {
        menuLogin();
    }
}

void MenuCLI::menuLogin() {
    int pilihan;

    tampilkanMenuUtama();

    if (!(cin >> pilihan)) {
        cout << "Input harus berupa angka." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilihan) {
        case 1: {
            string username;
            string password;

            cout << "\n===== LOGIN ADMIN =====" << endl;
            cout << "Username: ";
            getline(cin, username);

            cout << "Password: ";
            getline(cin, password);

            if (autentikasi.loginAdmin(username, password)) {
                menuAdmin();
                autentikasi.logout();
            }

            break;
        }

        case 2: {
            string nomorKartu;
            string pin;

            cout << "\n===== LOGIN NASABAH =====" << endl;
            cout << "Nomor Kartu: ";
            getline(cin, nomorKartu);

            cout << "PIN: ";
            getline(cin, pin);

            if (autentikasi.loginNasabah(nomorKartu, pin)) {
                menuNasabah();
                autentikasi.logout();
            }

            break;
        }

        case 0:
            simpanSemuaData();
            running = false;
            cout << "Program selesai. Terima kasih." << endl;
            break;

        default:
            cout << "Pilihan tidak tersedia." << endl;
    }
}
    
void MenuCLI::menuAdmin() {
    int pilihan;
    bool sesiAktif = true;

    while (sesiAktif &&
           autentikasi.getStatusLogin() &&
           autentikasi.getStatusAdmin()) {

        cout << "\n==================================" << endl;
        cout << "           MENU ADMIN             " << endl;
        cout << "==================================" << endl;
        cout << "1. Nasabah" << endl;
        cout << "2. Rekening" << endl;
        cout << "3. ATM" << endl;
        cout << "4. Transaksi" << endl;
        cout << "5. Simpan Semua Data" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize> :: max(), '\n');

        switch (pilihan) {
            case 1:
                menuNasabahAdmin();
                break;

            case 2:
                menuRekeningAdmin();
                break;

            case 3:
                menuATMAdmin();
                break;

            case 4:
                menuTransaksiAdmin();
                break;

            case 5:
                simpanSemuaData();
                break;

            case 0:
                simpanSemuaData();
                sesiAktif = false;
                cout << "Logout admin berhasil." << endl;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}


void MenuCLI::menuNasabahAdmin() {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n========== MENU NASABAH ==========" << endl;
        cout << "1. Registrasi Nasabah" << endl;
        cout << "2. Lihat Daftar Nasabah" << endl;
        cout << "3. Lihat Data Nasabah" << endl;
        cout << "4. Ubah Data Nasabah" << endl;
        cout << "5. Hapus Nasabah" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                layananBank.registrasiNasabah();
                penyimpanan.simpanNasabah(layananBank);
                break;

            case 2:
                layananBank.getBank().lihatDaftarNasabah();
                break;

            case 3:
                layananBank.lihatDataNasabah();
                break;

            case 4:
                layananBank.ubahDataNasabah();
                penyimpanan.simpanNasabah(layananBank);
                break;

            case 5: {
                string idNasabah;

                cout << "ID Nasabah yang akan dihapus: ";
                getline(cin, idNasabah);

                layananBank.getBank().hapusNasabah(idNasabah);
                simpanSemuaData();
                break;
            }

            case 0:
                kembali = true;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}


void MenuCLI::menuRekeningAdmin() {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n========== MENU REKENING ==========" << endl;
        cout << "1. Buat Rekening" << endl;
        cout << "2. Lihat Daftar Rekening" << endl;
        cout << "3. Tutup Rekening" << endl;
        cout << "4. Aktifkan Rekening" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                layananBank.buatRekening();
                penyimpanan.simpanNasabah(layananBank);
                penyimpanan.simpanRekening(layananBank);
                break;

            case 2:
                lihatDaftarRekening();
                break;

            case 3:
                layananBank.tutupRekening();
                penyimpanan.simpanRekening(layananBank);
                break;

            case 4:
                layananBank.aktifkanRekening();
                penyimpanan.simpanRekening(layananBank);
                break;

            case 0:
                kembali = true;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}


void MenuCLI::lihatDaftarRekening() {
    const auto& daftarRekening = layananBank.getDaftarRekening();

    cout << "\n========== DAFTAR REKENING ==========" << endl;

    if (daftarRekening.empty()) {
        cout << "Belum ada rekening." << endl;
        return;
    }

    for (const auto& rekening : daftarRekening) {
        if (rekening != nullptr) {
            rekening->lihatInformasiRekening();
            cout << "------------------------------------" << endl;
        }
    }
}


void MenuCLI::menuATMAdmin() {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n============= MENU ATM =============" << endl;
        cout << "1. Buat Kartu ATM" << endl;
        cout << "2. Lihat Daftar Kartu ATM" << endl;
        cout << "3. Ubah PIN Kartu" << endl;
        cout << "4. Blokir Kartu ATM" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                layananBank.buatKartuATM();
                penyimpanan.simpanKartu(layananBank);
                break;

            case 2:
                lihatDaftarKartu();
                break;

            case 3: {
                string nomorKartu;
                string pinLama;
                string pinBaru;

                cout << "Nomor kartu: ";
                getline(cin, nomorKartu);

                cout << "PIN lama: ";
                getline(cin, pinLama);

                cout << "PIN baru: ";
                getline(cin, pinBaru);

                bool ditemukan = false;

                for (const auto& kartu : layananBank.getDaftarKartu()) {
                    if (kartu != nullptr &&
                        kartu->getNomorKartu() == nomorKartu) {
                        ditemukan = true;

                        if (kartu->ubahPIN(pinLama, pinBaru)) {
                            if (penyimpanan.simpanKartu(layananBank)) {
                                cout << "PIN berhasil diubah." << endl;
                            } else {
                                cout << "PIN berubah, tetapi penyimpanan gagal." << endl;
                            }
                        } else {
                            cout << "PIN lama salah atau PIN gagal diubah." << endl;
                        }

                        break;
                    }
                }

                if (!ditemukan) {
                    cout << "Kartu tidak ditemukan." << endl;
                }

                break;
            }

            case 4: {
                string nomorKartu;
                bool ditemukan = false;

                cout << "Nomor kartu yang akan diblokir: ";
                getline(cin, nomorKartu);

                for (const auto& kartu : layananBank.getDaftarKartu()) {
                    if (kartu != nullptr &&
                        kartu->getNomorKartu() == nomorKartu) {
                        ditemukan = true;

                        kartu->blokirKartu();
                        penyimpanan.simpanKartu(layananBank);

                        cout << "Proses pemblokiran selesai." << endl;
                        break;
                    }
                }

                if (!ditemukan) {
                    cout << "Kartu tidak ditemukan." << endl;
                }

                break;
            }

            case 0:
                kembali = true;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}


void MenuCLI::lihatDaftarKartu() {
    const auto& daftarKartu = layananBank.getDaftarKartu();

    cout << "\n========== DAFTAR KARTU ATM ==========" << endl;

    if (daftarKartu.empty()) {
        cout << "Belum ada kartu ATM." << endl;
        return;
    }

    for (const auto& kartu : daftarKartu) {
        if (kartu == nullptr) {
            continue;
        }

        cout << "Nomor Kartu       : "
             << kartu->getNomorKartu() << endl;

        cout << "Tanggal Terbit    : "
             << kartu->getTanggalTerbit() << endl;

        cout << "Tanggal Kedaluwarsa: "
             << kartu->getTanggalKadaluarsa() << endl;

        cout << "Status            : "
             << (kartu->getStatusKartu() ? "Aktif" : "Terblokir")
             << endl;

        Rekening* rekening = kartu->getRekening();

        if (rekening != nullptr) {
            cout << "Nomor Rekening    : "
                 << rekening->getNomorRekening() << endl;
        }

        cout << "--------------------------------------" << endl;
    }
}


void MenuCLI::menuTransaksiAdmin() {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n========== MENU TRANSAKSI ==========" << endl;
        cout << "1. Setor Tunai" << endl;
        cout << "2. Tarik Tunai" << endl;
        cout << "3. Transfer" << endl;
        cout << "4. Lihat Daftar Transaksi" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                layananBank.setor();
                break;

            case 2:
                layananBank.tarik();
                break;

            case 3:
                layananBank.transfer();
                break;

            case 4: {
                const auto& daftarTransaksi =
                    layananBank.getDaftarTransaksi();

                cout << "\n========== DAFTAR TRANSAKSI ==========" << endl;

                if (daftarTransaksi.empty()) {
                    cout << "Belum ada transaksi." << endl;
                    break;
                }

                for (const auto& transaksi : daftarTransaksi) {
                    if (transaksi != nullptr) {
                        transaksi->lihatDetailTransaksi();
                        cout << "--------------------------------------" << endl;
                    }
                }

                break;
            }

            case 0:
                kembali = true;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}

void MenuCLI::menuNasabah() {
    KartuATM* kartu = autentikasi.getKartuAktif();

    if (kartu == nullptr || !kartu->getStatusKartu()) {
        cout << "Kartu tidak tersedia atau sudah diblokir." << endl;
        return;
    }

    Rekening* rekening = kartu->getRekening();

    if (rekening == nullptr) {
        cout << "Kartu tidak terhubung dengan rekening." << endl;
        return;
    }

    string idNasabah = rekening->getNama();
    Nasabah* nasabah =
        layananBank.getBank().cariNasabah(idNasabah);

    if (nasabah == nullptr) {
        cout << "Data nasabah tidak ditemukan." << endl;
        return;
    }

    int pilihan;
    bool sesiAktif = true;

    while (sesiAktif && autentikasi.getStatusLogin()
           && !autentikasi.getStatusAdmin()) {
        cout << "\n========= MENU NASABAH =========" << endl;
        cout << "Selamat datang, " << nasabah->getNama() << endl;
        cout << "1. Lihat Informasi Pribadi" << endl;
        cout << "2. Lihat Rekening" << endl;
        cout << "3. Perbarui Informasi Pribadi" << endl;
        cout << "4. Ubah PIN ATM" << endl;
        cout << "5. Lihat Riwayat Transaksi" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                nasabah->lihatInformasiPribadi();
                break;

            case 2:
                nasabah->lihatRekening();
                break;

            case 3:
                nasabah->perbaruiInformasiPribadi();
                penyimpanan.simpanNasabah(layananBank);
                break;

            case 4:
                ubahPINNasabah();
                break;

            case 5:
                lihatTransaksiNasabah();
                break;

            case 0:
                sesiAktif = false;
                cout << "Logout nasabah berhasil." << endl;
                break;

            default:
                cout << "Pilihan tidak tersedia." << endl;
        }
    }
}

void MenuCLI::ubahPINNasabah() {
    KartuATM* kartu = autentikasi.getKartuAktif();

    if (kartu == nullptr) {
        cout << "Tidak ada kartu yang aktif." << endl;
        return;
    }

    string pinLama;
    string pinBaru;
    string konfirmasiPIN;

    cout << "\n========== UBAH PIN ==========" << endl;
    cout << "PIN lama: ";
    getline(cin, pinLama);

    cout << "PIN baru (6 digit): ";
    getline(cin, pinBaru);

    cout << "Konfirmasi PIN baru: ";
    getline(cin, konfirmasiPIN);

    if (pinBaru.length() != 6) {
        cout << "PIN baru harus terdiri dari 6 digit." << endl;
        return;
    }

    for (char digit : pinBaru) {
        if (digit < '0' || digit > '9') {
            cout << "PIN baru hanya boleh berisi angka." << endl;
            return;
        }
    }

    if (pinBaru != konfirmasiPIN) {
        cout << "Konfirmasi PIN tidak cocok." << endl;
        return;
    }

    if (kartu->ubahPIN(pinLama, pinBaru)) {
        if (penyimpanan.simpanKartu(layananBank)) {
            cout << "PIN berhasil diubah dan disimpan." << endl;
        } else {
            cout << "PIN berubah, tetapi penyimpanan gagal." << endl;
        }
    } else {
        cout << "PIN lama salah atau PIN gagal diubah." << endl;
    }
}

void MenuCLI::lihatTransaksiNasabah() {
    KartuATM* kartu = autentikasi.getKartuAktif();

    if (kartu == nullptr || kartu->getRekening() == nullptr) {
        cout << "Rekening tidak tersedia." << endl;
        return;
    }

    Rekening* rekening = kartu->getRekening();
    bool ditemukan = false;

    cout << "\n===== RIWAYAT TRANSAKSI =====" << endl;

    for (const auto& transaksi :
         layananBank.getDaftarTransaksi()) {
        bool terkaitRekening =
            transaksi->getRekening() == rekening ||
            transaksi->getRekeningPengirim() == rekening ||
            transaksi->getRekeningPenerima() == rekening;

        if (terkaitRekening) {
            transaksi->lihatDetailTransaksi();
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Belum ada transaksi untuk rekening ini." << endl;
    }
}

void MenuCLI::simpanSemuaData() {
    bool nasabahTersimpan = penyimpanan.simpanNasabah(layananBank);
    bool rekeningTersimpan = penyimpanan.simpanRekening(layananBank);
    bool kartuTersimpan = penyimpanan.simpanKartu(layananBank);
    bool transaksiTersimpan = penyimpanan.simpanTransaksi(layananBank);

    if (nasabahTersimpan && rekeningTersimpan &&
        kartuTersimpan && transaksiTersimpan) {
        cout << "Semua data berhasil disimpan." << endl;
    } else {
        cout << "Peringatan: sebagian data gagal disimpan." << endl;
    }
}
