#include <stdio.h>


typedef struct {
    int id;
    char nomorPlat[50];
    char jenisKendaraan[50];
    int tahunProduksi;
} Kendaraan;

typedef Kendaraan KendaraanArray[100 + 1];
typedef char String[255];

// Deklarasi fungsi
void tambahData();
int bacaData(KendaraanArray kendaraan);
void lihatData(KendaraanArray kendaraan, int n);
void ubahData(KendaraanArray kendaraan, int *n);
void hapusData(KendaraanArray kendaraan, int *n);
void simpanData(KendaraanArray kendaraan, int n);

int main() {
    int pilihanMenu;
    KendaraanArray kendaraanArray;
    int n = 0;

    // Baca data dari file saat program mulai
    n = bacaData(kendaraanArray);

    do {
        printf("\n****** DATA KENDARAAN ******\n\n");
        printf("[1] Tambah Data Kendaraan\n");
        printf("[2] Lihat Data Kendaraan\n");
        printf("[3] Ubah Data Kendaraan\n");
        printf("[4] Hapus Data Kendaraan\n");
        printf("[5] Keluar Program\n");
        printf("Pilih Menu : "); scanf("%d", &pilihanMenu);

        // Reload data setiap kali memilih menu
        n = bacaData(kendaraanArray);

            if ( pilihanMenu == 1) {
                tambahData();
            }else if ( pilihanMenu == 2) {
                lihatData(kendaraanArray, n);

            } else if ( pilihanMenu == 3) {
                ubahData(kendaraanArray, &n);

            } else if ( pilihanMenu == 4) {
                hapusData(kendaraanArray, &n);
            }else if (pilihanMenu <= 0 || pilihanMenu > 5) {
                printf("\nPilihan tidak valid!\n");
            }


    } while (pilihanMenu != 5);
    if (pilihanMenu == 5) {
        printf("\nProgram selesai. Terima kasih!\n");

    }
    return 0;
}

// Fungsi untuk menambah data
void tambahData() {
    FILE *fileKendaraan;
    Kendaraan kendaraanRec;

    printf("\n*** Tambah Data Kendaraan ***\n");
    fileKendaraan = fopen("Kendaraan.dat", "ab");
    if (fileKendaraan == NULL) {
        printf("Error: File tidak dapat dibuka!\n");
        return;
    }

    printf("ID Kendaraan (9999 untuk berhenti): "); scanf("%d", &kendaraanRec.id);

    while (kendaraanRec.id != 9999) {
        printf("Nomor Plat: "); scanf(" %[^\n]", kendaraanRec.nomorPlat);
        printf("Jenis Kendaraan: "); scanf(" %[^\n]", kendaraanRec.jenisKendaraan);
        printf("Tahun Produksi: "); scanf("%d", &kendaraanRec.tahunProduksi);

        fwrite(&kendaraanRec, sizeof(Kendaraan), 1, fileKendaraan);
        printf("\nData berhasil ditambahkan!\n\n");

        printf("ID Kendaraan (9999 untuk berhenti): "); scanf("%d", &kendaraanRec.id);
    }

    fclose(fileKendaraan);
}

// Fungsi untuk membaca data dari file ke array
int bacaData(KendaraanArray kendaraan) {
    FILE *fileKendaraan;
    Kendaraan temp;
    int count = 0;

    fileKendaraan = fopen("Kendaraan.dat", "rb");
    if (fileKendaraan == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Kendaraan), 1, fileKendaraan) == 1) {
        count++;
        kendaraan[count] = temp;
    }

    fclose(fileKendaraan);
    return count;
}

// Fungsi untuk melihat data
void lihatData(KendaraanArray kendaraan, int n) {
    printf("\n*** Lihat Data Kendaraan ***\n\n");

    if (n == 0) {
        printf("Tidak ada data kendaraan.\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        printf("ID Kendaraan     : %d\n", kendaraan[i].id);
        printf("Nomor Plat       : %s\n", kendaraan[i].nomorPlat);
        printf("Jenis Kendaraan  : %s\n", kendaraan[i].jenisKendaraan);
        printf("Tahun Produksi   : %d\n", kendaraan[i].tahunProduksi);
        printf("\n");
    }
}

// Fungsi untuk mengubah data
void ubahData(KendaraanArray kendaraan, int *n) {
    int idCari, found = 0;

    printf("\n*** Ubah Data Kendaraan ***\n");
    printf("ID Kendaraan : "); scanf("%d", &idCari);

    if (*n == 0) {
        printf("\nData Kendaraan dengan ID %d tidak ditemukan!\n", idCari);
        return;
    }

    for (int i = 1; i <= *n; i++) {
        if (kendaraan[i].id == idCari) {
            found = 1;

            printf("\nMasukkan nomor plat baru : "); scanf(" %[^\n]", kendaraan[i].nomorPlat);

            simpanData(kendaraan, *n);
            printf("Data Kendaraan berhasil diperbarui!\n");
            break;
        }
    }

    if (!found) {
        printf("\nData Kendaraan dengan ID %d tidak ditemukan!\n", idCari);
    }
}

// Fungsi untuk menghapus data
void hapusData(KendaraanArray kendaraan, int *n) {
    int idCari, found = 0;

    printf("\n*** Hapus Data Kendaraan ***\n");
    printf("ID Kendaraan : "); scanf("%d", &idCari);

    if (*n == 0) {
        printf("\nTidak ada data kendaraan.\n");
        return;
    }

    for (int i = 1; i <= *n; i++) {
        if (kendaraan[i].id == idCari) {
            found = 1;

            // Geser data ke atas
            for (int j = i; j < *n; j++) {
                kendaraan[j] = kendaraan[j + 1];
            }
            (*n)--;

            simpanData(kendaraan, *n);
            printf("Data berhasil dihapus!\n");
            break;
        }
    }

    if (!found) {
        printf("\nData Kendaraan dengan ID %d tidak ditemukan!\n", idCari);
    }
}

// Fungsi untuk menyimpan data ke file (overwrite)
void simpanData(KendaraanArray kendaraan, int n) {
    FILE *fileKendaraan;

    fileKendaraan = fopen("Kendaraan.dat", "wb");
    if (fileKendaraan == NULL) {
        printf("Error: File tidak dapat dibuka!\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        fwrite(&kendaraan[i], sizeof(Kendaraan), 1, fileKendaraan);
    }

    fclose(fileKendaraan);
}
