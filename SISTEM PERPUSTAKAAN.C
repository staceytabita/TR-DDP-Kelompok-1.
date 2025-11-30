#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


#define MAX 100

struct Buku {
    char kode[10];
    char judul[50];
    char pengarang[30];
    int stok;
    int dipinjam;
    char namaPeminjam[30];
};

struct RiwayatPinjam {

    char kode[10];
    char judul[50];
    char namaPeminjam[30];
};

struct RiwayatKembali {
    char kode[10];
    char judul[50];
    int hariTerlambat;
    int denda;
};


void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}




void simpanDataBuku(struct Buku daftar[], int jumlah) {
    FILE *fp = fopen("buku.txt", "w");
    if (fp == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s|%s|%s|%d|%d|%s\n",
                daftar[i].kode,
                daftar[i].judul,
                daftar[i].pengarang,
                daftar[i].stok,
                daftar[i].dipinjam,
                strlen(daftar[i].namaPeminjam) == 0 ? "-" : daftar[i].namaPeminjam);
    }

    fclose(fp);
}

void muatDataBuku(struct Buku daftar[], int *jumlah) {
    FILE *fp = fopen("buku.txt", "r");
    if (fp == NULL) {
        printf("Belum ada file buku.txt.\n");
        return;
    }

    *jumlah = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]\n",
                  daftar[*jumlah].kode,
                  daftar[*jumlah].judul,
                  daftar[*jumlah].pengarang,
                  &daftar[*jumlah].stok,
                  &daftar[*jumlah].dipinjam,
                  daftar[*jumlah].namaPeminjam) == 6) {

        if (strcmp(daftar[*jumlah].namaPeminjam, "-") == 0)
            daftar[*jumlah].namaPeminjam[0] = '\0';

        (*jumlah)++;
    }

    fclose(fp);
}

void hapusDataBuku() {
    FILE *file = fopen("buku.txt", "w");
    if (file == NULL) {
        printf("File tidak bisa dibuka!\n");
        return;
    }
    fclose(file);
    printf("Riwayat Buku berhasil dihapus!\n");
}

void simpanRiwayatPinjam(struct RiwayatPinjam logPinjam[], int jumlahPinjam) {
    FILE *fp = fopen("riwayat_pinjam.txt", "w");
    if (fp == NULL) return;
    for (int i = 0; i < jumlahPinjam; i++) {
        fprintf(fp, "%s|%s|%s\n",
                logPinjam[i].kode,
                logPinjam[i].judul,
                logPinjam[i].namaPeminjam);
    }
    fclose(fp);
}

void muatRiwayatPinjam(struct RiwayatPinjam logPinjam[], int *jumlahPinjam) {
    FILE *fp = fopen("riwayat_pinjam.txt", "r");
    if (fp == NULL) return;
    while (fscanf(fp, "%[^|]|%[^|]|%[^\n]\n",
                  logPinjam[*jumlahPinjam].kode,
                  logPinjam[*jumlahPinjam].judul,
                  logPinjam[*jumlahPinjam].namaPeminjam) == 3) {
        (*jumlahPinjam)++;
    }
    fclose(fp);
}

void hapusDataPeminjaman() {
    FILE *file = fopen("riwayat_kembali.txt", "w");
    if (file == NULL) {
        printf("File tidak bisa dibuka!\n");
        return;
    }
    fclose(file);
    printf("Riwayat peminjaman berhasil dihapus!\n");
}

void simpanRiwayatKembali(struct RiwayatKembali logKembali[], int jumlahKembali) {
    FILE *fp = fopen("riwayat_kembali.txt", "w");
    if (fp == NULL) return;
    for (int i = 0; i < jumlahKembali; i++) {
        fprintf(fp, "%s|%s|%d|%d\n",
                logKembali[i].kode,
                logKembali[i].judul,
                logKembali[i].hariTerlambat,
                logKembali[i].denda);
    }
    fclose(fp);
}

void muatRiwayatKembali(struct RiwayatKembali logKembali[], int *jumlahKembali) {
    FILE *fp = fopen("riwayat_kembali.txt", "r");
    if (fp == NULL) return;
    while (fscanf(fp, "%[^|]|%[^|]|%d|%d\n",
                  logKembali[*jumlahKembali].kode,
                  logKembali[*jumlahKembali].judul,
                  &logKembali[*jumlahKembali].hariTerlambat,
                  &logKembali[*jumlahKembali].denda) == 4) {
        (*jumlahKembali)++;
    }
    fclose(fp);
}

void hapusRiwayatKembali() {
    FILE *file = fopen("riwayat_kembali.txt", "w");
    if (file == NULL) {
        printf("File tidak bisa dibuka!\n");
        return;
    }
    fclose(file);
    printf("Riwayat Pengembalian berhasil dihapus!\n");

}


void loadingSimple() {
    printf("Loading");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        Sleep(100);
    }
    printf("\n");
}


int main() {
    struct Buku daftar[MAX];
    struct RiwayatPinjam logPinjam[MAX];
    struct RiwayatKembali logKembali[MAX];
    int jumlah = 0;
    int jumlahPinjam = 0;
    int jumlahKembali = 0;

    muatDataBuku(daftar, &jumlah);
    muatRiwayatPinjam(logPinjam, &jumlahPinjam);
    muatRiwayatKembali(logKembali, &jumlahKembali);

    int menu, pilihanSub;
    char kode[10];

    do {
        clear();
        system("color 17");
        printf("=== SISTEM PERPUSTAKAAN ===\n");
        printf("1. Data Buku\n");
        printf("2. Peminjaman\n");
        printf("3. Pengembalian\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);
        getchar();

        switch (menu) {
       case 1:
    clear();
    system("color 57");
    printf("=== DATA BUKU ===\n");
    printf("1. Tambah Buku\n");
    printf("2. Lihat Buku\n");
    printf("3. Hapus Buku\n");
    printf("4. Kembali\n");
    printf("Pilih: ");
    scanf("%d", &pilihanSub);
    getchar();

     if (pilihanSub == 4) break;

    if (pilihanSub == 1) {
        clear();
        printf("Masukkan Kode Buku: ");
        scanf("%s", daftar[jumlah].kode);
        getchar();
        printf("Masukkan Judul Buku: ");
        fgets(daftar[jumlah].judul, sizeof(daftar[jumlah].judul), stdin);
        daftar[jumlah].judul[strcspn(daftar[jumlah].judul, "\n")] = 0;
        printf("Masukkan Nama Pengarang: ");
        fgets(daftar[jumlah].pengarang, sizeof(daftar[jumlah].pengarang), stdin);
        daftar[jumlah].pengarang[strcspn(daftar[jumlah].pengarang, "\n")] = 0;
        printf("Masukkan Stok: ");
        scanf("%d", &daftar[jumlah].stok);
        getchar();
        daftar[jumlah].dipinjam = 0;

        jumlah++;
        simpanDataBuku(daftar, jumlah);

        printf("\nBuku berhasil ditambahkan!\n");
        pause();

    } else if (pilihanSub == 2) {
        clear();
        printf("=== DAFTAR BUKU ===\n\n");

        if (jumlah == 0)
            printf("Belum ada buku.\n");
        else {
            printf("-------------------------------------------------------------\n");
            printf("| %-10s | %-25s | %-15s | %-5s |\n",
                   "Kode", "Judul", "Pengarang", "Stok");
            printf("-------------------------------------------------------------\n");

            for (int i = 0; i < jumlah; i++) {
                printf("| %-10s | %-25s | %-15s | %-5d |\n",
                       daftar[i].kode,
                       daftar[i].judul,
                       daftar[i].pengarang,
                       daftar[i].stok);
            }

            printf("-------------------------------------------------------------\n");
        }
        pause();

    } else if (pilihanSub == 3) {
        clear();
        hapusDataBuku();
        jumlah = 0;
        pause();
    }

    break;


        case 2:
            clear();
            system("color 57");
            printf("=== MENU PEMINJAMAN ===\n");
            printf("1. Pinjam Buku\n");
            printf("2. Lihat Riwayat Peminjaman\n");
            printf("3. Hapus Peminjaman\n");
            printf("4. Kembali\n");
            printf("Pilih: ");
            scanf("%d", &pilihanSub);
            getchar();

            if (pilihanSub == 4) break;

            if (pilihanSub == 1) {
                clear();
                printf("Masukkan kode buku: ");
                scanf("%s", kode);
                getchar();
                int ditemukan = -1;
                for (int i = 0; i < jumlah; i++) {
                    if (strcmp(daftar[i].kode, kode) == 0) {
                        ditemukan = i;
                        break;
                    }
                }
                if (ditemukan == -1) {
                    printf("Buku tidak ditemukan.\n");
                } else if (daftar[ditemukan].stok == 0) {
                    printf("Stok buku habis.\n");
                } else {
                    printf("Masukkan nama peminjam: ");
                    fgets(daftar[ditemukan].namaPeminjam, sizeof(daftar[ditemukan].namaPeminjam), stdin);
                    daftar[ditemukan].namaPeminjam[strcspn(daftar[ditemukan].namaPeminjam, "\n")] = 0;
                    daftar[ditemukan].stok--;
                    daftar[ditemukan].dipinjam = 1;

                    strcpy(logPinjam[jumlahPinjam].kode, daftar[ditemukan].kode);
                    strcpy(logPinjam[jumlahPinjam].judul, daftar[ditemukan].judul);
                    strcpy(logPinjam[jumlahPinjam].namaPeminjam, daftar[ditemukan].namaPeminjam);
                    jumlahPinjam++;
                    simpanRiwayatPinjam(logPinjam, jumlahPinjam);

                    printf("\nPeminjaman berhasil dicatat!\n");
                }
                pause();
            } else if (pilihanSub == 2) {
                clear();
                printf("=== RIWAYAT PEMINJAMAN ===\n\n");
                if (jumlahPinjam == 0) {
                    printf("Belum ada data peminjaman.\n");
                } else {
                    printf("---------------------------------------------------------------\n");
                    printf("| %-3s | %-10s | %-30s | %-20s |\n",
                           "No", "Kode", "Judul", "Nama Peminjam");
                    printf("---------------------------------------------------------------\n");
                    for (int i = 0; i < jumlahPinjam; i++) {
                        printf("| %-3d | %-10s | %-30s | %-20s |\n",
                               i + 1,
                               logPinjam[i].kode,
                               logPinjam[i].judul,
                               logPinjam[i].namaPeminjam);
                    }
                    printf("---------------------------------------------------------------\n");
                }
                pause();

                }   else if (pilihanSub == 3) {
                    clear();
                    hapusDataPeminjaman();
                    jumlahPinjam = 0;
                    pause();
                }

                break;

        case 3:
            clear();
            system("color 57");
            printf("=== MENU PENGEMBALIAN ===\n");
            printf("1. Kembalikan Buku\n");
            printf("2. Lihat Riwayat Pengembalian\n");
            printf("3. Hapus Pengembalian\n");
            printf("4. Kembali\n");
            printf("Pilih: ");
            scanf("%d", &pilihanSub);
            getchar();

            if (pilihanSub == 4) break;

            if (pilihanSub == 1) {
                clear();
                printf("Masukkan kode buku: ");
                scanf("%s", kode);
                getchar();
                int ditemukan = -1;
                for (int i = 0; i < jumlah; i++) {
                    if (strcmp(daftar[i].kode, kode) == 0) {
                        ditemukan = i;
                        break;
                    }
                }
                if (ditemukan == -1) {
                    printf("Buku tidak ditemukan.\n");
                } else {
                    int hariTerlambat;
                    printf("Masukkan jumlah hari terlambat: ");
                    scanf("%d", &hariTerlambat);
                    getchar();
                    int denda = hariTerlambat * 100;

                    daftar[ditemukan].stok++;
                    daftar[ditemukan].dipinjam = 0;

                    strcpy(logKembali[jumlahKembali].kode, daftar[ditemukan].kode);
                    strcpy(logKembali[jumlahKembali].judul, daftar[ditemukan].judul);
                    logKembali[jumlahKembali].hariTerlambat = hariTerlambat;
                    logKembali[jumlahKembali].denda = denda;
                    jumlahKembali++;
                    simpanRiwayatKembali(logKembali, jumlahKembali);

                    printf("\nPengembalian berhasil!\nDenda: Rp%d\n", denda);
                }
                pause();
            } else if (pilihanSub == 2) {
                clear();
                printf("=== RIWAYAT PENGEMBALIAN ===\n\n");
                if (jumlahKembali == 0) {
                    printf("Belum ada data pengembalian.\n");
                } else {
                    printf("---------------------------------------------------------------------------------\n");
                    printf("| %-3s | %-10s | %-30s | %-15s | %-10s |\n",
                           "No", "Kode", "Judul", "Terlambat(hari)", "Denda");
                    printf("---------------------------------------------------------------------------------\n");
                    for (int i = 0; i < jumlahKembali; i++) {
                        printf("| %-3d | %-10s | %-30s | %-15d | Rp%-9d |\n",
                               i + 1,
                               logKembali[i].kode,
                               logKembali[i].judul,
                               logKembali[i].hariTerlambat,
                               logKembali[i].denda);
                    }
                    printf("---------------------------------------------------------------------------------\n");
                }
                pause();

                }else if (pilihanSub == 3) {
                    clear();
                    hapusDataPeminjaman();
                    jumlahPinjam = 0;
                    pause();
            }
            break;
        }

    } while (menu != 4);

    printf("\nTerima kasih sudah menggunakan sistem perpustakaan!\n");
    return 0;
}
