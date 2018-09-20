#include"BST.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

node* makeNode(keyType key, char dochoi[]){
	node* new=(node*)malloc(sizeof(node));
	if (new==NULL) return NULL; 
	else{
		new->key=key;
		strcpy(new->dochoi,dochoi);
		new->left=NULL;
		new->right=NULL;
		return new;
	}
}

int insertNode(BSTree* Root, keyType key, char dochoi[]){
	if (*Root==NULL) *Root=makeNode(key,dochoi);
	else if (key<(*Root)->key) insertNode(&((*Root)->left),key,dochoi);
	else if (key>(*Root)->key) insertNode(&((*Root)->right),key,dochoi);
	else return 0;
	return 1;
}

node* search(BSTree Root, keyType key){
	if (Root==NULL) return NULL;
	if (Root->key==key) return Root;
	if (key<Root->key) return search(Root->left,key);
	if (key>Root->key) return search(Root->right,key);
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

node* deleteNode(BSTree Root, keyType key){
	if (Root==NULL) return Root;
  	if (key<Root->key) Root->left=deleteNode(Root->left,key);
	else if (key>Root->key) Root->right=deleteNode(Root->right,key);
	else{							  
      	if (Root->left!=NULL && Root->right!=NULL){
			node* tmp=findMin(Root->right);
			Root->key=tmp->key;
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
	printf("%d\t%s\n",Root->key,Root->dochoi);
	printInorder(Root->right);
}
