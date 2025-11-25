#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    char id[15];
    char name[50];
    char unit[15];
    int quantity;
    int status;// trang thai 
};

typedef struct Product Product;// san pham 

Product products[100];
int pCount = 0;

void clearBuffer();
int findProductIndex(char *id);
void F01_AddProduct();
void F02_UpdateProduct();

int main() {
    int choice;
    do {
        printf("\n==========================================\n");
        printf("   QUAN LY HANG HOA (F01 & F02)\n");
        printf("==========================================\n");
        printf("1. F01 - Them hang hoa moi\n");
        printf("2. F02 - Cap nhat thong tin\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: F01_AddProduct(); break;
            case 2: F02_UpdateProduct(); break;
            case 0: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n"); break;
        }
    } while (choice != 0);

    return 0;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int findProductIndex(char *id) {
    for (int i = 0; i < pCount; i++) {
        if (strcmp(products[i].id, id) == 0) return i;
    }
    return -1;
}

void F01_AddProduct() {
    printf("\n--- [F01] THEM HANG HOA MOI ---\n");
    Product p;
    
    printf("Nhap ma hang: ");
    scanf("%s", p.id);
    clearBuffer();

    if (findProductIndex(p.id) != -1) {
        printf("LOI: Ma hang nay da ton tai!\n");
        return;
    }

    printf("Nhap ten hang: ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Nhap don vi tinh: ");
    scanf("%s", p.unit);

    printf("Nhap so luong khoi tao: ");
    scanf("%d", &p.quantity);

    if (p.quantity < 0) {
        printf("LOI: So luong khong duoc am!\n");
        return;
    }

    p.status = 1; 
    products[pCount++] = p;
    printf("-> Them moi thanh cong!\n");
}

void F02_UpdateProduct() {
    printf("\n--- [F02] CAP NHAT THONG TIN ---\n");
    char id[15];
    printf("Nhap ma hang can sua: ");
    scanf("%s", id);
    clearBuffer();

    int idx = findProductIndex(id);
    if (idx == -1) {
        printf("LOI: Khong tim thay ma hang!\n");
        return;
    }

    printf("Ten hien tai: %s. Nhap ten moi (Enter de giu nguyen): ", products[idx].name);
    char tempName[50];
    fgets(tempName, 50, stdin);
    if (strlen(tempName) > 1) {
        tempName[strcspn(tempName, "\n")] = 0;
        strcpy(products[idx].name, tempName);
    }

    printf("Don vi hien tai: %s. Nhap don vi moi (Enter de giu nguyen): ", products[idx].unit);
    char tempUnit[15];
    fgets(tempUnit, 15, stdin);
    if (strlen(tempUnit) > 1) { 
        tempUnit[strcspn(tempUnit, "\n")] = 0;
        strcpy(products[idx].unit, tempUnit);
    }

    printf("-> Cap nhat thanh cong!\n");
}
