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

typedef struct _node
{
	 datatype data;
	 struct _node *link;
}node;

typedef struct _Queue	
{
	node* front;
	node* rear;
}Queue;


void enQueue(Queue *Q,datatype data)
{	
	node* new=(node*)malloc(sizeof(node));
	new->data=data;
	new->link=NULL;
	
	if (Q->front==NULL) Q->front=new;
	else  (Q->rear)->link=new;

	Q->rear=new;
}

datatype deQueue(Queue *Q)
{
	if (Q->front==NULL) 
	{
		printf("Queue is empty\n");
		return;
	}
	
	node* temp=Q->front; 
	if (Q->front==Q->rear)
	{		
		Q->front=NULL;
		Q->rear=NULL;
	}else	Q->front=temp->link;
	return temp->data;
	free(temp);
}

void doctep(Queue *Q)
{
	FILE *fptr;
	if ((fptr=fopen(filename,"rb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return ;
	}else
	{	
		do
		{
			datatype data;
			int irc=fread(&data,sizeof(datatype),1,fptr);
			if (feof(fptr)!=0)	break;
			enQueue(Q,data);
			
		}
		while (1);
		fclose(fptr);
		printf("Doc tep thanh cong! \n");
	}	
}

void indanhsach(Queue *Q)
{
	printf("\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
	while (Q->front!=NULL)
	{
		datatype data;
		data=deQueue(Q);	
		printf("%-10s%-20s%-10.2f\n",data.mssv,data.hoten,data.diem);
	}
}

void ghiratep(Queue *Q)
{
	FILE* fptr;
	if ((fptr=fopen(filename2,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return ;
	}else
	{		
		while (Q->front!=NULL)
		{
			datatype data;
			data=deQueue(Q);
			int irc=fwrite(&data,sizeof(datatype),1,fptr);
			
		}
		fclose(fptr);
		printf("Chep Thanh Cong\n");
	}
}


int main()
{
	Queue *Q=(Queue*)malloc(sizeof(Queue));
	Q->front=NULL;
	Q->rear=NULL;
	doctep(Q);
	indanhsach(Q);
	//ghiratep(Q);

}
