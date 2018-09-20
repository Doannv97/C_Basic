#include"BST.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int stringcmp(char a[], char b[]){
	int i=0, lena=strlen(a), lenb=strlen(b);
	while (1){
		if (a[i]<b[i]) return -1;
		else if (a[i]>b[i]) return 1;
		else{
			i++;
			if (i==lena && i==lenb) return 0;
			if (i==lena) return -1;
			if (i==lenb) return 1;
		}
	}
}

node* makeNode(keyType key[], char vn[]){
	node* new=(node*)malloc(sizeof(node));
	if (new==NULL) return NULL; 
	else{
		strcpy(new->key,key);
		strcpy(new->vn,vn);
		new->left=NULL;
		new->right=NULL;
		return new;
	}
}

int insertNode(BSTree* Root, keyType key[], char vn[]){
	if (*Root==NULL) *Root=makeNode(key,vn);
	else if (stringcmp(key,(*Root)->key)==-1) insertNode(&((*Root)->left),key,vn);
	else if (stringcmp(key,(*Root)->key)==1) insertNode(&((*Root)->right),key,vn);
	else return 0;
	return 1;
}

node* search(BSTree Root, keyType key[]){
	if (Root==NULL) return NULL;
	if (stringcmp(key,Root->key)==0) return Root;
	if (stringcmp(key,Root->key)==-1) return search(Root->left,key);
	else return search(Root->right,key);
}

node* findMax(BSTree Root){
	if (Root==NULL) return NULL;
	else{
		if (Root->right==NULL) return Root;
		else return findMax(Root->right);
	}
}

node* findMin(BSTree Root){
	if (Root==NULL) return NULL;
	else{
		if (Root->left==NULL) return Root;
		else return findMin(Root->left);
	}
}

node* deleteNode(BSTree Root, keyType key[]){
	if (Root==NULL) return Root;
  	if (stringcmp(key,Root->key)==-1) Root->left=deleteNode(Root->left,key);
	else if (stringcmp(key,Root->key)==1) Root->right=deleteNode(Root->right,key);
	else{							  
      	if (Root->left!=NULL && Root->right!=NULL){
			node* tmp=findMin(Root->right);
			strcpy(Root->key,tmp->key);
			strcpy(Root->vn,tmp->vn);
	  		Root->right=deleteNode(Root->right,tmp->key);
		}
		else{
	  		node* temp=Root;
	  		if (Root->right!=NULL) Root=Root->right;
	 		else Root=Root->left;
	  		free(temp);
		}
    }
 	return Root;
}

int highTree(BSTree Root){
	if (Root==NULL) return 0;
	int h_left=highTree(Root->left);
	int h_right=highTree(Root->right);
	return 1+(h_left > h_right? h_left :h_right);
}

void printInorder(BSTree Root){
	if (Root==NULL) return;
	printInorder(Root->left);
	printf("%s	%s\n",Root->key,Root->vn);
	printInorder(Root->right);
}

void printPreorder(BSTree Root){
	if (Root==NULL) return;
	printf("%s	%s\n",Root->key,Root->vn);
	printPreorder(Root->left);
	printPreorder(Root->right);
}

void printPosorder(BSTree Root){
	if (Root==NULL) return;
	printPosorder(Root->left);
	printPosorder(Root->right);
	printf("%s	%s\n",Root->key,Root->vn);
}
