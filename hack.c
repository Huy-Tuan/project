#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date{
	int month, day, year;
};
struct Category{
	char CategoryId[10];
	char CategoryName[10];
};
struct Product{
	char productId[10];
	char cateGory[10];
	char productName[10];
	int quantity;
	int price;
};
struct Product products[100];
struct Category category[10];
int numberProduct = 0;
int numberCategory = 0;
// ham in danh muc
void printCategory() {
    printf("\tDanh sach danh muc:\n");
    printf("\t+-----+-------------------+-------------------+\n");
    printf("\t| STT | Ma danh muc       | Ten danh muc      |\n"); 
    printf("\t+-----+-------------------+-------------------+\n");
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) > 0) {
            printf("\t| %-3d | %-17s | %-17s |\n", 
                   i + 1, 
                   category[i].CategoryId, 
                   category[i].CategoryName);
        }
    }
    printf("\t+-----+-------------------+-------------------+\n");
}

// ham luu danh muc vao file
void saveCategoryToFile() {
    FILE *file = fopen("category.txt", "w");
    if (file == NULL) {
        printf("\tLoi: Khong the mo file!\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) > 0) {
            fprintf(file, "%s,%s\n", category[i].CategoryId, category[i].CategoryName);
        }
    }
    fclose(file);
    printf("\tDanh muc da duoc luu vao file.\n");
}

// ham them danh muc
void addCategory() {
    for (int i = 0; i < 10; i++) {
        if (strlen(category[i].CategoryId) == 0) {
            printf("\tThem danh muc moi:\n");

            // Nh?p ID danh m?c
            int valid = 0;
            while (!valid) {
                printf("\tID danh muc (toi da 9 ky tu): ");
                while(getchar() != '\n');
                fgets(category[i].CategoryId, sizeof(category[i].CategoryId), stdin);
                category[i].CategoryId[strcspn(category[i].CategoryId, "\n")] = '\0';
				break;
                // Ki?m tra d? dài ID danh m?c
                if (strlen(category[i].CategoryId) > 9) {
                    printf("\tLoi: ID danh muc qua dai, vui long nhap toi da 9 ky tu!\n");
                } else if (strlen(category[i].CategoryId) == 0) {
                    printf("\tLoi: ID danh muc khong duoc de trong!\n");
                } else {
                    // Ki?m tra trùng l?p ID danh m?c
                    int isDuplicate = 0;
                    for (int j = 0; j < i; j++) {
                        if (strcmp(category[i].CategoryId, category[j].CategoryId) == 0) {
                            printf("\tLoi: ID danh muc da ton tai!\n");
                            isDuplicate = 1;
                            break;
                        }
                    }
                    if (!isDuplicate) {
                        valid = 1; // Thoát vòng l?p khi ID h?p l?
                    }
                }
            }

            // Nh?p tên danh m?c
            printf("\tTen danh muc (toi da 9 ky tu): ");
            while(getchar() != '\n');
            while (1) {
                fgets(category[i].CategoryName, sizeof(category[i].CategoryName), stdin);
                category[i].CategoryName[strcspn(category[i].CategoryName, "\n")] = '\0';
				break;
                // Ki?m tra d? dài Tên danh m?c
                if (strlen(category[i].CategoryName) > 9) {
                    printf("\tLoi: Ten danh muc qua dai, vui long nhap toi da 9 ky tu!\n");
                } else if (strlen(category[i].CategoryName) == 0) {
                    printf("\tLoi: Ten danh muc khong duoc de trong!\n");
                } else {
                    break; // Thoát vòng l?p khi tên h?p l?
                }
            }

            printf("\tThem danh muc thanh cong!\n");
            saveCategoryToFile();
            return;
        }
    }
    printf("\tDanh sach danh muc da day, khong the them moi!\n");
}

// ham tai danh muc
void loadCategoryFromFile() {
    FILE *file = fopen("category.txt", "r");
    if (file == NULL) {
        printf("\tLoi: Khong the mo file!\n");
        return;
    }

    int index = 0;
    while (fscanf(file, "%[^,],%[^\n]\n", category[index].CategoryId, category[index].CategoryName) == 2) {
        index++;
        if (index >= 10) break;
    }

    fclose(file);
    printf("\tDanh muc da duoc tai len tu file.\n");
}
// Ham chinh sua danh muc
void editCategory() {
    char x[30];
    int found = 0;
    printf("\tNhap ID danh muc can sua: ");
    while (getchar() != '\n');
    fgets(x, sizeof(x), stdin);
    x[strcspn(x, "\n")] = '\0';

    for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;

            printf("\tThong tin danh muc hien tai:\n");
            printf("\tID: %s\n", category[i].CategoryId);
            printf("\tTen: %s\n", category[i].CategoryName);

            printf("\tNhap thong tin sua doi:\n");

//            printf("\tID danh muc moi: ");
//            fgets(category[i].CategoryId, sizeof(category[i].CategoryId), stdin);
//            category[i].CategoryId[strcspn(category[i].CategoryId, "\n")] = '\0';

            printf("\tTen danh muc moi: ");
            fgets(category[i].CategoryName, sizeof(category[i].CategoryName), stdin);
            category[i].CategoryName[strcspn(category[i].CategoryName, "\n")] = '\0';

            printf("\tSua thong tin danh muc thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("\tKhong tim thay ID danh muc!\n");
    } else {
        saveCategoryToFile();
    }
}
// ham xoa danh muc
void deleteCategory(){
	char x[30];
	int found = 0;
	char a[30];
	printf("\tHay nhap ID muon xoa: ");
	while(getchar() != '\n');
	fgets(x, sizeof(x),stdin);
	x[strcspn(x, "\n")] = '\0';
	for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;
            break;
        }
    }
    if(!found) {
    	printf("\tKhong tim thay ID\n");
    	return;
	}
	printf("\tBan co chac chan muon xoa (yes/no): ");
	fgets(a, sizeof(a),stdin);
	a[strcspn(a, "\n")] = '\0';
	
	if(strcmp(a, "yes") == 0){
		for (int i = 0; i < 10; i++) {
        if (strcmp(x, category[i].CategoryId) == 0) {
            found = 1;
            for(int j = i; j < 10; j++){
            	category[j] = category[j + 1];
			}
		strcpy(category[9].CategoryId, "");
        strcpy(category[9].CategoryName, "");
        printf("\tDa xoa danh muc thanh cong!\n");
        break;
        }
    }
    saveCategoryToFile();
    printCategory();
  }
  else{
  	printf("\tHuy thao tac xoa\n");
  }
}
//ham tim kiem danh muc theo ten
void searchCategory(){
	char a[30];
	int found = 0;
	printf("\tMoi ban nhap ten danh muc muon tim: ");
	getchar();
	fgets(a, sizeof(a), stdin);
	a[strcspn(a, "\n")] = '\0';
	for(int i = 0; i < 10; i++){
		if(strcmp(a, category[i].CategoryName) == 0){
			found = 1;
			printf("\tDa tim thay !\n");
			printf("\t+-----+-------------------+-------------------+\n");
    		printf("\t| STT | Ma danh muc       | Ten danh muc      |\n"); 
    		printf("\t+-----+-------------------+-------------------+\n");
    			for (int j = i; j < 9 ; j++) {
        			if (strlen(category[i].CategoryId) > 0) {
            			printf("\t| %-3d | %-17s | %-17s |\n", 
                   		i + 1, 
                   		category[i].CategoryId, 
                   		category[i].CategoryName);
            printf("\t+-----+-------------------+-------------------+\n");
			break;
          }
      }
	}
  }
      if(!found) {
      	printf("\tKhong tim thay!\n");
	}
}
// ham sap xep danh muc
void arrangeCategory() {
    char a[10];
    printf("\tHay chon cach sap xep (tang / giam): ");
    while(getchar() != '\n');
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0';
    if (strcmp(a, "tang") == 0 || strcmp(a, "giam") == 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = i + 1; j < 10; j++) {
                if ((strcmp(a, "tang") == 0 && strcmp(category[i].CategoryName, category[j].CategoryName) > 0) ||
                    (strcmp(a, "giam") == 0 && strcmp(category[i].CategoryName, category[j].CategoryName) < 0)) {
                    struct Category temp = category[i];
                    category[i] = category[j];
                    category[j] = temp;
                }
            }
        }
    }
	else{
        printf("Lua chon khong hop le. Vui long thu lai.\n");
        return;
    }
    
    saveCategoryToFile();
}

// ham menu danh muc
void menuCategory() {
    int choice;
    do {
        printf("\t    QUAN LY DANH MUC\n");
        printf("\t===========================\n");
        printf("\t[1]. Hien thi danh sach danh muc\n");
        printf("\t[2]. Them danh muc moi\n");
        printf("\t[3]. Chinh sua danh muc\n");
        printf("\t[4]. Xoa danh muc\n");
        printf("\t[5]. Tim kiem danh muc\n");
        printf("\t[6]. Sap xep danh muc\n");
        printf("\t[0]. Quay lai menu chinh\n");
        printf("\t===========================\n");
        printf("\tNhap lua chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("\tQuay lai menu chinh.\n");
                break;
            case 1:
                printCategory();
                break;
            case 2:
                addCategory();
                break;
            case 3:
            	editCategory();
            	break;
            case 4:
            	deleteCategory();
            	break;
            case 5:
            	searchCategory();
            	break;
            case 6:
            	arrangeCategory();
            	break;
            default:
                printf("\tLua chon khong hop le!\n");
        }
    } while (choice != 0);
}
// ham tai san pham
void loadProductFromFile() {
    FILE *file = fopen("product.txt", "r");
    if (file == NULL) {
        printf("\tLoi: khong the mo file!\n");
        return;
    }
    numberProduct = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", 
                  products[numberProduct].productId, 
                  products[numberProduct].productName, 
                  products[numberProduct].cateGory, 
                  &products[numberProduct].quantity, 
                  &products[numberProduct].price) == 5) {
        numberProduct++;
        if (numberProduct >= 100) {
            printf("\tDanh sach san pham da day!\n");
            break;
        }
    }
    fclose(file);
    printf("\tSan pham da duoc tai len tu file.\n");
}
// ham luu san pham vao file
void saveProductToFile() {
    FILE *file = fopen("product.txt", "w");
    if (file == NULL) {
        printf("\tLoi: khong the mo file!\n");
        return;
    }
    for (int i = 0; i < numberProduct; i++) {
        fprintf(file, "%s,%s,%s,%d,%d\n", 
                products[i].productId, 
                products[i].productName, 
                products[i].cateGory, 
                products[i].quantity, 
                products[i].price);
    }
    fclose(file);
    printf("\tSan pham da duoc luu vao file.\n");
}
// ham them san pham
void addProduct() {
    if (numberProduct >= 100) {
        printf("\tDanh sach san pham da day!\n");
        return;
    }

    struct Product newProduct;

    printf("\tNhap Ma SP: ");
    getchar();
    fgets(newProduct.productId, sizeof(newProduct.productId), stdin);
    newProduct.productId[strcspn(newProduct.productId, "\n")] = '\0';

    for (int i = 0; i < numberProduct; i++) {
        if (strcmp(products[i].productId, newProduct.productId) == 0) {
            printf("\tLoi: Ma san pham da ton tai!\n");
            return;
        }
    }

    printf("\tNhap Ten SP: ");
    fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
    newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';

    printf("\tNhap Ma Danh Muc: ");
    getchar();
    fgets(newProduct.cateGory, sizeof(newProduct.cateGory), stdin);
    newProduct.cateGory[strcspn(newProduct.cateGory, "\n")] = '\0';

    int validCategory = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(category[i].CategoryId, newProduct.cateGory) == 0) {
            validCategory = 1;
            break;
        }
    }
    if (!validCategory) {
        printf("\tLoi: Ma danh muc khong ton tai!\n");
        return;
    }

    printf("\tNhap So Luong: ");
    scanf("%d", &newProduct.quantity);
    getchar();
    if (newProduct.quantity <= 0) {
        printf("\tLoi: So luong khong hop le!\n");
       	getchar();
        return;
    }

    printf("\tNhap Gia: ");
    scanf("%d", &newProduct.price);
    getchar();
    if (newProduct.price <= 0) {
        printf("\tLoi: Gia khong hop le!\n");
        return;
    }

    products[numberProduct] = newProduct;
    numberProduct++;

    printf("\tThem san pham thanh cong!\n");
    saveProductToFile();
    return;
}
// ham in danh sach san pham
void printProduct() {
    if (numberProduct == 0) {
        printf("\tDanh sach san pham rong!\n");
        return;
    }
    printf("\t+-----+----------+--------------------+------------+----------+----------+\n");
    printf("\t| STT | Ma SP    | Ten San Pham       | Danh Muc   | So Luong | Gia      |\n");
    printf("\t+-----+----------+--------------------+------------+----------+----------+\n");
    for (int i = 0; i < numberProduct; i++) {
        printf("\t| %-3d | %-8s | %-18s | %-10s | %-8d | %-8d |\n", 
               i + 1, 
               products[i].productId, 
               products[i].productName, 
               products[i].cateGory,
               products[i].quantity, 
               products[i].price);
    }
    printf("\t+-----+----------+--------------------+------------+----------+----------+\n");
}
void menuProduct() {
    int choice;
    do {
        printf("\t    PRODUCT MANAGEMENT MENU\n");
        printf("\t===========================\n");
        printf("\t[1]. Them san pham moi\n");
        printf("\t[2]. Hien thi danh sach san pham\n");
        printf("\t[0]. Quay lai menu chinh\n");
        printf("\t===========================\n");
        printf("\tNhap lua chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("\tQuay lai menu chinh.\n");
                break;
            case 1:
                addProduct();
                break;
            case 2:
                printProduct();
                break;
            default:
                printf("\tLua chon khong hop le!\n");
        }
    } while (choice != 0);
}


void menuAdmin(){
	int choice;
	do{
		printf("\t	ADMIN MENU\n");
		printf("\t===========================\n");
		printf("\t[1]. Category management\n");
		printf("\t[2]. Product management\n");
		printf("\t[3]. User Guideline\n");
		printf("\t[4]. About Us\n");
		printf("\t[0]. Exit the program\n");
		printf("\t===========================\n");
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		
		switch (choice){
			case 0:
				printf("Quay lai menu chinh\n");
				break;
			case 1:
				menuCategory();			
				break;
			case 2:
				menuProduct();
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				printf("Lua chon khong hop le!\n");
		}
	}while (choice != 0);
}
int main () {
	loadCategoryFromFile();
	loadProductFromFile();
	int choice;
	do{
		printf("***Store Management System Using C***\n");
		printf("\n");
		printf("\tCHOOSE YOUR ROLE\n");
		printf("\t=====================\n");
		printf("\t[1]. Admin\n");
		printf("\t[2]. Customer\n");
		printf("\t[0]. Exit the program\n");
		printf("\t=====================\n");
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 0:
				printf("\tBan da thoat chuong trinh");
				break;
			case 1:
				menuAdmin();
				break;
			case 2:
				break;
		}
	}while(choice != 0);
	
	saveCategoryToFile();
	saveProductToFile();
	return 0;
}

