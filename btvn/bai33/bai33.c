#include <stdio.h>
#include <string.h>
#include "BST.h"

const char filename[]="data.txt";

int loaddata(BSTree *Root){
	FILE* fptr;
	if ((fptr=fopen(filename,"r"))==NULL){
		printf("Canot open %s\n",filename);
		return 0;
	}
	char key[MAX],vn[MAX+1],ch;
	while (1){
		fscanf(fptr,"%s",key);
		if (feof(fptr)!=0) break;
		ch=fgetc(fptr);
		fgets(vn,MAX,fptr); vn[strlen(vn)-1]='\0';
		insertNode(&(*Root),key,vn);
	}
	fclose(fptr);
	printf("Nhap thanh cong!\n"); return 1;
}

int menu(){
	printf("\n------------MENU----------\n");
	printf("1. Nhap du lieu tu file\n");
	printf("2. In danh sach tu dien\n");
	printf("3. Dich tu tieng anh\n");
	printf("4. Chinh sua tu dien\n");
	printf("5. Luu va Thoat\n");
	printf("Chon: ");
	int c=0; scanf("%d",&c);
	while (c>5 || c<1){
		while(getchar()!='\n');
		printf("Chon sai! Chon lai: ");
		scanf("%d",&c);
	} 
	return c;
}

void printDictionary(BSTree Root){
	printf("\nDanh sach tu dien:\n");
	printInorder(Root);
}


int updateFile(BSTree Root){
	FILE* fptr=fopen(filename,"w");
	void Preorder(BSTree Root){
		if (Root==NULL) return;
		fprintf(fptr,"%s\t%s\n",Root->key,Root->vn);
		Preorder(Root->left);
		Preorder(Root->right);
	}
	Preorder(Root);
	fclose(fptr);
}

int insertWord(BSTree* Root, keyType key[]){
	printf("  Ban co muon bo sung nghia cho tu '%s' (y/n): ",key);
	char ch; scanf("%c",&ch);
	if (ch!='y') return 0;
	else{
		char vn[MAX];
		printf("  Nhap nghia: "); 
		while(getchar()!='\n');
		gets(vn);
		insertNode(&(*Root),key,vn);
		printf("  Them tu thanh cong");
		return 1; 
	} 
}

int chuthuong(char str[]){
	int i;
	for (i=0; i<strlen(str); i++)
		if (str[i]<='Z' && str[i]>='A') str[i]=str[i]+32;
		else if (str[i]>'z' || str[i]<'a') return 0;
	return 1; 	
}

void translate(BSTree* Root){
	char str[MAX],kq[100],key[MAX];
	int dk=1,n=0;
	printf("\nNhap cau can dich:  ");
	while (1){
		scanf("%s",str);
		if (dk==1){
			if (chuthuong(str)==0){
				printf("\n!Loi: khong duoc nhap cac ki tu dac biet.\n");
				dk=0;
			}
		}
		if (dk==1){
			node* tmp=search(*Root,str);
			if (tmp!=NULL){
				int i; 
				for (i=0; i<strlen(tmp->vn); i++) kq[n++]=tmp->vn[i];
				kq[n++]=' ';  
			}
			else{
				printf("\n!Loi thieu tu: Tu '%s' chua co nghia tieng viet\n",str);
				strcpy(key,str);
				dk=2;
			}
		}
		if (getchar()=='\n') break;
	}
	kq[n++]='\0';
	if (dk==1) printf("\nNghia Tieng viet la:  %s",kq);
	if (dk==2) insertWord(&(*Root),key);
}

void toLower(char str[]){
	int i;
	for (i=0; i<strlen(str); i++)
		if (str[i]>='A' && str[i]<='Z') str[i]+='a'-'A';
}

void translate2(BSTree *Root){
	char i,str[100],s[20],n,kq[100];
	while (getchar()!='\n');
	printf("\nNhap cau can dich:  "); gets(str); 
	toLower(str);
	n=strlen(str); str[n]=' '; str[n+1]='\0';
	n=0;
	
	for (i=0; i<strlen(str); i++){
		if (str[i]>='a' && str[i]<='z') s[n++]=str[i];
		else if (str[i]==' ' || str[i]==',' || str[i]=='.'){
			s[n]='\0';
			if (n==0) continue; else n=0;
			node* tmp=search(*Root,s);
			if (tmp!=NULL){
				strcat(kq," ");
				strcat(kq,tmp->vn); 
			}
			else{
				printf("\n!Loi thieu tu: Tu '%s' chua co nghia tieng viet\n",s);
				insertWord(&(*Root),s);
				return;
			}
			if (str[i]!=' '){
				int len=strlen(kq);
				kq[len]=str[i];
				kq[len+1]='\0';
			}
		} 
		else{
			printf("!Loi: Khong dc nhap cac ki tu dac biet.\n");
			return;
		}
	}
	printf("\nNghia Tieng viet:  %s",kq);
}

int menuEdit(){
	printf("\n\n---Chinh sua tu dien---\n");
	printf("1  Them 1 tu\n");
	printf("2. Sua nghia 1 tu\n");
	printf("3. Xoa 1 tu\n");
	printf("4. In tu dien\n");
	printf("5. Luu va Thoat\n");
	printf("Chon: "); 
	int c; scanf("%d",&c);
	while (c>5 || c<1){
		while(getchar()!='\n');
		printf("Chon sai! Chon lai: ");
		scanf("%d",&c);
	}
	return c;
}

int insertDic(BSTree* Root){
	char key[MAX],vn[MAX];
	printf("\nNhap tu tieng anh: "); scanf("%s",key);
	printf("Nhap nghia tieng viet: ");
	while (getchar()!='\n'); gets(vn);
	insertNode(&(*Root),key,vn);
	printf("Them thanh cong\n");
}

int editDic(BSTree* Root){
	char key[MAX],vn[MAX];
	printf("\nNhap tu tieng anh can sua: "); scanf("%s",key);
	node* temp=search(*Root,key);
	if (temp==NULL) printf("Khong co tu nay!\n");
	else{
		printf("Nghia hien tai: %s\n",temp->vn);
		printf("Nhap nghia moi(Nhan '#' thoat): ");
		while (getchar()!='\n'); gets(vn);
		if (strcmp(vn,"#")!=0){
			strcpy(temp->vn,vn);
			printf("Sua thanh cong\n");
		}
	}
}

int deleteDic(BSTree* Root){
	char key[MAX];
	printf("\nNhap tu tieng anh can xoa: "); scanf("%s",key);
	*Root=deleteNode(*Root,key);
	printf("Xoa thanh cong!\n");
}

void editDictionary(BSTree* Root){
	while (1){
		int c=menuEdit();
		switch (c){
			case 1: insertDic(&(*Root)); break;
			case 2: editDic(&(*Root)); break;
			case 3: deleteDic(&(*Root)); break;
			case 4: printDictionary(*Root); break;
			case 5: return;
		}
	}
}

int main(){
	BSTree Root=NULL; 
	while(1){
		int c=menu();
		switch (c){
			case 1: if (loaddata(&Root)==0) return 0; break;
			case 2:	printDictionary(Root); break;
			case 3: translate(&Root); break;
			case 4: editDictionary(&Root); break;
			case 5: updateFile(Root); return 0;
		}
		printf("\n");
	}
}
