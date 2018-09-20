#include<stdio.h>
#include<string.h>

void toLower(char str[]){
	int i;
	for (i=0; i<strlen(str); i++)
		if (str[i]>='A' && str[i]<='Z') str[i]+='a'-'A';
}

int main(){
	char str[100],s[20],n=0,kq[100];
	gets(str); toLower(str);
	
	int i;
	for (i=0; i<strlen(str); i++){
		if (str[i]>='a' && str[i]<='z') s[n++]=str[i];
		else if (str[i]==' ' || str[i]==',' || str[i]=='.'){
			s[n]='\0';
			n=0;

			node* tmp=search(*Root,str);
			if (tmp!=NULL){
				strcat(kq,tmp->vn); 
				strcat(kq," ");
			}
		}
	}
	
	
	
}

