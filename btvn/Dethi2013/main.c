#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

const char filename[]="BongDa.txt";
const char filename2[]="KetQua.txt";

int menu(){
	printf("\n\n-------MENU-------\n");
	printf("1. Tao cay\n");
	printf("2. Ket qua\n");
	printf("3. Tim kiem\n");
	printf("4. Xuong hang\n");
	printf("5. Xuat file\n");
	printf("6. Thoat\n");
	printf("Chon: ");
	int c; scanf("%d",&c);
	while (c>6 || c<1){
		printf("Nhap sai! Nhap lai: ");
		scanf("%d",&c);
	}
	return c;
}

void taocay(BSTree *Root){
	FILE* fptr;
	if ((fptr=fopen(filename,"r"))==NULL){
		printf("Canot open %s\n",filename);
		return;
	}
	
	char team1[MAX],team2[MAX];
	int x,y,i=0;
	while (1){
		fscanf(fptr,"%s%s%d%d",team1,team2,&x,&y);
		node* tmp1=search(*Root,team1);
		if (tmp1==NULL){
			i++;
			insertNode(&(*Root),team1);
			tmp1=search(*Root,team1);
			printf("Tao nut moi thu %d cho doi %s, dia chi la %X\n",i,team1,tmp1);
		}
		node* tmp2=search(*Root,team2);
		if (tmp2==NULL){
			i++;
			insertNode(&(*Root),team2);
			tmp2=search(*Root,team2);
			printf("Tao nut moi thu %d cho doi %s, dia chi la %X\n",i,team2,tmp2);
		}
		if (x>y) tmp1->point+=3; 
		else if (x<y) tmp2->point+=3;
		else{
			tmp1->point+=1; tmp2->point+=1;
		}	
		if (feof(fptr)!=0) break;
	}
	fclose(fptr);
}

void ketqua(BSTree Root){
	printf("\n----Bang diem cac doi-----\n");
	printInorder(Root);
}

void timkiem(BSTree Root){
	char team[MAX];
	printf("\nNhap ten doi bong can tim: "); scanf("%s",team);
	node* tmp=search(Root,team);
	if (tmp==NULL) printf("\nKhong co doi bong nay!");
	else printf("\nDiem so cua doi %s la: %d\n",team,tmp->point);
}

void xuonghang(BSTree *Root){
	int X; printf("\nNhap so diem X: "); scanf("%d",&X);
	char ds[MAX][MAX],n=0;
	void Inorder(BSTree Root){
		if (Root==NULL) return;
		Inorder(Root->left); 
		if (Root->point<X){
			strcpy(ds[n],Root->key);
			n++;
		}
		Inorder(Root->right);
	}
	Inorder(*Root);
	printf("\nCac doi bi xuong hang: ");
	int i;
	for (i=0; i<n; i++){
		printf("%s ",ds[i]);
		*Root=deleteNode(*Root,ds[i]);
	}
}

void thongke(BSTree Root){
	FILE* fptr;
	if ((fptr=fopen(filename2,"w"))==NULL){
		printf("Canot open %s\n",filename2);
		return;
	}
	void Inorder(BSTree Root){
		if (Root==NULL) return;
		Inorder(Root->left);
		fprintf(fptr,"%s\t%d\n",Root->key,Root->point); 
		Inorder(Root->right);
	}
	Inorder(Root);
	printf("\nGhi la file thanh cong.");
	fclose(fptr);
}

int main(){
	BSTree Root=NULL;
	while (1){
		int c=menu();
		switch (c){
			case 1: taocay(&Root); break;
			case 2: ketqua(Root);  break;
			case 3: timkiem(Root); break;
			case 4: xuonghang(&Root); ketqua(Root); break;
			case 5: thongke(Root); break;
			case 6: return 0;
		}
	}
	
}
