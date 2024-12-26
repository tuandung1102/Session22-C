#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

void read_file() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        fread(&account_count, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), account_count, file);
        fclose(file);
    }
}

void write_file() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(&account_count, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), account_count, file);
        fclose(file);
    }
}

int is_username_taken(const char *username) {
    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_account() {
    if (account_count >= MAX_ACCOUNTS) {
        printf("Danh sach tai khoan da day!\n");
        return;
    }

    Account new_account;
    char confirm_password[50];

    printf("Nhap tai khoan: ");
    scanf("%s", new_account.username);

    if (is_username_taken(new_account.username)) {
        printf("Tai khoan da ton tai! Vui long thu lai.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", new_account.password);

    printf("Xac nhan mat khau: ");
    scanf("%s", confirm_password);

    if (strcmp(new_account.password, confirm_password) != 0) {
        printf("Mat khau xac nhan khong trung khop!\n");
        return;
    }

    accounts[account_count++] = new_account;
    write_file();
    printf("Dang ky thanh cong!\n");
}

void login() {
    char username[50], password[50];

    printf("Nhap tai khoan: ");
    scanf("%s", username);

    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return;
        }
    }

    printf("Dang nhap that bai! Tai khoan hoac mat khau sai.\n");
}

void show_menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                register_account();
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 3);
}

int main() {
    read_file();
    show_menu();
    return 0;
}

