#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

char filename[100];
int hang,cot,maloi;
char kituloi;

typedef char datatype;

typedef struct _node
{
	 datatype data;
	 struct _node *link;
}node;

void inmuitenmau()
{
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor,4);
    printf("%c",24);
    SetConsoleTextAttribute(hConsoleColor,7);
}

node* push(node *top,datatype x)
{
	node* new = (node*)malloc(sizeof(node));
	
	if (new==NULL) printf("No memory available\n");
	else
	{
		new->data=x;
		new->link=top;
		return new; 
	}
}

node* pop(node* top,datatype *data)
{
	if (top==NULL)	printf("Stack is empty\n");
	else
	{
		node* temp;
		*data=top->data;
		temp=top->link;
		free(top);
		return temp;
	}
	
}

int ktmongoac(char ch)
{
	if (ch=='{' || ch=='(' || ch=='[' ) return 1;
	return 0;
}

int ktdongngoac(char ch)
{
		if (ch=='}' || ch==')' || ch==']' ) return 1;
		return 0;
}


int kiemtra(char ch1, char ch2)
{
	if (ch1=='{' && ch2=='}') return 1;
	if (ch1=='[' && ch2==']') return 1;
	if (ch1=='(' && ch2==')') return 1;
	return 0;
}


int nhapduongdan()
{
	printf("\nHay nhap ten file can kiem tra: "); 
	scanf("%s",&filename);
		
	FILE* fptr;
	if ((fptr=fopen(filename,"r"))==NULL)
	{
		printf("Khong the mo file");
		return 0;
	}
	
	printf("\n");
	do
	{
		char ch=fgetc(fptr);
		if (feof(fptr)!=0) break;
		printf("%c",ch);
	}while(1);
	fclose(fptr);
	return 1;
}


void kiemtradaungoac()
{
	FILE* fptr=fopen(filename,"r");
	node* top=NULL;
	
	int hang1,cot1;
	hang=1; cot=0; maloi=0;
	do
	{
		char ch=fgetc(fptr);
		if (feof(fptr)!=0) break;
	
		if (ch=='\n')
		{
			hang++;
			cot=0;
		}else cot++;
		
		if (ktmongoac(ch)) 
		{
			if (top==NULL)
			{
				hang1=hang; cot1=cot;
			}
			top=push(top,ch);	
		}
		else
			if (ktdongngoac(ch))
			{
				if (top==NULL) 	
				{
					maloi=1; kituloi=ch; break;
				}
				else
				{
					char ch2; 
					top=pop(top,&ch2);
					if (kiemtra(ch2,ch)==0)  
					{
						maloi=2; kituloi=ch; break;
					}
				} 
			}	
	}while(1);
	fclose(fptr);
	
	if (maloi==0 && top!=NULL)  
	{
		top=pop(top,&kituloi);
		hang=hang1; cot=cot1;
		maloi=3; 
	}
}

void ketqua()
{	
	if (maloi==0) printf("Dau ngoac hop le\n");else
	{
		printf("Hang %d Cot %d :",hang,cot);
		if (maloi==1) printf("Thieu dau ngoac mo cua dau %c\n",kituloi);
		else if (maloi==2) 
		  	printf("Khong tuong ung voi dau mo ngoac gan nhat: %c\n",kituloi);
		else printf("Thieu dau dong ngoac cua dau %c\n",kituloi);
		
		printf("\n\n");
		FILE* fptr=fopen(filename,"r");
		int u=1,v=0; 
		do
		{
			char ch=fgetc(fptr);
			if (feof(fptr)!=0) break;
			if (ch=='\n')
			{
				u++; v=0;
			}else v++;	
			printf("%c",ch);
			
			if (u==hang+1 && v==0)
			{
				while (cot>1)
				{
					printf(" ");
					cot--;
				}
				inmuitenmau(); printf("\n");
			}
		}while(1);
		fclose(fptr);
		if (u==hang)
		{
			printf("\n");
			while (cot>1)
			{
				printf(" ");
				cot--;
			}
			inmuitenmau(); printf("\n");
		}
		
	}
}


int menu()
{
	printf("\n------------MENU-----------\n");
	printf("1. Nhap ten file ma nguon\n");
	printf("2. Kiem tra dau ngoac\n");
	printf("3. Thoat\n");
	printf("Chon: ");
	int ch;  scanf("%d",&ch);
	while (ch>3 || ch<1)
	{
		printf("Chon sai! Nhap lai: ");
		scanf("%d",&ch);
	}
	return ch;
}

int main()
{	

	while (1)
	{
		int ch=menu();
		switch (ch)
		{
			case 1: if (nhapduongdan()==0) return; break;
			case 2: kiemtradaungoac(); ketqua(); break;
			case 3: return;
		}
		printf("\n");
	}	
}
