#include "berbekas.h"

User currentUser;
Node *head = NULL;
Transaksi *top = NULL; 
Queue keranjang = {NULL, NULL};

void registerUser () {
    User user, temp;
    FILE *file = fopen(FILENAME, "a+");
    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    //cek duplikasi username
    rewind(file);
    while (fscanf(file, "%s %s",  temp.username, temp.password) !=EOF){
        if (strcmp(temp.username, user.username) == 0){
            printf("Username sudah digunakan. Silakan gunakan username lain\n");
            fclose(file);
            return;
        }
    }
    //simpan jika tidak duplikat
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);
    printf("\nRegistration successful!\n");
}


int loginUser() {
    User user;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            found = 1;
            // Tambahkan ini untuk menyimpan user yang login
            strcpy(currentUser.username, user.username);
            strcpy(currentUser.password, user.password);
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("\nLogin successful!\n");
        return 1;
    } else {
        printf("\nInvalid username or password.\n");
        return 0;
    }
}

void loginMenu() {
    if (loginUser()) {
        mainMenu();
    } else {
        printf("\nGagal login. Kembali ke menu awal.\n");
    }
}

//========================= SELL MENU ===========================
void sellMenu() {
    int pilihan;
    do {
        printf("\n--- Jual Barang ---\n");
        printf("1. Tambah Barang\n");
        printf("2. Lihat Daftar Barang Saya\n");
        printf("3. Hapus Barang\n");
        printf("4. Kembali\n");
        printf("\nPilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            
            while (getchar() != '\n');
            printf("Input tidak valid! Hanya pilihan (1-6)\n");
            continue;
        }
        getchar();

    
        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilBarangSaya();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                printf("Kembali ke menu utama.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }while(pilihan != 4);

}

void tambahBarang() {
    Node *baru = (Node *)malloc(sizeof(Node));
    if (!baru) {
        printf("Gagal mengalokasikan memori.\n");
        return;
    }

    printf("Masukkan nama barang: ");
    scanf(" %[^\n]", baru->nama);
    printf("Masukkan harga barang: ");
    scanf("%d", &baru->harga);
    printf("Masukkan tahun keluaran barang: ");
    scanf("%d", &baru->tahun);


    strcpy(baru->pemilik, currentUser.username);
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    printf("\nBarang berhasil ditambahkan ke daftar!\n");
}

void tampilBarangSaya() {
    if (head == NULL) {
        printf("Tidak ada barang yang tersedia.\n");
        return;
    }

    Node *temp = head;
    int no = 1;
    bool ditemukan = false;

    printf("\n--- Daftar Barang Saya ---\n");
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) == 0) {
            printf("%d. Nama : %s\n", no, temp->nama);
            printf("   Harga: Rp%d\n", temp->harga);
            printf("   Tahun: %d\n", temp->tahun);
            printf("--------------------------\n");
            ditemukan = true;
            no++;
        }
        temp = temp->next;
    }
    if (!ditemukan) {
        printf("Anda belum menambah barang apapun.\n");
    }
}