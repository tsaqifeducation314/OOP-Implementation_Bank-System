#include "layanan.h"
#include "../nasabah/nasabah.h"
#include "../autentikasi/autentikasi.h"
#include "../penyimpanan/penyimpanan.h"

#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <ctime>

using namespace std;

// constructor class layanan bank 
LayananBank :: LayananBank(string namaBank)
    : bank(namaBank), autentikasi(nullptr), penyimpanan(nullptr) {
}

// fungsi registrasi nasabah
void LayananBank :: registrasiNasabah() {
    string id;
    string nama;
    string tanggalLahir;
    string alamat;
    string nomorTelepon;
    string email;

    cout << endl;
    cout << "===== REGISTRASI NASABAH =====" << endl;

    int nomor = 1;

    do {
        id = "NS";
        if (nomor < 10) {
            id += "00";
        } else if (nomor < 100) {
            id += "0";
        }
        id += to_string(nomor);
        nomor++;
    } while (bank.cariNasabah(id) != nullptr);

    cout << "Nama             : ";
    getline(cin >> ws, nama);

    cout << "Tanggal Lahir    : ";
    getline(cin, tanggalLahir);

    cout << "Alamat           : ";
    getline(cin, alamat);

    cout << "Nomor Telepon    : ";
    getline(cin, nomorTelepon);

    cout << "Email            : ";
    getline(cin, email);

    Nasabah nasabah(
        id,
        nama,
        tanggalLahir,
        alamat,
        nomorTelepon,
        email
    );

    bank.tambahNasabah(nasabah);

    Nasabah* nasabahTerdaftar = bank.cariNasabah(id);

    if (nasabahTerdaftar == nullptr) {
        cout << "Registrasi nasabah gagal." << endl;
        return;
    }

    cout << endl;
    cout << "Nasabah berhasil ditambahkan." << endl;
    cout << "ID Nasabah       : " << id << endl;

    if (penyimpanan != nullptr) {
        if (penyimpanan->simpanNasabah(*this)) {
            cout << "Data nasabah berhasil disimpan." << endl;
        } else {
            cout << "Gagal menyimpan data nasabah." << endl;
        }
    }
}

// fungsi untuk melihat data nasabah
void LayananBank :: lihatDataNasabah() {
    string id;

    cout << endl;
    cout << "===== LIHAT DATA NASABAH =====" << endl;
    cout << "Masukkan ID Nasabah: ";
    getline(cin >> ws, id);

    Nasabah* nasabah = bank.cariNasabah(id);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    nasabah->lihatInformasiPribadi();
}

// fungsi untuk mengubah data nasabah
void LayananBank :: ubahDataNasabah() {
    string id;

    cout << endl;
    cout << "===== UBAH DATA NASABAH =====" << endl;
    cout << "Masukkan ID Nasabah : ";
    getline(cin >> ws, id);

    Nasabah* nasabah = bank.cariNasabah(id);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    nasabah->perbaruiInformasiPribadi();
}

// fungsi untuk membuat rekening 
void LayananBank :: buatRekening() {
    string idNasabah;
    string jenisRekening;
    string nomorRekening;
    string tanggalDibuka;
    double saldoAwal;

    cout << endl;
    cout << "===== PEMBUKAAN REKENING =====" << endl;
    cout << "ID Nasabah : ";
    getline(cin >> ws, idNasabah);

    Nasabah* nasabah = bank.cariNasabah(idNasabah);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    if (nasabah->getRekening() != nullptr) {
        cout << "Nasabah sudah memiliki rekening." << endl;
        return;
    }

    cout << endl;
    cout << "Pilih jenis rekening:" << endl;
    cout << "1. Rekening Tabungan" << endl;
    cout << "2. Rekening Giro" << endl;
    cout << "3. Rekening Deposito" << endl;
    cout << "Pilihan : ";
    getline(cin, jenisRekening);

    if (jenisRekening != "1" &&
        jenisRekening != "2" &&
        jenisRekening != "3") {
        cout << "Jenis rekening tidak valid." << endl;
        return;
    }

    int nomor = 1;
    bool ditemukan;

    do {
        ditemukan = false;
        nomorRekening = to_string(1023456788LL + nomor);

        for (const auto& rekening : daftarRekening) {
            if (rekening != nullptr &&
                rekening->getNomorRekening() == nomorRekening) {
                ditemukan = true;
                break;
            }
        }

        nomor++;
    } while (ditemukan);

    cout << "Nomor Rekening                 : "
        << nomorRekening << endl;
    
    cout << "Tanggal Pembukaan (DD-MM-YYYY) : ";
    getline(cin, tanggalDibuka);

    cout << "Saldo Awal                     : ";
    if (!(cin >> saldoAwal) || saldoAwal < 0) {
        cout << "Saldo awal tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize> :: max(), '\n');

    unique_ptr<Rekening> rekeningBaru;

    if (jenisRekening == "1") {
        rekeningBaru = make_unique<RekeningTabungan>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    } else if (jenisRekening == "2") {
        rekeningBaru = make_unique<RekeningGiro>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    } else {
        rekeningBaru = make_unique<RekeningDeposito>(
            nasabah->getIdNasabah(),
            nomorRekening,
            tanggalDibuka,
            saldoAwal
        );
    }

    Rekening* ptrRekening = rekeningBaru.get();

    daftarRekening.push_back(move(rekeningBaru));
    nasabah->setRekening(ptrRekening);

    cout << "\nRekening berhasil dibuat!" << endl;
    ptrRekening->lihatInformasiRekening();

    if (penyimpanan != nullptr) {
        if (penyimpanan->simpanRekening(*this)) {
            cout << "Data rekening berhasil disimpan.\n";
        } else {
            cout << "Gagal menyimpan data rekening.\n";
        }
    }
}

// fungsi untuk menutup rekening 
void LayananBank :: tutupRekening() {
    string nomorRekening;

    cout << endl;
    cout << "===== TUTUP REKENING =====" << endl;
    cout << "Nomor Rekening : ";
    getline(cin >> ws, nomorRekening);

    Rekening* rekening = nullptr;

    for (const auto& data : daftarRekening) {
        if (data->getNomorRekening() == nomorRekening) {
            rekening = data.get();
            break;
        }
    }

    if (rekening == nullptr) {
        cout << "Rekening tidak ditemukan." << endl;
        return;
    }

    if (!rekening->getStatusRekening()) {
        cout << "Rekening sudah nonaktif." << endl;
        return;
    }

    rekening->setStatusRekening(false);

    cout << "Rekening berhasil dinonaktifkan." << endl;
    rekening->lihatInformasiRekening();
}

// fungsi untuk mengaktifkan rekening 
void LayananBank :: aktifkanRekening() {
    string nomorRekening;

    cout << endl;
    cout << "===== AKTIFKAN REKENING =====" << endl;
    cout << "Nomor Rekening : ";
    getline(cin >> ws, nomorRekening);

    Rekening* rekening = nullptr;

    for (const auto& data : daftarRekening) {
        if (data->getNomorRekening() == nomorRekening) {
            rekening = data.get();
            break;
        }
    }

    if (rekening == nullptr) {
        cout << "Rekening tidak ditemukan." << endl;
        return;
    }

    if (rekening->getStatusRekening()) {
        cout << "Rekening sudah aktif." << endl;
        return;
    }

    rekening->setStatusRekening(true);

    cout << "Rekening berhasil diaktifkan." << endl;
    rekening->lihatInformasiRekening();
}

// setter autentikasi 
void LayananBank :: setAutentikasi(Autentikasi* autentikasi) {
    this->autentikasi = autentikasi;
}

// fungsi untuk membuat kartu ATM
void LayananBank :: buatKartuATM() {
    if (autentikasi == nullptr) {
        cout << "Autentikasi belum terhubung." << endl;
        return;
    }

    string nomorRekening;
    string nomorKartu;
    string tanggalTerbit;
    string tanggalKadaluarsa;
    string pin;

    cout << endl;
    cout << "===== PEMBUATAN KARTU ATM =====" << endl;
    cout << "Nomor Rekening     : ";
    getline(cin >> ws, nomorRekening);

    Rekening* rekening = nullptr;

    for (const auto& data : daftarRekening) {
        if (data->getNomorRekening() == nomorRekening) {
            rekening = data.get();
            break;
        }
    }

    if (rekening == nullptr) {
        cout << "Rekening tidak ditemukan." << endl;
        return;
    }

    if (!rekening->getStatusRekening()) {
        cout << "Rekening tidak aktif." << endl;
        return;
    }

    for (const auto& kartu : daftarKartu) {
        if (kartu->getRekening() == rekening) {
            cout << "Rekening ini sudah memiliki kartu ATM." << endl;
            return;
        }
    }

    unsigned long long nomor = 5274810362951841ULL;
    bool ditemukan;

    do {
        ditemukan = false;
        nomorKartu = to_string(nomor);

        for (const auto& kartu : daftarKartu) {
            if (kartu->getNomorKartu() == nomorKartu) {
                ditemukan = true;
                nomor++;
                break;
            }
        }
    } while (ditemukan);

    cout << "Nomor Kartu        : "
        << nomorKartu << endl;

    for (const auto& kartu : daftarKartu) {
        if (kartu->getNomorKartu() == nomorKartu) {
            cout << "Nomor kartu sudah digunakan." << endl;
            return;
        }
    }

    cout << "Tanggal Terbit     : ";
    getline(cin, tanggalTerbit);

    cout << "Tanggal Kadaluarsa : ";
    getline(cin, tanggalKadaluarsa);

    cout << "PIN Awal (6 digit) : ";
    getline(cin, pin);

    if (pin.length() != 6) {
        cout << "PIN harus terdiri dari 6 digit." << endl;
        return;
    }

    for (char digit : pin) {
        if (!isdigit(static_cast<unsigned char>(digit))) {
            cout << "PIN hanya boleh berisi angka." << endl;
            return;
        }
    }

    auto kartuBaru = make_unique<KartuATM>(
        nomorKartu,
        tanggalTerbit,
        tanggalKadaluarsa,
        pin,
        rekening
    );

    KartuATM* ptrKartu = kartuBaru.get();

    daftarKartu.push_back(move(kartuBaru));
    autentikasi->daftarkanKartu(ptrKartu);

    if (penyimpanan != nullptr) {
        penyimpanan->simpanKartu(*this);
    }

    cout << "Kartu ATM berhasil dibuat." << endl;
    cout << "Nomor Kartu        : " << ptrKartu->getNomorKartu() << endl;
}

// getter bank const 
const Bank& LayananBank :: getBank() const {
    return bank;
}

// setter penyimpanan 
void LayananBank :: setPenyimpanan(PenyimpananBank* penyimpanan) {
    this->penyimpanan = penyimpanan;
}

// getter bank 
Bank& LayananBank :: getBank() {
    return bank;
}

// getter daftar rekening 
const vector<unique_ptr<Rekening>>& LayananBank :: getDaftarRekening() const {
    return daftarRekening;
}

// getter daftar kartu 
const vector<unique_ptr<KartuATM>>& LayananBank :: getDaftarKartu() const {
    return daftarKartu;
}

// getter daftar transaksi
const vector<unique_ptr<Transaksi>>&
LayananBank::getDaftarTransaksi() const {
    return daftarTransaksi;
}

// fungsi untuk menambahkan data rekening tersimpan 
void LayananBank :: tambahRekeningTersimpan(
    unique_ptr<Rekening> rekening
) {
    daftarRekening.push_back(move(rekening));
}

// fungsi untuk menambahkan data kartu ATM tersimpan
void LayananBank :: tambahKartuTersimpan(
    unique_ptr<KartuATM> kartu
) {
    KartuATM* kartuPtr = kartu.get();
    daftarKartu.push_back(move(kartu));

    if (autentikasi != nullptr) {
        autentikasi->daftarkanKartu(kartuPtr);
    }
}

// fungsi untuk menambahkan data transaksi tersimpan 
void LayananBank :: tambahTransaksiTersimpan(
    unique_ptr<Transaksi> transaksi
) {
    daftarTransaksi.push_back(move(transaksi));
}

// fungsi untuk setor dana 
void LayananBank :: setorNasabah(Rekening* rekening) {
    double jumlah;

    cout << endl;
    cout << "===== SETOR TUNAI =====" << endl;

    if (rekening == nullptr || !rekening->getStatusRekening()) {
        cout << "Rekening tidak tersedia atau tidak aktif." << endl;
        return;
    }

    cout << "Jumlah Setoran : ";
    if (!(cin >> jumlah)) {
        cout << "Jumlah tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (jumlah <= 0) {
        cout << "Jumlah setoran harus lebih dari nol." << endl;
        return;
    }

    if (!rekening->setorDana(jumlah)) {
        return;
    }

    time_t waktuSekarang = time(nullptr);
    tm* waktuLokal = localtime(&waktuSekarang);
    char tanggal[11];
    strftime(tanggal, sizeof(tanggal), "%d-%m-%Y", waktuLokal);

    string idTransaksi =
        "TRX" + to_string(waktuSekarang) + "-" +
        to_string(daftarTransaksi.size() + 1);

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "1",
        "Berhasil",
        "Setor tunai melalui menu nasabah"
    );

    transaksi->setRekening(rekening);
    daftarTransaksi.push_back(move(transaksi));

    if (penyimpanan != nullptr) {
        penyimpanan->simpanRekening(*this);
        penyimpanan->simpanTransaksi(*this);
    }

    cout << "Setor tunai berhasil." << endl;
    cout << "Saldo terbaru  : " << rekening->lihatSaldo() << endl;
}

// fungsi untuk tarik dana 
void LayananBank::tarikNasabah(Rekening* rekening) {
    double jumlah;

    cout << endl;
    cout << "===== TARIK TUNAI =====" << endl;

    if (rekening == nullptr || !rekening->getStatusRekening()) {
        cout << "Rekening tidak tersedia atau tidak aktif." << endl;
        return;
    }

    cout << "Jumlah Penarikan : ";
    if (!(cin >> jumlah)) {
        cout << "Jumlah tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (jumlah <= 0) {
        cout << "Jumlah penarikan harus lebih dari nol." << endl;
        return;
    }

    if (!rekening->tarikDana(jumlah)) {
        return;
    }

    time_t waktuSekarang = time(nullptr);
    tm* waktuLokal = localtime(&waktuSekarang);
    char tanggal[11];
    strftime(tanggal, sizeof(tanggal), "%d-%m-%Y", waktuLokal);

    string idTransaksi =
        "TRX" + to_string(waktuSekarang) + "-" +
        to_string(daftarTransaksi.size() + 1);

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "2",
        "Berhasil",
        "Tarik tunai melalui menu nasabah"
    );

    transaksi->setRekening(rekening);
    daftarTransaksi.push_back(move(transaksi));

    if (penyimpanan != nullptr) {
        penyimpanan->simpanRekening(*this);
        penyimpanan->simpanTransaksi(*this);
    }

    cout << "Tarik tunai berhasil." << endl;
    cout << "Saldo terbaru    : " << rekening->lihatSaldo() << endl;
}

// fungsi untuk transfer 
void LayananBank::transferNasabah(Rekening* rekening) {
    string nomorTujuan;
    double jumlah;

    cout << endl;
    cout << "===== TRANSFER =====" << endl;

    if (rekening == nullptr || !rekening->getStatusRekening()) {
        cout << "Rekening pengirim tidak tersedia atau tidak aktif."
             << endl;
        return;
    }

    cout << "Nomor Rekening Tujuan : ";
    getline(cin >> ws, nomorTujuan);

    if (nomorTujuan == rekening->getNomorRekening()) {
        cout << "Tidak dapat transfer ke rekening sendiri." << endl;
        return;
    }

    Rekening* rekeningTujuan = nullptr;

    for (const auto& data : daftarRekening) {
        if (data != nullptr &&
            data->getNomorRekening() == nomorTujuan) {
            rekeningTujuan = data.get();
            break;
        }
    }

    if (rekeningTujuan == nullptr ||
        !rekeningTujuan->getStatusRekening()) {
        cout << "Rekening tujuan tidak ditemukan atau tidak aktif."
             << endl;
        return;
    }

    cout << "Jumlah Transfer       : ";
    if (!(cin >> jumlah)) {
        cout << "Jumlah tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (jumlah <= 0) {
        cout << "Jumlah transfer harus lebih dari nol." << endl;
        return;
    }

    if (!rekening->tarikDana(jumlah)) {
        cout << "Transfer dibatalkan." << endl;
        return;
    }

    if (!rekeningTujuan->setorDana(jumlah)) {
        rekening->setorDana(jumlah);
        cout << "Transfer gagal. Dana dikembalikan." << endl;
        return;
    }

    time_t waktuSekarang = time(nullptr);
    tm* waktuLokal = localtime(&waktuSekarang);
    char tanggal[11];
    strftime(tanggal, sizeof(tanggal), "%d-%m-%Y", waktuLokal);

    string idTransaksi =
        "TRX" + to_string(waktuSekarang) + "-" +
        to_string(daftarTransaksi.size() + 1);

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "3",
        "Berhasil",
        "Transfer melalui menu nasabah"
    );

    transaksi->setRekeningPengirim(rekening);
    transaksi->setRekeningPenerima(rekeningTujuan);
    daftarTransaksi.push_back(move(transaksi));

    if (penyimpanan != nullptr) {
        penyimpanan->simpanRekening(*this);
        penyimpanan->simpanTransaksi(*this);
    }

    cout << "Transfer berhasil." << endl;
    cout << "Saldo pengirim        : " << rekening->lihatSaldo() << endl;
}
