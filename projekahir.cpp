#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using namespace std;

//struct untuk menyimpan informasi buku
struct Buku
{
    char judul[100], pengarang[100], genre[100];
    int tahunterbit;
    Buku *next;
};

//variabel global
int jmlbuku = 0;
int pilih;


Buku *kepala = NULL, *ekor = NULL, *baru = NULL, *bantu = NULL;

//fungsi untuk membaca data dari file dan menyimpan ke dalam linked list
void bacadata()
{
    FILE *databuku = fopen("databuku.dat", "rb");
    if (databuku == NULL)
    {
        cout << "Gagal membuka file!\n";
        fclose(databuku);
    }
    
    kepala = ekor = NULL;
    Buku bukutemp; //variabel sementara untuk membaca data dari file

    
    while (fread(&bukutemp, sizeof(Buku), 1, databuku))
    {
        baru = new Buku();
        strcpy(baru->judul, bukutemp.judul);
        strcpy(baru->pengarang, bukutemp.pengarang);
        strcpy(baru->genre, bukutemp.genre); //karena array char maka menggunakan strcpy untuk menyalin karakter satu per satu dari string sumber ke string tujuan
        baru->tahunterbit = bukutemp.tahunterbit;
        baru->next = NULL; 

        if (kepala == NULL)
        {
            kepala = ekor = baru; //jika ini buku pertama, maka node buku baru akan dijadikan kepala dan ekor
        }
        else
        {
            ekor->next = baru; //jika sudah ada buku lain, maka node buku baru disambungkan ke bagian belakang
            ekor = baru;
        }
        jmlbuku++; //menambahkan angka penghitung buku, jika berhasil memasukkan 
    }

    fclose(databuku);
}

void bubblesort()
{
    if (kepala == NULL)
        return;

    bool swapped; //untuk menandai apakah ada pertukaran data
    Buku *ptr1;
    Buku *lptr = NULL;

    do
    {
        swapped = false; //set awal bahwa belum ada yang ditukar
        ptr1 = kepala; //memulai dari node pertama

        while (ptr1->next != lptr)//membandingkan sampai sebelum batas akhirapa
        {
            if (strcmp(ptr1->judul, ptr1->next->judul) > 0)//strcmp adalah fungsi untuk membandingkan dua string, hanya bisa digunakan pada array char
                //jika data judul buku pertama lebih besar dari data judul buku selanjutnya maka akan dilakukan suatu kondisi
            {
                //menukar semua isi data buku
                swap(ptr1->judul, ptr1->next->judul);
                swap(ptr1->pengarang, ptr1->next->pengarang);
                swap(ptr1->genre, ptr1->next->genre);
                swap(ptr1->tahunterbit, ptr1->next->tahunterbit);
                swapped = true; //ada penukaran berarti masih perlu iterasi
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped); //mengulangi jika ada penukaran
}

void buatlink(char judul[], char pengarang[], char genre[], int tahun)
{
    baru = new Buku(); //membuat node
    //menyalin informasi buku
    strcpy(baru->judul, judul); 
    strcpy(baru->pengarang, pengarang);
    strcpy(baru->genre, genre);
    baru->tahunterbit = tahun;
    baru->next = NULL;

    kepala = ekor = baru; //menetapkan node baru sebagai kepala dan ekor karena ini buku pertama

    FILE *databuku = fopen("databuku.dat", "ab");
    if (databuku != NULL)
    {
        fwrite(baru, sizeof(Buku), 1, databuku); //menulis data buku ke dalam file sehingga dapat tersimpan
        fclose(databuku);
        jmlbuku++;
    }

    cout << "\nBuku pertama berhasil ditambahkan!" << endl;
    getch();
}

void tambahakhir()
{
    char lagi; //variabel apakah pengguna ingin menambahkan buku lagi
    system("cls");
    FILE *databuku = fopen("databuku.dat", "ab"); //append binary, data baru ditulis di akhir file tanpa menghapus data lama
    if (databuku == NULL)
    {
        cout << "Gagal membuka file!" << endl; //erorr handling jika gagal membuka file
        return; 
    }

    do
    {
        Buku bukutemp;
        cout << "\nData buku ke-" << jmlbuku + 1 << endl;
        cout << "Judul    : ";
        cin.getline(bukutemp.judul, 100);
        cout << "Pengarang: ";
        cin.getline(bukutemp.pengarang, 100);
        cout << "Genre    : ";
        cin.getline(bukutemp.genre, 100);
        cout << "Tahun    : ";
        cin >> bukutemp.tahunterbit;

        fwrite(&bukutemp, sizeof(Buku), 1, databuku); //menulis data dari bukutemp ke dalam file

        baru = new Buku(); //membuat node baru dalam linked list dengan menyalin data dari bukutemp
        strcpy(baru->judul, bukutemp.judul);
        strcpy(baru->pengarang, bukutemp.pengarang);
        strcpy(baru->genre, bukutemp.genre);
        baru->tahunterbit = bukutemp.tahunterbit;
        baru->next = NULL;

        if (kepala == NULL) //jika linked list kosong maka node baru tadi menjadi kepala dan ekor
        {
            kepala = ekor = baru;
        }
        else
        {
            ekor->next = baru;
            ekor = baru;
        }

        cout << "\nData Buku berhasil ditambahkan!" << endl;
        jmlbuku++;
        
        cout << "Tambah buku lagi? (y/n): ";
        cin >> lagi;
        cin.ignore();
    } while (lagi == 'Y' || lagi == 'y');

    fclose(databuku);
    cout << "\nTekan apa saja untuk melanjutkan..";
    getch();
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
        bubblesort(); //melakukan sorting terlebih dahulu sebelum ditampilkan

        bantu = kepala;
        int no = 1;
        while (bantu != NULL) //selama bantu tidak kosong, maka akan menampilkan buku kemudian bantu berpindah ke bantu->next
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
    Buku *temp = kepala;
    bool found = false;

    while (temp != NULL)
    {
        if (strcmp(temp->judul, juduldicari) == 0 || strcmp(temp->pengarang, pengarangdicari) == 0 || strcmp(temp->genre, genredicari) == 0) //strcmp untuk membandingkan string
        {
            system("cls");
            cout << "Buku ditemukan!\n";
            cout << "Judul       : " << temp->judul << endl;
            cout << "Pengarang   : " << temp->pengarang << endl;
            cout << "Genre       : " << temp->genre << endl;
            cout << "Tahun Terbit: " << temp->tahunterbit << endl;
            cout << "---------------------------------" << endl;
            getch();
            found = true;
        }
        temp = temp->next;
    }

    if (!found) 
    {
        system("cls");
        cout << "\nBuku tidak ditemukan dalam daftar. Tekan apa saja untuk kembali...\n";
        getch();
    }
}

void searching(char juduldicari[], char pengarangdicari[], char genredicari[])
{
    int pilihan;
    do
    {
        system("cls");
        cout << "===== MENU SEARCHING =====" << endl;
        cout << "1. Cari Judul Buku " << endl;
        cout << "2. Cari Pengarang " << endl;
        cout << "3. Cari Genre" << endl;
        cout << "0. Kembali menu utama" << endl;
        cout << "Masukkan pilihan : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan judul buku yang dicari: ";
            cin.getline(juduldicari, 100);
            sequential_search(juduldicari, pengarangdicari, genredicari);
            break;
        case 2:
            cout << "Masukkan pengarang buku yang dicari: ";
            cin.getline(pengarangdicari, 100);
            sequential_search(juduldicari, pengarangdicari, genredicari);
            break;
        case 3:
            cout << "Masukkan genre buku yang dicari: ";
            cin.getline(genredicari, 100);
            sequential_search(juduldicari, pengarangdicari, genredicari);
            break;
        case 0:
            break;
        default:
            cout << "Pilih sesuai angka menu!\n";
            getch();
        }
    } while (pilihan != 0);
}

void hapustengah(char juduldihapus[])
{
    system("cls");
    FILE *databuku = fopen("databuku.dat", "wb");
    if (databuku == NULL) {
        cout << "Gagal menyimpan file!" << endl;
        return;
    }
    cout << "Masukkan judul buku yang akan dihapus: ";
    cin.getline(juduldihapus, 100);

    if (kepala == NULL) //jika linked list kosong
    {
        cout << "Linked List kosong!\n";
        return;
    }

    if (strcmp(kepala->judul, juduldihapus) == 0) //jika buku yang dihapus merupakan kepala
    {
        Buku *hapus = kepala;
        kepala = kepala->next;
        delete hapus;
        cout << "Buku dengan judul '" << juduldihapus << "' berhasil dihapus dari daftar!\n";
        return;
    }

    //pencarian untuk menghapus node di tengah dan di akhir
    Buku *bantu = kepala; 

    while (bantu->next != NULL && strcmp(bantu->next->judul, juduldihapus) != 0)
    {
        bantu = bantu->next;
    }

    if (bantu->next == NULL)
    {
        cout << "Buku dengan judul '" << juduldihapus << "' tidak ditemukan!\n";
        return;
    }

    Buku *hapus = bantu->next;
    bantu->next = hapus->next;
    delete hapus;
    cout << "Buku dengan judul '" << juduldihapus << "' berhasil dihapus dari daftar!\n";
    Buku *temp = kepala;
    while (temp != NULL) {
        fwrite(temp, sizeof(Buku), 1, databuku);
        temp = temp->next;
    }

    fclose(databuku);
    jmlbuku--;
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

