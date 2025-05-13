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

// Fungsi untuk filter tahun di case 3
void filterTahun() {
    Node *temp = head;
    int count = 0;

    // Hitung jumlah data
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0)  // Hanya barang orang lain
            count++;
        temp = temp->next;
    }

    if (count == 0) {
        printf("Tidak ada barang yang tersedia dari penjual lain.\n");
        return;
    }

    // Salin ke array
    Node array[count];
    temp = head;
    int i = 0;
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0)
            array[i++] = *temp;
        temp = temp->next;
    }

    // Urutkan berdasarkan tahun
    mergeSort(array, 0, count - 1);

    // Tampilkan hasil
    printf("\n--- Daftar Barang (Urut Tahun: Terlama ke Terbaru) ---\n");
    for (int j = 0; j < count; j++) {
        printf("%d. Nama : %s\n", j + 1, array[j].nama);
        printf("   Harga: Rp%d\n", array[j].harga);
        printf("   Tahun: %d\n", array[j].tahun);
        printf("   Penjual: %s\n", array[j].pemilik);
        printf("-------------------------------\n");
    }
}

void merge(Node arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Node L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].tahun >= R[j].tahun) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(Node arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
// End Merge Sort

//  fungsi untuk beli barang di case 4
void beliBarang() {
    if (head == NULL) {
        printf("Tidak ada barang yang tersedia.\n");
        return;
    }

    Node *temp = head;
    int no = 1;
    int found = 0;
    char daftarNama[100][30];

    printf("\n--- Daftar Barang yang Tersedia ---\n");
    while (temp != NULL) {
        if (strcmp(temp->pemilik, currentUser.username) != 0) { 
            printf("%d. Nama : %s\n", no, temp->nama);
            printf("   Harga: Rp%d\n", temp->harga);
            printf("   Tahun: %d\n", temp->tahun);
            printf("   Penjual: %s\n", temp->pemilik);
            printf("--------------------------\n");
            strcpy(daftarNama[no - 1], temp->nama);
            no++;
            found++;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("Tidak ada barang dari penjual lain untuk dibeli.\n");
        return;
    }

    char target[30];
    printf("Masukkan nama barang yang ingin dibeli: ");
    scanf(" %[^\n]", target);

    Node *curr = head;
    Node *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->nama, target) == 0 && strcmp(curr->pemilik, currentUser.username) != 0) { 
            printf("\nAnda telah membeli barang \"%s\" seharga Rp%d dari %s.\n", curr->nama, curr->harga, curr->pemilik);
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            masukkanHistory(curr->nama, curr->harga, curr->tahun, curr->pemilik);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Barang tidak ditemukan atau Anda tidak bisa membeli barang sendiri.\n");
}

void tambahKeKeranjang() {
    char namaCari[30];
    printf("Masukkan nama barang yang ingin dimasukkan ke keranjang: ");
    scanf(" %[^\n]", namaCari);

    Node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->nama, namaCari) == 0 && strcmp(temp->pemilik, currentUser.username) != 0) {
            Node *item = (Node *)malloc(sizeof(Node));
            if (!item) {
                printf("Gagal menambahkan ke keranjang.\n");
                return;
            }
            strcpy(item->nama, temp->nama);
            item->harga = temp->harga;
            item->tahun = temp->tahun;
            strcpy(item->pemilik, temp->pemilik);
            item->next = NULL;

            if (keranjang.rear == NULL) {
                keranjang.front = keranjang.rear = item;
            } else {
                keranjang.rear->next = item;
                keranjang.rear = item;
            }

            printf("Barang '%s' berhasil dimasukkan ke keranjang.\n", namaCari);
            return;
        }
        temp = temp->next;
    }
    printf("Barang tidak ditemukan atau Anda tidak bisa membeli barang sendiri.\n");
}

void tampilkanKeranjang() {
    if (keranjang.front == NULL) {
        printf("Keranjang kosong.\n");
        return;
    }
    Node *temp = keranjang.front;
    int i = 1;
    printf("\n--- Isi Keranjang Anda ---\n");
    while (temp != NULL) {
        printf("%d. Nama     : %s\n", i++, temp->nama);
        printf(" Harga      : Rp%d\n", temp->harga);
        printf(" Tahun      : %d\n", temp->tahun);
        printf(" Penjual    : %s\n", temp->pemilik);
        printf("---------------------------\n");
        temp = temp->next;
    }
}

void prosesKeranjang() {
    if (keranjang.front == NULL) {
        printf("Keranjang kosong. Tidak ada barang untuk diproses.\n");
        return;
    }
    Node *curr = keranjang.front;
    while (curr != NULL) {
        printf("Membeli '%s' seharga Rp%d dari %s...\n", curr->nama, curr->harga, curr->pemilik);
        masukkanHistory(curr->nama, curr->harga, curr->tahun, curr->pemilik);

        // Hapus dari daftar barang utama
        Node *ptr = head, *prev = NULL;
        while (ptr != NULL) {
            if (strcmp(ptr->nama, curr->nama) == 0 && strcmp(ptr->pemilik, curr->pemilik) == 0) {
                if (prev == NULL) head = ptr->next;
                else prev->next = ptr->next;
                free(ptr);
                break;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        Node *hapus = curr;
        curr = curr->next;
        free(hapus);
    }
    keranjang.front = keranjang.rear = NULL;
    printf("\nSemua barang di keranjang telah dibeli.\n");
}

void masukkanHistory(const char *nama, int harga, int tahun, const char *penjual) {
    Transaksi *baru = (Transaksi *)malloc(sizeof(Transaksi));
    if (baru == NULL) {
        printf("Gagal menyimpan riwayat transaksi.\n");
        return;
    }

    strcpy(baru->namaBarang, nama);
    strcpy(baru->penjual, penjual);
    baru->harga = harga;
    baru->tahun = tahun;
    baru->next = top;
    top = baru;

    printf("Transaksi berhasil dicatat dalam riwayat.\n");
}

// ============================ END BUY MENU ============================

void transactionHistoryMenu(){
    int choice;
    while(1) {
    printf("\n--- Riwayat Transaksi ---\n");
    printf("1. Tampilkan Riwayat\n");
    printf("2. Undo Transaksi Terakhir\n");
    printf("3. Kembali\n");
    printf("\nPilih opsi: ");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            if(top == NULL){
                printf("\nBelum ada riwayat transaksi\n");
        
            }else {
                printf("\n===== Riwayat Transaksi Anda ====\n");
                Transaksi* temp = top;
                int no = 1;
                while (temp != NULL){
                    printf("%d. Nama Barang  : %s\n", no++, temp->namaBarang);
                    printf("   Harga        : Rp%d\n", temp->harga);
                    printf("   Tahun        : %d\n", temp->tahun);
                    printf("   Penjual      : %s\n", temp->penjual);
                    printf("----------------------------------\n");
                    temp = temp->next;  
                }
            }
            break;

        case 2:
            if(top == NULL) {
                printf("\nTidak ada transaksi yang bisa di-undo\n");
            }else {
                Transaksi* temp = top;
                top = top->next;
                free(temp);
                printf("\nTransaksi terakhir berhasil di undo\n");
            }
            break;

        case 3:
            printf("Kembali ke menu utama\n");
            return;
        default:
            printf("Opsi tidak valid, silakan coba lagi\n");
            break;
        }
    }
}

// =======================Menu Pencarian & Sort (BST, Quick, Merge) ========================
void searchMenu() {
    int pilihan;

    do {
        printf("\n--- Cari Barang ---\n");
        printf("1. Cari Berdasarkan Nama\n");
        printf("2. Cari Berdasarkan Harga\n");
        printf("3. Urutkan Harga (Quick Sort)\n");
        printf("4. Urutkan Tahun (Merge Sort)\n");
        printf("5. Tampilkan Harga Tertinggi/Terendah (Heap)\n");
        printf("6. Kembali\n");
        printf("\nPilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            
            while (getchar() != '\n');
            printf("Input tidak valid! Hanya pilihan (1-6)\n");
            continue;
        }
        getchar();
        switch (pilihan) {
            case 1:
                cariBerdasarkanNama();
                break;
            case 2:
                cariBerdasarkanHarga();
                break;
            case 3:
                urutkanHargaQuickSort();
                break;
            case 4:
                urutkanTahunMergeSort();
                break;
            case 5:
                tampilkanHargaTertinggiTerendah();
                break;
            case 6:
                printf("Kembali ke menu utama.\n");
                break;
            default:
                printf("Input tidak valid! Hanya pilihan (1-6)\n");
        }

    } while (pilihan != 6);

}

void cariBerdasarkanNama() {
    char keyword[30];
    printf("Masukkan nama barang yang ingin dicari: ");
    scanf(" %[^\n]", keyword);

    Node *temp = head;
    bool ditemukan = false;
    int no = 1;
    while (temp != NULL) {
        if (strstr(temp->nama, keyword) != NULL) {
            printf("%d. Nama     : %s\n", no++, temp->nama);
            printf("  Harga     : Rp%d\n", temp->harga);
            printf("  Tahun     : %d\n", temp->tahun);
            printf("  Penjual   : %s\n", temp->pemilik);
            printf("-------------------------\n");
            ditemukan = true;
        }
        temp = temp->next;
    }
    if (!ditemukan) {
        printf("Barang dengan kata kunci '%s' tidak ditemukan.\n", keyword);
    }
}

void cariBerdasarkanHarga() {
    int hargaCari;
    printf("Masukkan harga barang yang ingin dicari: ");
    scanf("%d", &hargaCari);

    Node *temp = head;
    bool ditemukan = false;
    int no = 1;
    while (temp != NULL) {
        if (temp->harga == hargaCari) {
            printf("%d. Nama     : %s\n", no++, temp->nama);
            printf("  Harga     : Rp%d\n", temp->harga);
            printf("   Tahun    : %d\n", temp->tahun);
            printf("   Penjual  : %s\n", temp->pemilik);
            printf("-------------------------\n");
            ditemukan = true;
        }
        temp = temp->next;
    }
    if (!ditemukan) {
        printf("Barang dengan harga Rp%d tidak ditemukan.\n", hargaCari);
    }
}


void urutkanHargaQuickSort() {
    Node *temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        printf("Tidak ada barang.\n");
        return;
    }

    Node array[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        array[i] = *temp;
        temp = temp->next;
    }

    quickSort(array, 0, count - 1);

    printf("\n--- Barang Diurutkan Berdasarkan Harga (Tinggi ke Rendah) ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Nama    : %s\n", i + 1, array[i].nama);
        printf("  Harga    : Rp%d\n", array[i].harga);
        printf("  Tahun    : %d\n", array[i].tahun);
        printf("  Penjual  : %s\n", array[i].pemilik);
        printf("-------------------------\n");
    }
}

void urutkanTahunMergeSort() {
    Node *temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        printf("Tidak ada barang.\n");
        return;
    }

    Node array[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        array[i] = *temp;
        temp = temp->next;
    }

    mergeSort(array, 0, count - 1);

    printf("\n--- Barang Diurutkan Berdasarkan Tahun (Terlama ke Terbaru) ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Nama     : %s\n", i + 1, array[i].nama);
        printf(" Harga      : Rp%d\n", array[i].harga);
        printf(" Tahun      : %d\n", array[i].tahun);
        printf(" Penjual    : %s\n", array[i].pemilik);
        printf("-------------------------\n");
    }
}

void tampilkanHargaTertinggiTerendah() {
    if (head == NULL) {
        printf("Tidak ada barang.\n");
        return;
    }

    Node *temp = head;
    Node *maxNode = head;
    Node *minNode = head;

    while (temp != NULL) {
        if (temp->harga > maxNode->harga) maxNode = temp;
        if (temp->harga < minNode->harga) minNode = temp;
        temp = temp->next;
    }

    printf("\nHarga Tertinggi:\n");
    printf("Nama    : %s\n", maxNode->nama);
    printf("Harga   : Rp%d\n", maxNode->harga);
    printf("Tahun   : %d\n", maxNode->tahun);
    printf("Penjual : %s\n", maxNode->pemilik);

    printf("\nHarga Terendah:\n");
    printf("Nama    : %s\n", minNode->nama);
    printf("Harga   : Rp%d\n", minNode->harga);
    printf("Tahun   : %d\n", minNode->tahun);
    printf("Penjual : %s\n", minNode->pemilik);
}
// ======================= END Menu Pencarian & Sort (BST, Quick, Merge) ========================


void lihat_profil(User* currentUser) {
    printf("\n--- Profil Pengguna ---\n");
    printf("Username : %s\n", currentUser->username);
}

void lihat_laporan_keuntungan(const char* username){
    printf("\n--- Laporan Keuntungan ---\n");
    printf("Penjual %s telah mendapatkan total Rp.0 (fitur simulasi)\n", username);
}

void accountMenu(User* currentUser)  {
    int pilihan;
    do {
        printf("\n=== Akun Saya ===\n");
        printf("1. Lihat Profil\n");
        printf("2. Lihat Laporan Keuntungan\n");
        printf("3. Kembali\n");
        printf("\nPilih opsi (1-3): ");
        
        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid. Harap masukkan angka 1-3.\n");
            continue;
        }
        getchar();

        switch (pilihan) {
            case 1:
                lihat_profil(currentUser);
                break;
            case 2:
                lihat_laporan_keuntungan(currentUser->username);
                break;
            case 3:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}

// Menu utama
void mainMenu() {
    int menu;
    do
    {
        printf("\n==== Menu Utama ====\n");
        printf("1. Jual Barang\n");
        printf("2. Beli Barang\n");
        printf("3. Riwayat Transaksi\n");
        printf("4. Cari Barang\n");
        printf("5. Akun Saya & Laporan\n");
        printf("6. Logout\n");
        printf("\nPilih menu: ");
        if (scanf("%d", &menu) != 1) {
            
            while (getchar() != '\n');
            printf("Input tidak valid! Hanya pilihan (1-6)\n");
            continue;
        }
        getchar();

        switch (menu) {
        case 1:
            sellMenu();
            break;
        case 2:
            buyMenu();
            break;
        case 3:
            transactionHistoryMenu();
            break;
        case 4:
            searchMenu();
            break;
        case 5:
            accountMenu(&currentUser);
            break;
        case 6:
            printf("Logout berhasil!\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (menu != 6);
}
