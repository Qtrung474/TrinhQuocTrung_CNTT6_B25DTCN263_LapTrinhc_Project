#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>  


struct Product {
    char id[15];     // Ma hang hoa (chuoi)
    char name[50];   // Ten hang hoa
    char unit[15];   // Don vi tinh (cai, hop, kg...)
    int quantity;    // So luong ton kho
    int status;      // Trang thai: 1 = Dang hoat dong, 0 = Da khoa (Ngung hoat dong)
};

// Dinh nghia lai ten struct cho ngan gon
typedef struct Product Product;



Product products[100]; 
int pCount = 0;       



void clearBuffer();               // Xoa bo nho dem ban phim
void trim(char *s);               // Xoa khoang trang thua dau/cuoi chuoi
int isNumber(char *s);            // Kiem tra mot chuoi co phai la so khong
int findProductIndex(char *id);   // Tim vi tri san pham trong mang theo ID
void F01_AddProduct();            // Chuc nang 1: Them moi
void F02_UpdateProduct();         // Chuc nang 2: Cap nhat
void F03_ChangeStatus();          // Chuc nang 3: Doi trang thai
void F04_SearchProduct();         // Chuc nang 4: Tim kiem


int main() {
    int choice;
    do {
        // Hien thi Menu
        printf("\n==========================================\n");
        printf("    QUAN LY HANG HOA\n");
        printf("==========================================\n");
        printf("1. F01 - Them hang hoa moi\n");
        printf("2. F02 - Cap nhat thong tin\n");
        printf("3. F03 - Thay doi trang thai (Khoa/Mo)\n");
        printf("4. F04 - Tim kiem hang hoa\n");
        printf("5. F05 - Danh sach hang hoa\n");
        printf("6. F06 - Sap xep hang hoa\n");
        printf("7. F07 - Nhap/Xuat kho\n");
        printf("8. F08 - Lich su giao dich\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("Lua chon cua ban: ");

        // Xu ly nhap lieu cho bien choice de tranh loi lap vo han neu nhap chu
        if (scanf("%d", &choice) != 1) {
            printf("Nhap sai! Vui long nhap so.\n");
            clearBuffer(); // Xoa bo nho dem neu nhap sai dinh dang
            choice = -1;   // Gan gia tri sai de vong lap tiep tuc
        } else {
            clearBuffer(); // Xoa bo nho dem (ky tu \n con sot lai) sau khi nhap so
        }

        // Dieu huong chuc nang
        switch (choice) {
            case 1: F01_AddProduct(); break;
            case 2: F02_UpdateProduct(); break;
            case 3: F03_ChangeStatus(); break;
            case 4: F04_SearchProduct(); break;
            case 0: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n"); break;
        }
    } while (choice != 0); // Lap lai cho den khi nguoi dung chon 0

    return 0;
}




void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void trim(char *s) {
    char *p = s;
    int l = strlen(p);
    while(l > 0 && isspace(p[l - 1])) p[--l] = 0;
    while(*p && isspace(*p)) p++, l--;
    memmove(s, p, l + 1);
}

// Ham kiem tra chuoi so: Tra ve 1 neu toan bo la so, 0 neu co chu
int isNumber(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

// Ham tim kiem Index (vi tri) cua san pham trong mang dua vao ID
// Tra ve: index (0 den pCount-1) neu thay, -1 neu khong thay
int findProductIndex(char *id) {
    for (int i = 0; i < pCount; i++) {
        if (strcmp(products[i].id, id) == 0) return i;
    }
    return -1;
}


//  Them hang hoa moi
void F01_AddProduct() {
    printf("\n--- [F01] THEM HANG HOA MOI ---\n");
    Product p;
    char numStr[20]; 

    // Nhap Ma hang (Kiem tra trung lap va khong duoc de trong)
    do {
        printf("Nhap ma hang: ");
        fgets(p.id, 15, stdin);
        trim(p.id);

        if (strlen(p.id) == 0) {
            printf("-> LOI: Ma hang khong duoc de trong!\n");
        } else if (findProductIndex(p.id) != -1) {
            printf("-> LOI: Ma hang '%s' da ton tai! Vui long nhap ma khac.\n", p.id);
            p.id[0] = '\0'; // Reset ma de nhap lai
        }
    } while (strlen(p.id) == 0);

    // Nhap Ten hang
    do {
        printf("Nhap ten hang: ");
        fgets(p.name, 50, stdin);
        trim(p.name);
        if (strlen(p.name) == 0) printf("-> LOI: Ten hang khong duoc de trong!\n");
    } while (strlen(p.name) == 0);

    // Nhap Don vi tinh
    do {
        printf("Nhap don vi tinh: ");
        fgets(p.unit, 15, stdin);
        trim(p.unit);
        if (strlen(p.unit) == 0) printf("-> LOI: Don vi tinh khong duoc de trong!\n");
    } while (strlen(p.unit) == 0);

    //Nhap So luong (Kiem tra phai la so nguyen)
    int valid = 0;
    do {
        printf("Nhap so luong ton kho: ");
        fgets(numStr, 20, stdin);
        trim(numStr);

        if (strlen(numStr) == 0) {
            printf("-> LOI: So luong khong duoc de trong!\n");
        } else if (!isNumber(numStr)) {
            printf("-> LOI: Vui long chi nhap so nguyen duong!\n");
        } else {
            p.quantity = atoi(numStr);
            valid = 1; 
        }
    } while (!valid);

    
    p.status = 1; // Mac dinh la Dang hoat dong
    products[pCount++] = p; 
    printf("-> Them moi thanh cong! (Ma: %s - SL: %d)\n", p.id, p.quantity);
}

//  Cap nhat thong tin hang hoa
void F02_UpdateProduct() {
    printf("\n--- [F02] CAP NHAT THONG TIN ---\n");
    char id[15];

    printf("Nhap ma hang can sua: ");
    fgets(id, 15, stdin);
    trim(id);

    int idx = findProductIndex(id);
    if (idx == -1) {
        printf("LOI: Khong tim thay ma hang '%s'!\n", id);
        return;
    }

    // Cap nhat Ten hang
    printf("Ten hien tai: %s\n", products[idx].name);
    printf("Nhap ten moi (Enter de giu nguyen): ");
    char tempName[50];
    fgets(tempName, 50, stdin);
    trim(tempName);

    if (strlen(tempName) > 0) {
        strcpy(products[idx].name, tempName);
        printf("-> Ten da duoc cap nhat.\n");
    } else {
        printf("-> Giu nguyen ten cu.\n");
    }

    // Cap nhat Don vi tinh
    printf("Don vi hien tai: %s\n", products[idx].unit);
    printf("Nhap don vi moi (Enter de giu nguyen): ");
    char tempUnit[15];
    fgets(tempUnit, 15, stdin);
    trim(tempUnit);

    if (strlen(tempUnit) > 0) {
        strcpy(products[idx].unit, tempUnit);
        printf("-> Don vi da duoc cap nhat.\n");
    } else {
        printf("-> Giu nguyen don vi cu.\n");
    }

    printf("\n=> Hoan tat cap nhat thong tin cho san pham %s!\n", id);
}

// Thay doi trang thai (Khoa / Mo khoa)
void F03_ChangeStatus() {
    printf("\n--- [F03] THAY DOI TRANG THAI ---\n");
    char id[15];

    printf("Nhap ma hang can khoa/mo khoa: ");
    fgets(id, 15, stdin);
    trim(id);

    int idx = findProductIndex(id);
    if (idx == -1) {
        printf("LOI: Khong tim thay ma hang '%s'!\n", id);
        return;
    }

    // Dao nguoc trang thai: 1 -> 0 hoac 0 -> 1
    if (products[idx].status == 1) {
        products[idx].status = 0;
        printf("-> Da chuyen trang thai sang: NGUNG HOAT DONG (KHOA)\n");
    } else {
        products[idx].status = 1;
        printf("-> Da chuyen trang thai sang: DANG HOAT DONG\n");
    }
}

//Tim kiem hang hoa
void F04_SearchProduct() {
    printf("\n--- [F04] TIM KIEM HANG HOA ---\n");
    char choiceStr[10];
    int type;

    printf("1. Tim theo Ma hang (ID)\n");
    printf("2. Tim theo Ten hang (Name)\n");
    printf("Chon phuong thuc tim: ");
    
    fgets(choiceStr, 10, stdin);
    trim(choiceStr);
    
    if (!isNumber(choiceStr)) type = 0;
    else type = atoi(choiceStr);

    if (type == 1) {
        // Tim chinh xac theo ID
        char id[15];
        printf("Nhap Ma hang can tim: ");
        fgets(id, 15, stdin);
        trim(id);

        int idx = findProductIndex(id);
        if (idx != -1) {
            printf("\nKET QUA TIM KIEM:\n");
            printf("Ma: %s | Ten: %s | Don vi: %s | SL: %d | Trang thai: %s\n", 
                   products[idx].id, 
                   products[idx].name, 
                   products[idx].unit, 
                   products[idx].quantity,
                   products[idx].status == 1 ? "Hoat dong" : "Khoa");
        } else {
            printf("-> Khong tim thay ma hang '%s'.\n", id);
        }

    } else if (type == 2) {
        // Tim tuong doi theo Ten (chua tu khoa)
        char keyword[50];
        printf("Nhap Ten hang can tim: ");
        fgets(keyword, 50, stdin);
        trim(keyword);

        printf("\nKET QUA TIM KIEM:\n");
        int found = 0;
        for (int i = 0; i < pCount; i++) {
            // strstr: Tim chuoi con (Keyword) trong chuoi me (Name)
            // Tra ve NULL neu khong tim thay
            if (strstr(products[i].name, keyword) != NULL) {
                printf("- [%s] %s (SL: %d) - %s\n", 
                       products[i].id, 
                       products[i].name, 
                       products[i].quantity,
                       products[i].status == 1 ? "Hoat dong" : "Khoa");
                found = 1;
            }
        }
        
        if (!found) {
            printf("-> Khong tim thay san pham nao co ten chua '%s'.\n", keyword);
        }

    } else {
        printf("Lua chon khong hop le!\n");
    }
}
