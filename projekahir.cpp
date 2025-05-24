#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using namespace std;

struct Buku
{
    char judul[100], pengarang[100], genre[100];
    int tahunterbit;
    Buku *next;
};

int jmlbuku = 0;
int pilih;

Buku *kepala = NULL, *ekor = NULL, *baru = NULL, *bantu = NULL;

void bacadata()
{
    FILE *databuku = fopen("databuku.dat", "rb");
    if (databuku == NULL)
    {
        cout << "Gagal membuka file!\n";
        fclose(databuku);
    }

    kepala = ekor = NULL;
    Buku bukutemp;

    while (fread(&bukutemp, sizeof(Buku), 1, databuku))
    {
        baru = new Buku();
        strcpy(baru->judul, bukutemp.judul);
        strcpy(baru->pengarang, bukutemp.pengarang);
        strcpy(baru->genre, bukutemp.genre);
        baru->tahunterbit = bukutemp.tahunterbit;
        baru->next = NULL;

        if (kepala == NULL)
        {
            kepala = ekor = baru;
        }
        else
        {
            ekor->next = baru;
            ekor = baru;
        }
        jmlbuku++;
    }

    fclose(databuku);
}

void bubblesort()
{
    if (kepala == NULL)
        return;

    bool swapped;
    Buku *ptr1;
    Buku *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = kepala;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->judul, ptr1->next->judul) > 0)
            {
                swap(ptr1->judul, ptr1->next->judul);
                swap(ptr1->pengarang, ptr1->next->pengarang);
                swap(ptr1->genre, ptr1->next->genre);
                swap(ptr1->tahunterbit, ptr1->next->tahunterbit);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void buatlink(char judul[], char pengarang[], char genre[], int tahun)
{
    baru = new Buku();
    strcpy(baru->judul, judul);
    strcpy(baru->pengarang, pengarang);
    strcpy(baru->genre, genre);
    baru->tahunterbit = tahun;
    baru->next = NULL;

    kepala = ekor = baru;

    FILE *databuku = fopen("databuku.dat", "ab");
    if (databuku != NULL)
    {
        fwrite(baru, sizeof(Buku), 1, databuku);
        fclose(databuku);
        jmlbuku++;
    }

    cout << "\nBuku pertama berhasil ditambahkan!" << endl;
    getch();
}

void tambahakhir()
{
}

void tampilkanbuku()
{
    system("cls");
    cout << "\n=========== DAFTAR BUKU (Diurutkan berdasarkan Judul) ===========\n";

    if (kepala == NULL)
    {
        cout << "Mencoba memuat data dari file...\n";
        bacadata();
    }

    if (kepala == NULL)
    {
        cout << "Belum ada data buku yang tersimpan.\n";
    }
    else
    {
        bubblesort();

        bantu = kepala;
        int no = 1;
        while (bantu != NULL)
        {
            cout << "\nBuku ke-" << no++ << endl;
            cout << "Judul       : " << bantu->judul << endl;
            cout << "Pengarang   : " << bantu->pengarang << endl;
            cout << "Genre       : " << bantu->genre << endl;
            cout << "Tahun Terbit: " << bantu->tahunterbit << endl;
            cout << "--------------------------\n";
            bantu = bantu->next;
        }
    }

    cout << "\nTotal buku: " << jmlbuku << endl;
    cout << "\nTekan apa saja untuk kembali ke menu utama..";
    getch();
}

void sequential_search(char juduldicari[], char pengarangdicari[], char genredicari[])
{
    
}

void searching(char juduldicari[], char pengarangdicari[], char genredicari[])
{
}

void hapustengah(char juduldihapus[])
{
}


int main()
{
    char juduldicari[100], pengarangdicari[100], genredicari[100], juduldihapus[100];
    bacadata();
    do
    {
        system("cls");
        cout << "\n====== MENU PERPUSTAKAAN ======";
        cout << "\n1. Tambah Buku Pertamamu";
        cout << "\n2. Tambah Buku";
        cout << "\n3. Lihat Daftar Buku";
        cout << "\n4. Cari Buku";
        cout << "\n5. Hapus Buku";
        cout << "\n0. Keluar";
        cout << "\nPilih menu: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih)
        {
        case 1:
            system("cls");
            if (kepala != NULL)
            {
                cout << "Linked list sudah dibuat.\n";
                getch();
            }
            else
            {
                char judul[100], pengarang[100], genre[100];
                int tahun;
                cout << "Judul: ";
                cin.getline(judul, 100);
                cout << "Pengarang: ";
                cin.getline(pengarang, 100);
                cout << "Genre: ";
                cin.getline(genre, 100);
                cout << "Tahun Terbit: ";
                cin >> tahun;
                buatlink(judul, pengarang, genre, tahun);
            }
            break;
        case 2:
            tambahakhir();
            break;
        case 3:
            tampilkanbuku();
            break;
        case 4:
            searching(juduldicari, pengarangdicari, genredicari);
            break;
        case 5:
            hapustengah(juduldihapus);
            getch();
            break;
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilih sesuai angka menu!\n";
            getch();
        }
    } while (pilih != 0);
}

