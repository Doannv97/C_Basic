#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

const char filename[]="SV.dat";

typedef struct _sinhvien
{
	char mssv[10],hoten[20];
	float diem;
} sinhvien;


void nhapdulieu()
{
	FILE* fptr;
	if ((fptr=fopen(filename,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return ;
	}

	int n=0;
	printf("\n\n---Nhap thong tin sinh vien: \n");
	while(1)
	{
      	sinhvien data;
		n++;
		printf("\nSinh vien thu %d\n",n);
		printf("  Maso SV: ");  scanf("%s",data.mssv);
		printf("  Ho va ten: ");  while (getchar()!='\n');
		gets(data.hoten);
        if (strcmp(data.hoten,"###")==0)  break;
		printf("  Diem thi: ");  scanf("%f",&data.diem);
	    while (data.diem>10 || data.diem<0)
		{
			printf("    Nhap diem loi! Nhap lai: ");
			scanf("%f",&data.diem);
		}
        int irc=fwrite(&data,sizeof(sinhvien),1,fptr);
	}
    fclose(fptr);
}


int doctep(sinhvien SV[])
{
    FILE *fptr;
	if ((fptr=fopen(filename,"rb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return 0;
	}else
	{
        int n=0;
		do
		{
            sinhvien data;
			int irc=fread(&data,sizeof(sinhvien),1,fptr);
			if (feof(fptr)!=0) break;
            SV[n++]=data;
		}
		while (1);
		
		fclose(fptr);
		printf("Doc tep thanh cong! \n");
        return n;
    }
}

void indanhsach(sinhvien SV[], int n)
{
	printf("\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
    int i;
    for (i=0; i<n; i++)
	{
		printf("%-10s%-20s%-10.2f\n",SV[i].mssv,SV[i].hoten,SV[i].diem);
	}
}

void sapxep(sinhvien SV[], int n)
{
     int i,j;
     for (i=0; i<n-1; i++)
       for (j=i+1; j<n; j++)
         if (strcmp(SV[i].mssv,SV[j].mssv)>0)
           {
                 sinhvien temp=SV[i];
                 SV[i]=SV[j];
                 SV[j]=temp;
           }
}

void timkiem(sinhvien SV[], int n)
{
     char ch[10];
     printf("Nhap ma so sinh vien can tim: "); scanf("%s",ch);

     int left=0, right=n-1, mid;
     do
       {
         mid=(left+right)/2;
         if (strcmp(SV[mid].mssv,ch)==0)
           {
             printf("Sinh vien can tim la:\n  Ho ten: %s\n  Diem %.2f\n",
                    SV[mid].hoten,SV[mid].diem);
             return;
           }
         else if (strcmp(SV[mid].mssv,ch)>0) right=mid-1; else left=mid+1;
       }while (left<=right);
       
	  printf("Khong tim thay!\n ");	
}

int menu()
{
	printf("\n-------------------MENU------------------\n");
	printf("1. Nhap thong tin va in ra file\n");
	printf("2. Doc thong tin tu tep\n");
	printf("3. Sap xep\n");
	printf("4. Tim kiem sv\n");
	printf("5. Thoat\n");
	printf("Chon: ");
	int c; scanf("%d",&c);
	while (c>5 || c<1)
	{
		printf("Nhap sai! Nhap lai: ");
		scanf("%d",&c);
	}
	return c;
}

int main()
{

    sinhvien SV[MAX];
    int n;
	while (1)
	{
		char c=menu();
		switch (c)
		{
		case 1: nhapdulieu(); break;
		case 2: n=doctep(SV); indanhsach(SV,n);  break;
		case 3: sapxep(SV,n);   indanhsach(SV,n); break;
        case 4: timkiem(SV,n);  break;
		case 5: return 0;
		}

	}
}
