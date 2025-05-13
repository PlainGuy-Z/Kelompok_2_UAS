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


#endif
