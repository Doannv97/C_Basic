#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

const char filename[]="pass.txt";

int loaddata(BSTree *Root){
	FILE* fptr;	
	if ((fptr=fopen(filename,"r"))==NULL){
		printf("Canot open %s\n",filename);
		return 0;
	}

	char key[MAX],password[MAX];
	while (1){
		fscanf(fptr,"%s",key);
		if (feof(fptr)!=0) break;
		fscanf(fptr,"%s",password);
		insertNode(&(*Root),key,password); 
	}
	return 1;
}

int login(BSTree Root,char user[]){
	char key[MAX],password[MAX],i=3;
	
	while(1){
		i--;
		printf("\n\n---------Login--------\n");
		printf("username: "); scanf("%s",key);
		printf("password: "); scanf("%s",password);
	
		node* temp=search(Root,key);
		if (temp==NULL) printf("Tai khoan khong ton tai\n");
		else{
			if (strcmp(temp->password,password)==0){
				printf("Dang nhap thanh cong\n");
				strcpy(user,key);
				return 1;
			}
			else printf("Ten dang nhap va mat khau khong trung nhau\n");
		}
		if (i==0){
			printf("\nDang nhap sai 3 lan! Thoat\n\n");
			return 0;
		}
		printf("\n\nDang nhap lai!");
	}
}

int checkinPass(char pass[]){
  int i,kt;
  if (strlen(pass)<6) return 0;
  for (i=0; i<strlen(pass); i++){
    kt=0;
    if (pass[i]>='A' && pass[i]<='Z') kt=1;
    if (pass[i]>='a' && pass[i]<='z') kt=1;
    if (pass[i]>='0' && pass[i]<='9') kt=1;
    if (pass[i]=='@' || pass[i]=='_') kt=1;
    if (kt==0) return 0;
  }
  return 1;
}

void enterPass(char password[]){
  char password2[MAX];
  printf(" Nhap mat khau: "); scanf("%s",password);
  while (checkinPass(password)==0){
      printf("   Mat khau khong dung quy dinh!\n");
      printf("   Nhap lai: ");
      scanf("%s",password);
  }
  printf(" Xac nhan lai mat khau: "); scanf("%s",password2);
  if (strcmp(password,password2)!=0){
    printf(" \nMat khau khong trung nhau! Vui long tao lai mk\n");
    enterPass(password);
  }
}

int menuAdmin(){
  printf("\n\n-------MENU-Admin-------\n");
  printf("1. Them tai khoan\n");
  printf("2. Sua mat khau nguoi dung\n");
  printf("3. Xoa tai khoan\n");
  printf("4. Danh sach tai khoan\n");
  printf("5. Dang xuat\n");
  printf("6. Thoat\n");
  printf("Chon: ");
  int c=0; scanf("%d",&c);
  while (c>6 || c<1){
    while (getchar()!='\n');
    printf("Nhap sai: Nhap lai: ");
    scanf("%d",&c);
  }
  return c;
}

int insertUser(BSTree *Root){
  char key[MAX],password[MAX];
  printf("\nNhap thong tin:\n");
  printf("Ten dang nhap: "); scanf("%s",key);
  if (search(*Root,key)!=NULL)  printf("Ten tai khoan bi trung!\n");
  else{
    enterPass(password);
    insertNode(&(*Root),key,password);
    printf("Them thanh cong\n");
  }
}

int editUser(BSTree *Root){
  char password[MAX],key[MAX];
  printf("\n\nNhap ten tai khoan can thay doi mat khau: "); scanf("%s",key);
  node* tmp=search(*Root,key);
  if (tmp==NULL) printf("Tai khoan khong ton tai!\n");
  else{
  	printf("Nhap mk moi: \n");
    enterPass(password);
    strcpy(tmp->password,password);
    printf("Doi mat khau thanh cong\n");
  }
}

int deleteUser(BSTree *Root){
  char key[MAX];
  printf("\n\nNhap ten tai khoan can xoa: "); scanf("%s",key);
  node* tmp=search(*Root,key);
  if (tmp==NULL) printf("Tai khoan khong ton tai!\n ");
  else{
    *Root=deleteNode(*Root,key);
    printf("Xoa thanh cong");
  }   
}

int updatedata(BSTree Root){
  FILE* fptr=fopen(filename,"w");	
  void Preorder(BSTree Root){
    if (Root==NULL) return;
    fprintf(fptr,"%s %s\n",Root->key,Root->password);
    Preorder(Root->left);
    Preorder(Root->right);
  }	
  Preorder(Root);
  fclose(fptr);
}

void printUser(BSTree Root){
  printf("\n\nDanh sach cac tai khoan va mat khau:\n");
  printInorder(Root);
}

int Admin(BSTree *Root){
  while(1){
    int c=menuAdmin();
    switch (c){
    case 1: insertUser(&(*Root)); break;
    case 2: editUser(&(*Root)); break;
    case 3: deleteUser(&(*Root)); break;
    case 4: printUser(*Root); break;
    case 5: updatedata(*Root); return 1;
    case 6: updatedata(*Root); return 0;
    }
  }
}

int editPass(BSTree *Root,char key[]){
  node* tmp=search(*Root,key);
  char password[MAX];
  enterPass(password);
  strcpy(tmp->password,password);
  printf("Doi mat khau thanh cong\n");
}

int menuUser(){
	printf("\n\n-----MENU-User-----\n");
	printf("1. Doi mat khau\n");
	printf("2. Dang xuat\n");
	printf("3. Thoat\n");
	printf("Chon: ");
	int c=0; scanf("%d",&c);
	while (c>3 || c<1){
		while (getchar()!='\n');
		printf("Nhap sai: Nhap lai: ");
		scanf("%d",&c);
	}
	return c;
}

int User(BSTree *Root,char key[]){
	while (1){
		int c=menuUser();
		switch (c){
		case 1: editPass(&(*Root),key); break;
		case 2: updatedata(*Root); return 1;
		case 3: updatedata(*Root); return 0;
		}
	}
}

int main(){
	BSTree Root=NULL;
	char user[MAX]="";
		
    if (loaddata(&Root)==0) return 0;
	
    while (1){
    	int kt=0;
		if (login(Root,user)==0) return 0;
		if (strcmp(user,"admin")==0) kt=Admin(&Root);
		else kt=User(&Root,user);
		if (kt==0) return;
		printf("\n\n");
	}
}
