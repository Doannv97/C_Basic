#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const char filename[]="sinhvien.dat";
const char filename2[]="sinhvien.dat";

typedef struct
{
	char mssv[10],hoten[20];
	double diem;
} datatype;

typedef struct node
{
	 datatype data;
	 struct node *link;
}node;

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


node* ghiratep(node* top)
{
	FILE* fptr;
	if ((fptr=fopen(filename2,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return top;
	}else
	{		
		while (top!=NULL)
		{
			datatype data;
			top=pop(top,&data);
			int irc=fwrite(&data,sizeof(datatype),1,fptr);
			
		}
		fclose(fptr);
		printf("Chep Thanh Cong\n");
		return top;
	}
}



node* doctep(node* top)
{
	FILE *fptr;
	if ((fptr=fopen(filename,"rb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return NULL;
	}else
	{	
		do
		{
			datatype data;
			int irc=fread(&data,sizeof(datatype),1,fptr);
			if (feof(fptr)!=0)	break;
			top=push(top,data);
			
		}
		while (1);
		fclose(fptr);
		printf("Doc tep thanh cong! \n");
		return top;
		
	}	
}

node* indanhsach(node *top)
{
	
	printf("\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
	while (top!=NULL)
	{
		datatype data;
		top=pop(top,&data);	
		printf("%-10s%-20s%-10.2f\n",data.mssv,data.hoten,data.diem);
	}
	return top;
}


int main()
{
	node* top=NULL;
	top=doctep(top);
	top=indanhsach(top);
//	top=ghiratep(top);
}
