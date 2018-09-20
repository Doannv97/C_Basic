#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 4

const char filename[]="sinhvien.dat";
const char filename2[]="sinhvien.dat";

typedef struct
{
	char mssv[10],hoten[20];
	double diem;
} datatype;


datatype Queue[MAX];
int front,rear;

int sizeQ()
{
	return (MAX+rear-front)%MAX;
}


void enQueue(datatype x)
{
	if (sizeQ()==MAX-1) printf("Queue is full\n");
	else
	{
		Queue[rear]=x;
		rear=(rear+1)% MAX;
	}	
}

datatype deQueue()
{
	if (sizeQ()==0) printf("Queue is empty\n");
	else 
	{
		datatype temp=Queue[front];
		front=(front+1)%MAX;
		return temp;
	}
}


void doctep()
{
	FILE *fptr;
	if ((fptr=fopen(filename,"rb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return;
	}else
	{	
		do
		{
			datatype data;
			int irc=fread(&data,sizeof(datatype),1,fptr);
			if (feof(fptr)!=0) break;
			enQueue(data);		
		}
		while (1);
		fclose(fptr);
		printf("Doc tep thanh cong\n");
	}
}


void indanhsach()
{
	printf("\n\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
			

	while (front!=rear)
	{
		datatype data=deQueue();	
		printf("%-10s%-20s%-10.2f\n",data.mssv,data.hoten,data.diem);
	}
	
}


void ghiratep()
{
	FILE* fptr;
	if ((fptr=fopen(filename2,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return;
	}else
	{
			
		while (front!=rear)
		{
			datatype data=deQueue(); 
			int irc=fwrite(&data,sizeof(datatype),1,fptr);
		}	
		fclose(fptr);
		printf("Chep Thanh Cong\n");
	}
}

int main()
{
	doctep();
	//indanhsach();
	ghiratep();
	
}
