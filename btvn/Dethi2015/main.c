#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"BST.h"

typedef struct _dataB{
	int key;
	char dochoi[MAX];
}dataB;

const char fileA[]="A.txt";
const char fileB[]="B.txt";


int menu(){
	printf("\n\n-------MENU------\n");
	printf("1. Doc file A\n");
	printf("2. Doc file B\n");
	printf("3. Tim kiem\n");
	printf("4. Tong hop\n");
	printf("5. Thong ke\n");
	printf("6. Thoat\n");
	printf("Chon: ");
	int c=0; scanf("%d",&c);  
	while (c>6 || c<1){
		while(getchar()!='\n');
		printf("CHon sai! CHon lai:  ");
		scanf("%d",&c);
	}
	return c;
}


void loadfileA(BSTree *Root){
	FILE *fptr;
	if ((fptr=fopen(fileA,"r"))==NULL){
		printf("Canot open %s\n",fileA);
		return;
	}
	int key; char dochoi[MAX];
	while (1){
		fscanf(fptr,"%d",&key);
		char ch=fgetc(fptr);	
		if (ch=='\n' || feof(fptr)!=0){
			printf("Nhap them thong tin ma so %d: ",key);
			scanf("%s",dochoi);
		}
		else fscanf(fptr,"%s",dochoi);
		insertNode(&(*Root),key,dochoi);
		if (feof(fptr)!=0) break;
	}	
	fclose(fptr);
}

int loadfileB(dataB Data[]){
	FILE *fptr;
	if ((fptr=fopen(fileB,"r"))==NULL){
		printf("Canot open %s\n",fileB);
		return;
	}
	int n=0;
	while (1){
		fscanf(fptr,"%d",&(Data[n].key));
		char ch=fgetc(fptr);
		if (ch=='\n' || feof(fptr)!=0){
			printf("Nhap them thong tin ma so %d: ",Data[n].key);
			scanf("%s",Data[n].dochoi);
		}
		else fscanf(fptr,"%s",Data[n].dochoi);
		n++;
		if (feof(fptr)!=0) break;
	}	
	fclose(fptr);
	return n;
}


void printfileA(BSTree Root){
	printf("\n---Du lieu file A---\n");
	printInorder(Root);
}

void printfileA2(BSTree Root){
	
	dataB data[MAX]; int n=0;
	void printInorder2(BSTree Root){
		if (Root==NULL) return;
		printInorder2(Root->left);
		data[n].key=Root->key; 
		strcpy(data[n].dochoi,Root->dochoi);
		n++;
		printInorder2(Root->right);
	}
	printInorder2(Root);
	printf("\n---Du lieu file A---\n");
	int i;
	for (i=n-1; i>=0; i--) printf("%d\t%s\n",data[i].key,data[i].dochoi);
}

void printfileB(dataB Data[], int n){
	printf("\n---Du lieu file B---\n");
	int i;
	for (i=0; i<n; i++) printf("%d\t%s\n",Data[i].key,Data[i].dochoi);
}

void searchAB(BSTree *Root, dataB Data[], int n){
	int i;
	for (i=0; i<n; i++){
		node* tmp=search(*Root,Data[i].key);
		if (tmp!=NULL){
			printf("\nTHong tin em bi trung   Maso: %d  Dochoi: %s\n",tmp->key,tmp->dochoi);
			printf("Da xoa thong tin bi trung!\n\n");
			*Root=deleteNode(*Root,Data[i].key);
		} 
	}
}

void tonghop(BSTree *Root, dataB Data[], int n){
	int i;
	for (i=0; i<n; i++)
		insertNode(&(*Root),Data[i].key, Data[i].dochoi);
}

void thongke(BSTree Root){
	dataB ds[MAX];
	int n=0,i;
	void Inorder(BSTree Root){
		if (Root==NULL) return;
		int dk=0;
		for (i=0; i<n; i++)
			if (strcmp(Root->dochoi,ds[i].dochoi)==0){
				ds[i].key++; dk=1; break;
			}
		if (dk==0){
			strcpy(ds[i].dochoi,Root->dochoi); ds[i].key=1; n++;
		}
		Inorder(Root->left);
		Inorder(Root->right);
	}
	Inorder(Root);
	
	printf("\n---Danh sach cac do vat----\n");
	for (i=0; i<n; i++) printf("%s\t%d\n",ds[i].dochoi,ds[i].key);
}
	


int main(){
	
	BSTree Root=NULL;
	dataB Data[MAX];
	int n;
	
	while (1){
		int c=menu();
		switch (c){
			case 1: loadfileA(&Root); printfileA(Root); break;
			case 2: n=loadfileB(Data); printfileB(Data,n); break;
			case 3: searchAB(&Root,Data,n); printfileA(Root); break;
			case 4: tonghop(&Root,Data,n); printfileA2(Root); break;
			case 5: thongke(Root); break;
			case 6: return;
		}
		
	}
	
}
