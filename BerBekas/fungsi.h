#ifndef TUGAS_KELOMPOKSDA_HEADER_H
#define TUGAS_KELOMPOKSDA_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define FILENAME "users.txt"

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

extern User currentUser;

typedef struct Node {
    char nama[30];
    int harga;
    int tahun;
    char pemilik[30];
    struct Node *next;
}Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;


typedef struct Transaksi {
    char namaBarang[30];
    int harga;
    int tahun;
    char penjual[30];
    struct Transaksi *next;
} Transaksi;

void mainMenu();

void loginMenu();
int loginUser();
void registerUser();


//di sini  linked list ditambahin
void tambahBarang();
void tampilBarangSaya();
void hapusBarang();
void sellMenu();


//============================ START BUY MENU ============================
void buyMenu();
void tampilBarang();


void swap(Node *a, Node *b);
int partition(Node arr[], int low, int high);
void quickSort(Node arr[], int low, int high);
void filterHarga();

#endif
