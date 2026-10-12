#include "layanan.h"
#include "../nasabah/nasabah.h"

#include <iostream>
#include <string>
#include <limits>
#include <memory>

using namespace std;

// constructor class layanan bank 
LayananBank :: LayananBank(string namaBank)
    : bank(namaBank), nasabahAktif(nullptr) {
}

// fungsi registrasi nasabah
void LayananBank :: registrasiNasabah() {
    string id;
    string nama;
    string tanggalLahir;
    string alamat;
    string nomorTelepon;
    string email;

    cout << "\n===== REGISTRASI NASABAH =====" << endl;

    cout << "ID Nasabah       : ";
    getline(cin >> ws, id);

    cout << "Nama             : ";
    getline(cin, nama);

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
}

// fungsi untuk melihat data nasabah
void LayananBank :: lihatDataNasabah() {
    string id;

    cout << "\n===== LIHAT DATA NASABAH =====" << endl;
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

    cout << "\n===== UBAH DATA NASABAH =====" << endl;
    cout << "Masukkan ID Nasabah: ";
    getline(cin >> ws, id);

    Nasabah* nasabah = bank.cariNasabah(id);

    if (nasabah == nullptr) {
        cout << "Nasabah tidak ditemukan." << endl;
        return;
    }

    nasabah->perbaruiInformasiPribadi();
}

// fungsi untuk membuat rekening 
void LayananBank::buatRekening() {
    string idNasabah;
    string jenisRekening;
    string nomorRekening;
    string tanggalDibuka;
    double saldoAwal;

    cout << "\n----- PEMBUKAAN REKENING -----" << endl;
    cout << "ID Nasabah: ";
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

    cout << "\nPilih jenis rekening:" << endl;
    cout << "1. Rekening Tabungan" << endl;
    cout << "2. Rekening Giro" << endl;
    cout << "3. Rekening Deposito" << endl;
    cout << "Pilihan: ";
    getline(cin, jenisRekening);

    if (jenisRekening != "1" &&
        jenisRekening != "2" &&
        jenisRekening != "3") {
        cout << "Jenis rekening tidak valid." << endl;
        return;
    }

    cout << "Nomor Rekening: ";
    getline(cin, nomorRekening);

    cout << "Tanggal Pembukaan (DD-MM-YYYY): ";
    getline(cin, tanggalDibuka);

    cout << "Saldo Awal: ";
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
}

// fungsi untuk setor 

void LayananBank :: setor() {
    string nomorRekening;
    string idTransaksi;
    string tanggal;
    string keterangan;
    double jumlah;

    cout << "\n----- SETOR TUNAI -----" << endl;

    cout << "Nomor Rekening: ";
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

    cout << "ID Transaksi: ";
    getline(cin, idTransaksi);

    cout << "Tanggal Transaksi: ";
    getline(cin, tanggal);

    cout << "Jumlah Setoran: Rp";
    if (!(cin >> jumlah)) {
        cout << "Jumlah tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        return;
    }   

    cin.ignore(numeric_limits<streamsize> :: max(), '\n');

    cout << "Keterangan: ";
    getline(cin, keterangan);

    if (!rekening->setorDana(jumlah)) {
        return;
    }

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "1",
        "Berhasil",
        keterangan
    );

    transaksi->setRekening(rekening);
    transaksi->lihatDetailTransaksi();

    daftarTransaksi.push_back(move(transaksi));

    cout << "Saldo terbaru: "
         << rekening->lihatSaldo() << endl;
}

// fungsi untuk tarik 

void LayananBank :: tarik() {
    string nomorRekening;
    string idTransaksi;
    string tanggal;
    string keterangan;
    double jumlah;

    cout << "\n----- TARIK TUNAI -----" << endl;

    cout << "Nomor Rekening: ";
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

    cout << "ID Transaksi: ";
    getline(cin, idTransaksi);

    cout << "Tanggal Transaksi: ";
    getline(cin, tanggal);

    cout << "Jumlah Penarikan: Rp";
    if (!(cin >> jumlah)) {
        cout << "Jumlah tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize> :: max(), '\n');

    cout << "Keterangan: ";
    getline(cin, keterangan);

    if (!rekening->tarikDana(jumlah)) {
        return;
    }

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "2",
        "Berhasil",
        keterangan
    );

    transaksi->setRekening(rekening);
    transaksi->lihatDetailTransaksi();

    daftarTransaksi.push_back(move(transaksi));

    cout << "Saldo terbaru: "
         << rekening->lihatSaldo() << endl;
}

// fungsi untuk transfer 

void LayananBank :: transfer() {
    string nomorPengirim;
    string nomorPenerima;
    string idTransaksi;
    string tanggal;
    string keterangan;
    double jumlah;

    cout << "\n----- TRANSFER -----" << endl;

    cout << "Nomor Rekening Pengirim: ";
    getline(cin >> ws, nomorPengirim);

    Rekening* rekeningPengirim = nullptr;

    for (const auto& data : daftarRekening) {
        if (data->getNomorRekening() == nomorPengirim) {
            rekeningPengirim = data.get();
            break;
        }
    }

    if (rekeningPengirim == nullptr) {
        cout << "Rekening pengirim tidak ditemukan." << endl;
        return;
    }

    cout << "Nomor Rekening Penerima: ";
    getline(cin, nomorPenerima);

    if (nomorPengirim == nomorPenerima) {
        cout << "Rekening pengirim dan penerima tidak boleh sama."
             << endl;
        return;
    }

    Rekening* rekeningPenerima = nullptr;

    for (const auto& data : daftarRekening) {
        if (data->getNomorRekening() == nomorPenerima) {
            rekeningPenerima = data.get();
            break;
        }
    }

    if (rekeningPenerima == nullptr) {
        cout << "Rekening penerima tidak ditemukan." << endl;
        return;
    }

    cout << "ID Transaksi: ";
    getline(cin, idTransaksi);

    cout << "Tanggal Transaksi: ";
    getline(cin, tanggal);

    cout << "Jumlah Transfer: ";
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

    cout << "Keterangan: ";
    getline(cin, keterangan);

    if (!rekeningPengirim->tarikDana(jumlah)) {
        cout << "Transfer dibatalkan." << endl;
        return;
    }

    if (!rekeningPenerima->setorDana(jumlah)) {
        rekeningPengirim->setorDana(jumlah);
        cout << "Transfer gagal. Dana dikembalikan ke rekening "
             << "pengirim." << endl;
        return;
    }

    auto transaksi = make_unique<Transaksi>(
        idTransaksi,
        tanggal,
        jumlah,
        "3",
        "Berhasil",
        keterangan
    );

    transaksi->setRekeningPengirim(rekeningPengirim);
    transaksi->setRekeningPenerima(rekeningPenerima);

    transaksi->lihatDetailTransaksi();

    daftarTransaksi.push_back(move(transaksi));

    cout << "Transfer berhasil." << endl;
    cout << "Saldo pengirim terbaru: "
         << rekeningPengirim->lihatSaldo() << endl;
    cout << "Saldo penerima terbaru: "
         << rekeningPenerima->lihatSaldo() << endl;
}


