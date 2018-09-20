#include<stdio.h>
#include<stdlib.h>
#define MAX 20

const char filename[]="sinhvien.dat";
const char filename2[]="sinhvien2.dat";

typedef struct
{
	char mssv[10],hoten[20];
	double diem;
} datatype;

typedef struct 
{
	datatype data[MAX];
	int top;
}stacktype;


void push(stacktype *stack, datatype x)
{
	if (stack->top==MAX) printf("Stack is FULL\n");
	else
			stack->data[stack->top++]=x;
}

datatype pop(stacktype *stack)
{
	if (stack->top==0) printf("Stack is EMPTY\n");
	else
			return stack->data[--stack->top];
} 



void doctep(stacktype *stack)
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
			push(stack,data);		
		}
		while (1);
		fclose(fptr);
		printf("Doc tep thanh cong\n");
	}
}


void indanhsach(stacktype *stack)
{
	printf("\n\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
			

	while (stack->top!=0)
	{
		datatype data=pop(stack);	
		printf("%-10s%-20s%-10.2f\n",data.mssv,data.hoten,data.diem);
	}
	
}


void ghiratep(stacktype *stack)
{
	FILE* fptr;
	if ((fptr=fopen(filename2,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return;
	}else
	{
			
		while (stack->top!=0)
		{
			datatype data=pop(stack); 
			int irc=fwrite(&data,sizeof(datatype),1,fptr);
		}	
		fclose(fptr);
		printf("Chep Thanh Cong\n");
	}
}



int main()
{
	stacktype stack;
	stack.top=0;
	
	doctep(&stack);
	indanhsach(&stack);
	//ghiratep(&stack);
	
}


