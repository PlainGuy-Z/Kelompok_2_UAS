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

void hapusBarang() {
    if (head == NULL) {
        printf("Tidak ada barang untuk dihapus.\n");
        return;
    }

    char target[30];
    printf("Masukkan nama barang yang ingin dihapus: ");
    scanf(" %[^\n]", target);

    Node *curr = head;
    Node *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->nama, target) == 0 && strcmp(curr->pemilik, currentUser.username) == 0) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Barang \"%s\" berhasil dihapus.\n", target);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Barang dengan nama \"%s\" tidak ditemukan.\n", target);
}
//========================== END SELL MENU ===========================


// ============================ BUY MENU ============================
void buyMenu() {
    int pilihan;
    do {
        printf("\n--- Menu Beli Barang ---\n");
        printf("1. Lihat Semua Barang\n");
        printf("2. Filter Berdasarkan Harga\n");
        printf("3. Filter Berdasarkan Tahun\n");
        printf("4. Proses Pembelian\n");
        printf("5. tambah ke keranjang\n");
        printf("6. Lihat isi keranjang\n");
        printf("7. proses keranjang\n");
        printf("8. Kembali\n");
        printf("\nPilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            
            while (getchar() != '\n');
            printf("Input tidak valid! Hanya pilihan (1-8)\n");
            continue;
        }
        getchar();

        switch (pilihan) {
            case 1:
                tampilBarang();
                break;
            case 2:
                filterHarga();
                break;
            case 3:
                filterTahun();
                break;
            case 4:
                beliBarang();
                break;
            case 5:
                tambahKeKeranjang();
                break;
            case 6:
                tampilkanKeranjang();
                break;
            case 7:
                prosesKeranjang();
                break;
            case 8:
                printf("Kembali ke menu utama.\n");
                break;
            default:
                printf("Input tidak valid! Hanya pilihan (1-8)\n");
        }

    } while (pilihan != 8);
}

//Fungsi untuk menampilkan barang di case 1
void tampilBarang() {
    Node *temp = head;
    bool ditemukan = false;

    if (temp == NULL){
        printf("Tidak ada barang yang tersedia.\n");
        return;
    }

    printf("\n--- Daftar Barang ---\n");
    int no = 1;
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0) {
            printf("%d. Nama : %s\n", no, temp->nama);
            printf("   Harga: Rp%d\n", temp->harga);
            printf("   Tahun: %d\n", temp->tahun);
            printf("   Penjual: %s\n", temp->pemilik);
            printf("--------------------------\n");
            ditemukan = true;
            no++;
        }
        temp = temp->next;
    }
    if (!ditemukan) {
        printf("Tidak ada barang yang tersedia untuk dibeli.\n");
    }

};
// End tampilkan barang

// fungsi untuk filter harga di case 2
void filterHarga() {
    Node *temp = head;

    int count = 0;

    while (temp !=NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0) // Hanya barang orang lain
            count++;
             temp = temp->next;

    }

    if (count == 0) {
        printf("Tidak ada barang yang tersedia dari penjual lain.\n");
        return;
    }

    Node array[count];
    temp = head;
    int i = 0;
    
    // Salin hanya barang dari penjual lain
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0) {
            array[i++] = *temp;
        }
        temp = temp->next;
    }

        quickSort(array, 0, count - 1);
        printf("\n--- Daftar Barang (Diurutkan Berdasarkan Harga) ---\n");
        for (int i = 0; i< count; i++) {
            printf("%d. Nama: %s\n", i + 1, array[i].nama);
            printf("Harga: %d\n", array[i].harga);
            printf("Tahun: %d\n", array[i].tahun);
            printf("---------------------\n");
        }
};

//Quick Sort
int partition(Node arr[], int low, int high) { 
    int pivot = arr[high].harga; 
    int i = (low - 1); 

    for (int j = low; j < high; j++) { 
        if (arr[j].harga > pivot) { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}

void quickSort(Node arr[], int low, int high) { 
    if (low < high) { 
        int pi = partition(arr, low, high); 

        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

void swap(Node *a, Node *b) { 
    Node temp = *a; 
    *a = *b; 
    *b = temp; 
}
// end fungsi untuk filter harga di case 2
