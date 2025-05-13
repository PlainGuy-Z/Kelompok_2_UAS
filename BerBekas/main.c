#include "fungsi.h"

int main() {
    int pilihan;
    do {
        printf("\n==== Selamat Datang di BerBekas.id ====\n");
        printf("1. Login\n");
        printf("2. Registrasi\n");
        printf("3. Keluar\n");
        printf("\nPilih opsi: ");
        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid! Hanya pilihan (1-3)\n");
            continue;
        }
        getchar();
        
        switch (pilihan) {
            case 1:
                loginMenu();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("---- Terima kasih telah menggunakan aplikasi ini ----\n\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);

    return 0;
}
