#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

int strupper(char str[]){
	int i;
	for (i=0; i<strlen(str); i++)
		if (str[i]<='Z' && str[i]>='A') str[i]+='a'-'A';
		
}

int loaddata(BSTree *Root){
	FILE* fptr;
	char filename[MAX];
	
	printf("\nNhap file du lieu: "); scanf("%s",filename);
	if ((fptr=fopen(filename,"r"))==NULL){
		printf("Canot open %s\n",filename);
		return 0;
	}	
	
	char str[MAX];
	while (1){
		fscanf(fptr,"%s",str);
		strupper(str);
		node* tmp=search(*Root,str);
		if (tmp==NULL) insertNode(&(*Root),str);
		else tmp->count++;
		if (feof(fptr)!=0) break;
	}
	
	printf("Nhap du lieu thanh cong\n\n");
	rewind(fptr);
	char ch;
	while (1){
		ch=fgetc(fptr);
		if (feof(fptr)!=0) break;
		printf("%c",ch);
	}
	fclose(fptr);
	return 1;
}

int searchWord(BSTree Root){
	char str[MAX];
	printf("\nNhap tu can tim: "); scanf("%s",str);
	node* tmp=search(Root,str);
	if (tmp==NULL) printf("Khong tim thay!\n");
	else{
		printf("So lan xuat hien la: %d\n",tmp->count);
	}
}

int menu(){
	printf("\n--------------MENU-------------\n");
	printf("1. Nhap ten file\n");
	printf("2. In tan suat xuat hien cua 1 tu\n");
	printf("3. Danh sach cac tu\n");
	printf("4. Thoat\n");
	printf("Chon: ");
	int c=0; scanf("%d",&c);
	while (c>4 || c<1){
		printf("Nhap sai! Nhap lai: ");
		scanf("%d",&c);
	}
	return c;
	
}

int giaiphong(BSTree *Root){
	if (*Root==NULL) return 0;
	giaiphong(&((*Root)->left));
	giaiphong(&((*Root)->right));
	free(*Root); *Root=NULL;
}

int main(){
	BSTree Root=NULL;
	while (1){
		int c=menu();
		switch (c){
			case 1: if (loaddata(&Root)==0) return;  break;
			case 2: searchWord(Root); break;
			case 3: printInorder(Root); break;
			case 4: giaiphong(&Root); return 0;
		}
		printf("\n");
	}
	
}
