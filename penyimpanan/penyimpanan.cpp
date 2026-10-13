
#include "penyimpanan.h"
#include "../layanan/layanan.h"
#include "../nasabah/nasabah.h"
#include "../rekening/rekening.h"
#include "../kartu/kartu.h"
#include "../transaksi/transaksi.h"

#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <utility>

using namespace std;

// constructor class penyimpanan bank
PenyimpananBank :: PenyimpananBank(const string& folder)
    : folderData(folder) {
}

// fungsi untuk menyimpan data nasabah
bool PenyimpananBank :: simpanNasabah(const LayananBank& layanan) {
    ofstream file(folderData + "/nasabah.csv");

    if (!file.is_open()) {
        return false;
    }

    file << "idNasabah,nama,tanggalLahir,alamat,nomorTelepon,email\n";

    for (const Nasabah& nasabah :
         layanan.getBank().getDaftarNasabah()) {
        file << nasabah.getIdNasabah() << ','
             << nasabah.getNama() << ','
             << nasabah.getTanggalLahir() << ','
             << nasabah.getAlamat() << ','
             << nasabah.getNomorTelepon() << ','
             << nasabah.getEmail() << '\n';
    }

    return file.good();
}

// fungsi untuk menyimpan data rekening 
bool PenyimpananBank :: simpanRekening(const LayananBank& layanan) {
    ofstream file(folderData + "/rekening.csv");

    if (!file.is_open()) {
        return false;
    }

    file << "nomorRekening,idNasabah,jenis,tanggalDibuka,saldo,status\n";

    for (const auto& rekening : layanan.getDaftarRekening()) {
        if (!rekening) {
            continue;
        }

        string jenis;

        if (dynamic_cast<RekeningTabungan*>(rekening.get()) != nullptr) {
            jenis = "1";
        } else if (dynamic_cast<RekeningGiro*>(rekening.get()) != nullptr) {
            jenis = "2";
        } else if (dynamic_cast<RekeningDeposito*>(rekening.get()) != nullptr) {
            jenis = "3";
        } else {
            continue;
        }

        file << rekening->getNomorRekening() << ','
             << rekening->getNama() << ','
             << jenis << ','
             << rekening->getTanggalDibuka() << ','
             << rekening->getSaldo() << ','
             << rekening->getStatusRekening() << '\n';
    }

    return file.good();
}

// fungsi untuk menyimpan data kartu ATM
bool PenyimpananBank :: simpanKartu(const LayananBank& layanan) {
    ofstream file(folderData + "/kartu.csv");

    if (!file.is_open()) {
        return false;
    }

    file << "nomorKartu,tanggalTerbit,tanggalKadaluarsa,pin,"
            "nomorRekening,status\n";

    for (const auto& kartu : layanan.getDaftarKartu()) {
        if (!kartu) {
            continue;
        }

        file << kartu->getNomorKartu() << ','
             << kartu->getTanggalTerbit() << ','
             << kartu->getTanggalKadaluarsa() << ','
             << kartu->getPIN() << ',';

        if (kartu->getRekening() != nullptr) {
            file << kartu->getRekening()->getNomorRekening();
        }

        file << ',' << kartu->getStatusKartu() << '\n';
    }

    return file.good();
}

// fungsi untuk menyimpan data transaksi 
bool PenyimpananBank :: simpanTransaksi(const LayananBank& layanan) {
    ofstream file(folderData + "/transaksi.csv");

    if (!file.is_open()) {
        return false;
    }

    file << "idTransaksi,tanggal,jumlah,jenis,status,keterangan,"
            "nomorRekening,nomorPengirim,nomorPenerima\n";

    for (const auto& transaksi : layanan.getDaftarTransaksi()) {
        if (!transaksi) {
            continue;
        }

        file << transaksi->getIdTransaksi() << ','
             << transaksi->getTanggal() << ','
             << transaksi->getJumlah() << ','
             << transaksi->getJenis() << ','
             << transaksi->getStatus() << ','
             << transaksi->getKeterangan() << ',';

        if (transaksi->getRekening() != nullptr) {
            file << transaksi->getRekening()->getNomorRekening();
        }

        file << ',';

        if (transaksi->getRekeningPengirim() != nullptr) {
            file << transaksi->getRekeningPengirim()->getNomorRekening();
        }

        file << ',';

        if (transaksi->getRekeningPenerima() != nullptr) {
            file << transaksi->getRekeningPenerima()->getNomorRekening();
        }

        file << '\n';
    }

    return file.good();
}

// fungsi untuk memuat data nasabah
bool PenyimpananBank :: muatNasabah(LayananBank& layanan) {
    ifstream file(folderData + "/nasabah.csv");

    if (!file.is_open()) {
        return false;
    }

    string baris;
    getline(file, baris);

    while (getline(file, baris)) {
        if (baris.empty()) {
            continue;
        }

        string id;
        string nama;
        string tanggalLahir;
        string alamat;
        string nomorTelepon;
        string email;

        stringstream ss(baris);

        getline(ss, id, ',');
        getline(ss, nama, ',');
        getline(ss, tanggalLahir, ',');
        getline(ss, alamat, ',');
        getline(ss, nomorTelepon, ',');
        getline(ss, email);

        Nasabah nasabah(
            id,
            nama,
            tanggalLahir,
            alamat,
            nomorTelepon,
            email
        );

        layanan.getBank().tambahNasabah(nasabah);
    }

    return !file.bad();
}

// fungsi untuk memuat data rekening 
bool PenyimpananBank :: muatRekening(LayananBank& layanan) {
    ifstream file(folderData + "/rekening.csv");

    if (!file.is_open()) {
        return false;
    }

    string baris;
    getline(file, baris);

    while (getline(file, baris)) {
        if (baris.empty()) {
            continue;
        }

        string nomorRekening;
        string idNasabah;
        string jenis;
        string tanggalDibuka;
        string saldoText;
        string statusText;

        stringstream ss(baris);

        getline(ss, nomorRekening, ',');
        getline(ss, idNasabah, ',');
        getline(ss, jenis, ',');
        getline(ss, tanggalDibuka, ',');
        getline(ss, saldoText, ',');
        getline(ss, statusText);

        stringstream saldoStream(saldoText);
        double saldo = 0.0;

        if (!(saldoStream >> saldo)) {
            return false;
        }

        Nasabah* nasabah = layanan.getBank().cariNasabah(idNasabah);

        if (nasabah == nullptr) {
            continue;
        }

        if (nasabah->getRekening() != nullptr) {
            continue;
        }

        unique_ptr<Rekening> rekening;

        if (jenis == "1") {
            rekening = make_unique<RekeningTabungan>(
                idNasabah, nomorRekening, tanggalDibuka, saldo
            );
        } else if (jenis == "2") {
            rekening = make_unique<RekeningGiro>(
                idNasabah, nomorRekening, tanggalDibuka, saldo
            );
        } else if (jenis == "3") {
            rekening = make_unique<RekeningDeposito>(
                idNasabah, nomorRekening, tanggalDibuka, saldo
            );
        } else {
            continue;
        }

        bool statusAktif =
            statusText == "1" || statusText == "true";

        rekening->setStatusRekening(statusAktif);

        Rekening* rekeningPtr = rekening.get();
        nasabah->setRekening(rekeningPtr);

        layanan.tambahRekeningTersimpan(move(rekening));
    }

    return !file.bad();
}

// fungsi untuk memuat data kartu ATM
bool PenyimpananBank :: muatKartu(LayananBank& layanan) {
    ifstream file(folderData + "/kartu.csv");

    if (!file.is_open()) {
        return false;
    }

    string baris;
    getline(file, baris);

    while (getline(file, baris)) {
        if (baris.empty()) {
            continue;
        }

        string nomorKartu;
        string tanggalTerbit;
        string tanggalKadaluarsa;
        string pin;
        string nomorRekening;
        string statusText;

        stringstream ss(baris);

        getline(ss, nomorKartu, ',');
        getline(ss, tanggalTerbit, ',');
        getline(ss, tanggalKadaluarsa, ',');
        getline(ss, pin, ',');
        getline(ss, nomorRekening, ',');
        getline(ss, statusText);

        Rekening* rekening = nullptr;

        for (const auto& item : layanan.getDaftarRekening()) {
            if (item && item->getNomorRekening() == nomorRekening) {
                rekening = item.get();
                break;
            }
        }

        if (rekening == nullptr) {
            continue;
        }

        unique_ptr<KartuATM> kartu = make_unique<KartuATM>(
            nomorKartu,
            tanggalTerbit,
            tanggalKadaluarsa,
            pin,
            rekening
        );

        bool statusAktif =
            statusText == "1" || statusText == "true";

        if (!statusAktif) {
            kartu->blokirKartu();
        }

        layanan.tambahKartuTersimpan(move(kartu));
    }

    return !file.bad();
}

// fungsi untuk memuat data transaksi
bool PenyimpananBank :: muatTransaksi(LayananBank& layanan) {
    ifstream file(folderData + "/transaksi.csv");

    if (!file.is_open()) {
        return false;
    }

    string baris;
    getline(file, baris);

    while (getline(file, baris)) {
        if (baris.empty()) {
            continue;
        }

        string id;
        string tanggal;
        string jumlahText;
        string jenis;
        string status;
        string keterangan;
        string nomorRekening;
        string nomorPengirim;
        string nomorPenerima;

        stringstream ss(baris);

        getline(ss, id, ',');
        getline(ss, tanggal, ',');
        getline(ss, jumlahText, ',');
        getline(ss, jenis, ',');
        getline(ss, status, ',');
        getline(ss, keterangan, ',');
        getline(ss, nomorRekening, ',');
        getline(ss, nomorPengirim, ',');
        getline(ss, nomorPenerima);

        stringstream jumlahStream(jumlahText);
        double jumlah = 0.0;

        if (!(jumlahStream >> jumlah)) {
            return false;
        }

        unique_ptr<Transaksi> transaksi = make_unique<Transaksi>(
            id, tanggal, jumlah, jenis, status, keterangan
        );

        auto cariRekening = [&layanan](const string& nomor) -> Rekening* {
            for (const auto& item : layanan.getDaftarRekening()) {
                if (item && item->getNomorRekening() == nomor) {
                    return item.get();
                }
            }

            return nullptr;
        };

        if (jenis == "3") {
            transaksi->setRekeningPengirim(
                cariRekening(nomorPengirim)
            );

            transaksi->setRekeningPenerima(
                cariRekening(nomorPenerima)
            );
        } else {
            transaksi->setRekening(
                cariRekening(nomorRekening)
            );
        }

        layanan.tambahTransaksiTersimpan(move(transaksi));
    }

    return !file.bad();
}

// fungsi untuk menyimpan semua data 
bool PenyimpananBank :: simpanSemuaData(const LayananBank& layanan) {
    bool nasabah = simpanNasabah(layanan);
    bool rekening = simpanRekening(layanan);
    bool kartu = simpanKartu(layanan);
    bool transaksi = simpanTransaksi(layanan);

    return nasabah && rekening && kartu && transaksi;
}

bool PenyimpananBank::muatSemuaData(LayananBank& layanan) {
    if (!muatNasabah(layanan)) {
        return false;
    }

    if (!muatRekening(layanan)) {
        return false;
    }

    if (!muatKartu(layanan)) {
        return false;
    }

    if (!muatTransaksi(layanan)) {
        return false;
    }

    return true;
}
