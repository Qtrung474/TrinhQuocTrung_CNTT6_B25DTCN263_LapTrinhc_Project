#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Product {
    char id[15];      // Ma san pham
    char name[50];    // Ten san pham
    char unit[15];    // Don vi tinh
    int quantity;     // So luong ton kho
    int status;       // Trang thai (1: Hoat dong, 0: Khoa)
};

typedef struct Product Product; 


Product products[100]; 
int pCount = 0;        

void clearBuffer();                 // Ham don rac bo nho dem
int findProductIndex(char *id);     // Ham tim kiem vi tri san pham
void F01_AddProduct();              // Chuc nang F01: Them moi
void F02_UpdateProduct();           // Chuc nang F02: Cap nhat

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
        
        // Dieu huong menu
        switch (choice) {
            case 1: F01_AddProduct(); break;
            case 2: F02_UpdateProduct(); break;
            case 0: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n"); break;
        }
    } while (choice != 0); // Lap lai neu chua chon 0

    return 0;
}



// Ham xoa bo nho dem (Tranh loi troi lenh khi nhap chuoi sau so)
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ham tim kiem: Tra ve vi tri (index) neu thay, -1 neu khong thay
int findProductIndex(char *id) {
    for (int i = 0; i < pCount; i++) {
        // strcmp tra ve 0 neu 2 chuoi giong het nhau
        if (strcmp(products[i].id, id) == 0) return i;
    }
    return -1; // Khong tim thay
}

// Chuc nang F01: Them hang hoa moi
void F01_AddProduct() {
    printf("\n--- [F01] THEM HANG HOA MOI ---\n");
    Product p; // Bien tam de luu thong tin nhap vao
    
    printf("Nhap ma hang: ");
    scanf("%s", p.id);
    clearBuffer(); // Xoa Enter thua sau khi nhap ma

    // Kiem tra ma da ton tai chua
    if (findProductIndex(p.id) != -1) {
        printf("LOI: Ma hang nay da ton tai!\n");
        return; // Dung ham tai day
    }

    printf("Nhap ten hang: ");
    fgets(p.name, 50, stdin);
    // Xoa ky tu xuong dong (\n) o cuoi chuoi do fgets lay vao
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Nhap don vi tinh: ");
    scanf("%s", p.unit);

    printf("Nhap so luong khoi tao: ");
    scanf("%d", &p.quantity);

    // Kiem tra so luong am
    if (p.quantity < 0) {
        printf("LOI: So luong khong duoc am!\n");
        return;
    }

    p.status = 1; // Mac dinh la trang thai Hoat dong
    
    // Luu hang vao mang va tang bien dem pCount len 1
    products[pCount++] = p;
    printf("-> Them moi thanh cong!\n");
}

// Chuc nang F02: Cap nhat ten va don vi tinh
void F02_UpdateProduct() {
    printf("\n--- [F02] CAP NHAT THONG TIN ---\n");
    char id[15];
    printf("Nhap ma hang can sua: ");
    scanf("%s", id);
    clearBuffer();

    // Tim vi tri cua hang trong kho
    int idx = findProductIndex(id);
    if (idx == -1) {
        printf("LOI: Khong tim thay ma hang!\n");
        return;
    }

    //Cap nhat Ten hang
    printf("Ten hien tai: %s. Nhap ten moi (Enter de giu nguyen): ", products[idx].name);
    char tempName[50];
    fgets(tempName, 50, stdin);
    
    // Logic: Neu do dai > 1 tuc la nguoi dung co go chu (khong phai chi bam Enter)
    if (strlen(tempName) > 1) {
        tempName[strcspn(tempName, "\n")] = 0; // Xoa Enter
        strcpy(products[idx].name, tempName);  // Copy ten moi vao
    }

    // Cap nhat Don vi tinh
    printf("Don vi hien tai: %s. Nhap don vi moi (Enter de giu nguyen): ", products[idx].unit);
    char tempUnit[15];
    fgets(tempUnit, 15, stdin);
    
    if (strlen(tempUnit) > 1) { 
        tempUnit[strcspn(tempUnit, "\n")] = 0;
        strcpy(products[idx].unit, tempUnit);
    }

    printf("-> Cap nhat thanh cong!\n");
}
