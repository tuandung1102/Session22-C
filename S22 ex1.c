#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SV 100

typedef struct {
    char fullName[20];
    char ID[20];
    int age;
} Sinhvien;

Sinhvien sinhvien[MAX_SV];
int std = 0;

void readfile() {
    FILE *file = fopen("file_name.dat", "rb");
    if (file != NULL) {
        fread(&std, sizeof(int), 1, file);
        fread(sinhvien, sizeof(Sinhvien), std, file);
        fclose(file);
    }
}

void writefile() {
    FILE *file = fopen("file_name.dat", "wb");
    if (file != NULL) {
        fwrite(&std, sizeof(int), 1, file);
        fwrite(sinhvien, sizeof(Sinhvien), std, file);
        fclose(file);
    }
}

void printSinhvien() {
    for (int i = 0; i < std; i++) {
        printf("ID: %s, Name: %s, Age: %d\n", sinhvien[i].ID, sinhvien[i].fullName, sinhvien[i].age);
    }
}

void addSinhvien() {
    if (std < MAX_SV) {
        Sinhvien new_sinhvien;
        printf("Nhap ID: ");
        scanf("%s", new_sinhvien.ID);
        getchar();
        printf("Nhap ten: ");
        fgets(new_sinhvien.fullName, sizeof(new_sinhvien.fullName), stdin);
        new_sinhvien.fullName[strcspn(new_sinhvien.fullName, "\n")] = 0; 
        printf("Nhap tuoi: ");
        scanf("%d", &new_sinhvien.age);
        sinhvien[std] = new_sinhvien;
        std++;
        writefile();
    } else {
        printf("Mang sinh vien da day!\n");
    }
}

void editSinhvien() {
    char id[20];
    printf("Nhap ID cua sinh vien can sua: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < std; i++) {
        if (strcmp(sinhvien[i].ID, id) == 0) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(sinhvien[i].fullName, sizeof(sinhvien[i].fullName), stdin);
            sinhvien[i].fullName[strcspn(sinhvien[i].fullName, "\n")] = 0;
            printf("Nhap tuoi moi: ");
            scanf("%d", &sinhvien[i].age);
            writefile();
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi ID %s khong tim thay!\n", id);
    }
}

void deleteSinhvien() {
    char id[20];
    printf("Nhap ID cua sinh vien can xoa: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < std; i++) {
        if (strcmp(sinhvien[i].ID, id) == 0) {
            for (int j = i; j < std - 1; j++) {
                sinhvien[j] = sinhvien[j + 1];
            }
            std--;
            writefile();
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi ID %s khong tim thay!\n", id);
    }
}

void searchSinhvien() {
    char id[20];
    printf("Nhap ID sinh vien can tim: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < std; i++) {
        if (strcmp(sinhvien[i].ID, id) == 0) {
            printf("ID: %s, Name: %s, Age: %d\n", sinhvien[i].ID, sinhvien[i].fullName, sinhvien[i].age);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi ID %s khong tim thay!\n", id);
    }
}

void sortSinhvien() {
    for (int i = 0; i < std - 1; i++) {
        for (int j = i + 1; j < std; j++) {
            if (strcmp(sinhvien[i].ID, sinhvien[j].ID) > 0) {
                Sinhvien temp = sinhvien[i];
                sinhvien[i] = sinhvien[j];
                sinhvien[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep.\n");
    writefile();
}

void showmenu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printSinhvien();
                break;
            case 2:
                addSinhvien();
                break;
            case 3:
                editSinhvien();
                break;
            case 4:
                deleteSinhvien();
                break;
            case 5:
                searchSinhvien();
                break;
            case 6:
                sortSinhvien();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 7);
}

int main() {
    readfile();
    showmenu();
    return 0;
}

