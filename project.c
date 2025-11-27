#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PAGE_SIZE 5 

struct Product {
    char id[15];     
    char name[50];   
    char unit[15];   
    int quantity;    
    int status;      // 1 = CON HANG, 0 = HET HANG (Ngung kinh doanh)
};

struct Transaction {
    char type[10];   
    char pId[15];    
    char pName[50];  
    int amount;      
};

typedef struct Product Product;
typedef struct Transaction Transaction;

Product products[100];
int pCount = 0;

Transaction history[100]; 
int hCount = 0;           

// --- NGUYEN MAU HAM ---
void clearBuffer();
void trim(char *s);
int isNumber(char *s);
int findProductIndex(char *id);
void recordTransaction(char *type, char *pId, char *pName, int amount);
void initData(); 

void F01_AddProduct();
void F02_UpdateProduct();
void F03_ChangeStatus(); // <-- Cap nhat logic moi tai day
void F04_SearchProduct();
void F05_ListProducts(); 
void F06_SortProducts();
void F07_StockInOut();
void F08_TransactionHistory();

int main() {
    initData();

    int choice;
    char choiceStr[10]; 

    do {
        printf("\n==========================================\n");
        printf("    HE THONG QUAN LY KHO HANG\n");
        printf("==========================================\n");
        printf("1. F01 - Them hang hoa moi\n");
        printf("2. F02 - Cap nhat thong tin\n");
        printf("3. F03 - Cap nhat trang thai (Con hang/Het hang)\n"); // <-- Doi ten menu
        printf("4. F04 - Tim kiem hang hoa\n");
        printf("5. F05 - Danh sach hang hoa (PHAN TRANG)\n");
        printf("6. F06 - Sap xep hang hoa (Theo SL giam dan)\n");
        printf("7. F07 - Nhap/Xuat kho\n");
        printf("8. F08 - Lich su giao dich\n");
        printf("0. Thoat\n");
        printf("------------------------------------------\n");
        printf("Lua chon cua ban: ");

        fgets(choiceStr, 10, stdin);
        trim(choiceStr); 

        if (strlen(choiceStr) == 0) {
            choice = -1;
            continue;    
        }

        if (!isNumber(choiceStr)) {
            printf("-> LOI: Nhap sai! Vui long chi nhap so.\n");
            choice = -1;
            continue;
        }

        choice = atoi(choiceStr);

        switch (choice) {
            case 1: F01_AddProduct(); break;
            case 2: F02_UpdateProduct(); break;
            case 3: F03_ChangeStatus(); break;
            case 4: F04_SearchProduct(); break;
            case 5: F05_ListProducts(); break;
            case 6: F06_SortProducts(); break;
            case 7: F07_StockInOut(); break;
            case 8: F08_TransactionHistory(); break;
            case 0: printf("Thoat chuong trinh. Tam biet!\n"); break;
            default: printf("Lua chon khong hop le! Vui long chon tu 0 den 8.\n"); break;
        }
    } while (choice != 0);

    return 0;
}

// --- HAM TAO DU LIEU MAU ---
void initData() {
    // Trang 1
    strcpy(products[0].id, "SP001"); strcpy(products[0].name, "Laptop Dell XPS"); strcpy(products[0].unit, "Cai"); products[0].quantity = 10; products[0].status = 1; pCount++;
    strcpy(products[1].id, "SP002"); strcpy(products[1].name, "Macbook Pro M1"); strcpy(products[1].unit, "Cai"); products[1].quantity = 5; products[1].status = 1; pCount++;
    strcpy(products[2].id, "SP003"); strcpy(products[2].name, "Chuot Logitech"); strcpy(products[2].unit, "Cai"); products[2].quantity = 50; products[2].status = 1; pCount++;
    strcpy(products[3].id, "SP004"); strcpy(products[3].name, "Ban phim Co"); strcpy(products[3].unit, "Cai"); products[3].quantity = 20; products[3].status = 1; pCount++;
    strcpy(products[4].id, "SP005"); strcpy(products[4].name, "Man hinh LG 24"); strcpy(products[4].unit, "Cai"); products[4].quantity = 8; products[4].status = 1; pCount++;

    // Trang 2
    strcpy(products[5].id, "SP006"); strcpy(products[5].name, "Tai nghe Sony"); strcpy(products[5].unit, "Cai"); products[5].quantity = 12; products[5].status = 1; pCount++;
    strcpy(products[6].id, "SP007"); strcpy(products[6].name, "Lot chuot Razer"); strcpy(products[6].unit, "Cai"); products[6].quantity = 100; products[6].status = 1; pCount++;
    // SP008 set la 0 (Het hang)
    strcpy(products[7].id, "SP008"); strcpy(products[7].name, "Ghe Cong thai hoc"); strcpy(products[7].unit, "Cai"); products[7].quantity = 0; products[7].status = 0; pCount++; 
    strcpy(products[8].id, "SP009"); strcpy(products[8].name, "Webcam 4K"); strcpy(products[8].unit, "Cai"); products[8].quantity = 7; products[8].status = 1; pCount++;
    strcpy(products[9].id, "SP010"); strcpy(products[9].name, "Micro Thu am"); strcpy(products[9].unit, "Cai"); products[9].quantity = 4; products[9].status = 1; pCount++;

    // Trang 3
    strcpy(products[10].id, "SP011"); strcpy(products[10].name, "Den ban Xiaomi"); strcpy(products[10].unit, "Cai"); products[10].quantity = 15; products[10].status = 1; pCount++;
    strcpy(products[11].id, "SP012"); strcpy(products[11].name, "Day cap HDMI"); strcpy(products[11].unit, "Met"); products[11].quantity = 200; products[11].status = 1; pCount++;
}

void clearBuffer() { int c; while ((c = getchar()) != '\n' && c != EOF); }
void trim(char *s) { char *p = s; int l = strlen(p); while(l > 0 && isspace(p[l - 1])) p[--l] = 0; while(*p && isspace(*p)) p++, l--; memmove(s, p, l + 1); }
int isNumber(char *s) { for (int i = 0; i < strlen(s); i++) { if (!isdigit(s[i])) return 0; } return 1; }
int findProductIndex(char *id) { for (int i = 0; i < pCount; i++) { if (strcmp(products[i].id, id) == 0) return i; } return -1; }
void recordTransaction(char *type, char *pId, char *pName, int amount) { if (hCount < 100) { strcpy(history[hCount].type, type); strcpy(history[hCount].pId, pId); strcpy(history[hCount].pName, pName); history[hCount].amount = amount; hCount++; } }

void F01_AddProduct() {
    printf("\n--- [F01] THEM HANG HOA MOI ---\n");
    Product p; char numStr[20]; 
    do { printf("Nhap ma hang: "); fgets(p.id, 15, stdin); trim(p.id);
        if (strlen(p.id) == 0 || findProductIndex(p.id) != -1) printf("-> LOI: Ma hang rong hoac da ton tai!\n");
    } while (strlen(p.id) == 0 || findProductIndex(p.id) != -1);

    do { printf("Nhap ten hang: "); fgets(p.name, 50, stdin); trim(p.name);
    } while (strlen(p.name) == 0);
    do { printf("Nhap don vi tinh: "); fgets(p.unit, 15, stdin); trim(p.unit);
    } while (strlen(p.unit) == 0);

    int valid = 0;
    do { printf("Nhap so luong: "); fgets(numStr, 20, stdin); trim(numStr);
        if (!isNumber(numStr) || strlen(numStr) == 0) printf("-> LOI: Nhap so nguyen!\n");
        else { p.quantity = atoi(numStr); valid = 1; }
    } while (!valid);

    p.status = 1; // Mac dinh la Con hang
    products[pCount++] = p; 
    printf("-> Them moi thanh cong!\n");
}

void F02_UpdateProduct() {
    printf("\n--- [F02] CAP NHAT THONG TIN ---\n");
    char id[15]; printf("Nhap ma hang: "); fgets(id, 15, stdin); trim(id);
    int idx = findProductIndex(id);
    if (idx == -1) { printf("LOI: Khong tim thay!\n"); return; }

    printf("Ten (%s) -> Moi: ", products[idx].name); char t[50]; fgets(t, 50, stdin); trim(t);
    if (strlen(t) > 0) strcpy(products[idx].name, t);

    printf("Don vi (%s) -> Moi: ", products[idx].unit); char u[15]; fgets(u, 15, stdin); trim(u);
    if (strlen(u) > 0) strcpy(products[idx].unit, u);
    printf("-> Cap nhat xong!\n");
}

// [F03] CAP NHAT TRANG THAI (Logic moi)
void F03_ChangeStatus() {
    printf("\n--- [F03] CAP NHAT TRANG THAI (CON HANG / HET HANG) ---\n");
    char id[15];
    printf("Nhap ma hang can cap nhat: ");
    fgets(id, 15, stdin); trim(id);

    int idx = findProductIndex(id);
    if (idx == -1) { printf("LOI: Khong tim thay ma hang '%s'!\n", id); return; }

    // Dao nguoc trang thai
    if (products[idx].status == 1) {
        products[idx].status = 0;
        printf("-> Da chuyen trang thai sang: HET HANG\n");
    } else {
        products[idx].status = 1;
        printf("-> Da chuyen trang thai sang: CON HANG\n");
    }
}

void F04_SearchProduct() {
    printf("\n--- [F04] TIM KIEM HANG HOA ---\n");
    char kw[50]; printf("Nhap tu khoa: "); fgets(kw, 50, stdin); trim(kw);
    printf("\n%-10s %-25s %-10s %-10s %-15s\n", "MA", "TEN HANG", "DON VI", "SL", "TRANG THAI");
    printf("--------------------------------------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < pCount; i++) {
        if (strstr(products[i].id, kw) || strstr(products[i].name, kw)) {
            printf("%-10s %-25s %-10s %-10d %-15s\n", 
                   products[i].id, products[i].name, products[i].unit, products[i].quantity,
                   products[i].status == 1 ? "Con hang" : "Het hang"); // <-- Text moi
            found = 1;
        }
    }
    if (!found) printf("(Khong tim thay ket qua)\n");
}

void F05_ListProducts() {
    int currentPage = 1;
    int totalPages;
    char navChoice[10];
    int nav;

    while (1) {
        if (pCount == 0) totalPages = 1;
        else totalPages = (pCount + PAGE_SIZE - 1) / PAGE_SIZE;

        printf("\n--- [F05] DANH SACH HANG HOA (Trang %d/%d) ---\n", currentPage, totalPages);
        printf("%-10s %-25s %-10s %-10s %-15s\n", "MA", "TEN HANG", "DON VI", "SL", "TRANG THAI");
        printf("--------------------------------------------------------------------------\n");

        if (pCount == 0) {
            printf("    (Kho hang trong)\n");
        } else {
            int start = (currentPage - 1) * PAGE_SIZE;
            int end = start + PAGE_SIZE;
            if (end > pCount) end = pCount;

            for (int i = start; i < end; i++) {
                printf("%-10s %-25s %-10s %-10d %-15s\n", 
                       products[i].id, 
                       products[i].name, 
                       products[i].unit, 
                       products[i].quantity,
                       products[i].status == 1 ? "Con hang" : "Het hang"); // <-- Text moi
            }
        }
        printf("--------------------------------------------------------------------------\n");
        printf("Dieu huong: [1] Truoc | [2] Sau | [0] Ve Menu -> ");
        
        fgets(navChoice, 10, stdin); trim(navChoice);
        if (!isNumber(navChoice)) nav = -1; else nav = atoi(navChoice);

        if (nav == 0) break;
        else if (nav == 1) { if (currentPage > 1) currentPage--; }
        else if (nav == 2) { if (currentPage < totalPages) currentPage++; }
    }
}

void F06_SortProducts() {
    for (int i = 0; i < pCount - 1; i++) {
        for (int j = 0; j < pCount - i - 1; j++) {
            if (products[j].quantity < products[j+1].quantity) {
                Product temp = products[j]; products[j] = products[j+1]; products[j+1] = temp;
            }
        }
    }
    printf("\n-> Da sap xep giam dan theo so luong. Vao F05 de xem.\n");
}

void F07_StockInOut() {
    printf("\n--- [F07] NHAP / XUAT KHO ---\n");
    char id[15]; printf("Nhap ma hang: "); fgets(id, 15, stdin); trim(id);
    int idx = findProductIndex(id);
    if (idx == -1) { printf("-> LOI: Khong tim thay!\n"); return; }

    printf("San pham: %s (Hien co: %d) - Trang thai: %s\n", 
            products[idx].name, products[idx].quantity, 
            products[idx].status == 1 ? "Con hang" : "Het hang");

    // Neu dang Het hang, van cho phep Nhap kho de co hang tro lai
    // Nhung neu Xuat kho thi phai canh bao
    
    printf("1. Nhap kho (Them SL)\n2. Xuat kho (Giam SL)\nChon: ");
    char optStr[10]; fgets(optStr, 10, stdin); trim(optStr);
    int opt = atoi(optStr);

    printf("Nhap so luong: "); char numStr[20]; fgets(numStr, 20, stdin); trim(numStr);
    int amount = atoi(numStr);
    if (amount <= 0) { printf("-> Loi: So luong phai > 0\n"); return; }

    if (opt == 1) {
        products[idx].quantity += amount;
        // Tu dong chuyen sang Con hang neu dang het hang
        if (products[idx].status == 0) products[idx].status = 1; 
        printf("-> NHAP KHO thanh cong! Ton moi: %d (Trang thai: Con hang)\n", products[idx].quantity);
        recordTransaction("NHAP", products[idx].id, products[idx].name, amount);
    } else {
        if (products[idx].status == 0 && products[idx].quantity == 0) {
            printf("-> LOI: Hang dang bao 'Het hang' va SL = 0, khong the xuat!\n");
            return;
        }
        if (amount > products[idx].quantity) {
            printf("-> LOI: Khong du hang de xuat (Con: %d)!\n", products[idx].quantity);
        } else {
            products[idx].quantity -= amount;
            // Neu xuat het sach thi tu dong bao het hang
            if (products[idx].quantity == 0) products[idx].status = 0;
            printf("-> XUAT KHO thanh cong! Ton moi: %d\n", products[idx].quantity);
            recordTransaction("XUAT", products[idx].id, products[idx].name, amount);
        }
    }
}

void F08_TransactionHistory() {
    printf("\n--- [F08] LICH SU GIAO DICH ---\n");
    printf("%-5s %-10s %-15s %-20s %-10s\n", "STT", "LOAI", "MA HANG", "TEN HANG", "SO LUONG");
    for (int i = 0; i < hCount; i++) {
        printf("%-5d %-10s %-15s %-20s %-10d\n", i + 1, history[i].type, history[i].pId, history[i].pName, history[i].amount);
    }
}
