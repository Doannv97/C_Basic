#include<stdio.h>
#include<stdio.h>
#define MAX 100

const char filename[]="sanpham.txt";

typedef struct _sanpham
{
	int ma;
	char ten[20],mota[100];
	int gia,sl;
}sanpham;

void nhapsanpham()
{
	FILE* fptr;
	if ((fptr=fopen(filename,"wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return ;
	}
	
	int n=0;
	printf("\n\n---Nhap thong tin cac san pham----\n");
	while(1)
	{
		n++;
      	sanpham data; data.ma=0;
		printf("\nSan pham thu %d\n",n);
		printf("  Ma san pham: "); scanf("%d",&data.ma); 
		if (data.ma==0)
		{
			while (getchar()!='\n');
			break; 
		}
	    while (data.ma>500 || data.ma<101)
		{
			
			printf("    Ma san pham loi! Nhap lai: ");
			scanf("%d",&data.ma);
		}
		while (getchar()!='\n');
		printf("  Ten san pham: ");  gets(data.ten);
		printf("  Mo ta san pham: "); gets(data.mota);
		printf("  Gia san pham: "); scanf("%d",&data.gia);
		printf("  So luong: "); scanf("%d",&data.sl); 
        int irc=fwrite(&data,sizeof(sanpham),1,fptr);
	}
    fclose(fptr);
}

int doctep(sanpham SP[])
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
            sanpham data;
			int irc=fread(&data,sizeof(sanpham),1,fptr);
			if (feof(fptr)!=0) break;
            SP[n++]=data;
		}
		while (1);
		
		fclose(fptr);
		printf("Doc tep thanh cong! \n");
        return n;
    }
}

void indanhsach(sanpham SP[], int n)
{
	printf("\n-------------Danh sach san pham--------------\n");
	printf("%-5s%-10s%-15s%-8s%-8s\n","Ma","Ten","Mo ta","Gia","So luong");
    int i;
    for (i=0; i<n; i++)
	{
		printf("%-5d%-10s%-15s%-8d%-8d\n",SP[i].ma,SP[i].ten,SP[i].mota,
									SP[i].gia,SP[i].sl);
	}
}


void timkiem(sanpham SP[], int n)
{
	int masp;
	printf("\nNhap ma SP can tim: "); scanf("%d",&masp);
	
	int sp=-1,count=1;
	int inf=0,sup=n-1,mid;
	while (inf<=sup)
	{
		mid=(inf+sup)/2;
		count++; if (SP[mid].ma==masp) 
				 {
				 	sp=mid;
				 	break;
				 }
		count++; if (SP[mid].ma>masp) sup=mid-1; else inf=mid+1;
		count++;
	}
	
	if (sp==-1) printf("\n !!!Khong tim thay sap pham\n");
	else
	{
		printf("San pham can tim la:\n");
		printf("  Ten: %s\n  Mota: %s\n  Gia:  %d\n  Soluong: %d\n",
			SP[sp].ten,SP[sp].mota,SP[sp].gia,SP[sp].sl);
	}
	
	printf("So phep so sanh can thiet la: %d\n",count);
	
}

int menu()
{
	printf("\n-------------MENU------------\n");
	printf("1. Nhap thong tin san pham\n");
	printf("2. Doc tep\n");
	printf("3. Tim kiem san pham\n");
	printf("4. Thoat\n");
	printf("Chon: ");
	int c; scanf("%d",&c); 
	while (c>4 || c<1)
	{	
	printf("!!!%d\n",c);
	
		printf("Chon sai! Chon lai: ");
		scanf("%d",&c);
	}
	return c;
}

int main()
{
	sanpham SP[MAX];
	int n=0;
	
	
	while (1)
	{
		int c=menu();
		switch (c)
		{
			case 1: nhapsanpham(); break;
			case 2: n=doctep(SP); indanhsach(SP,n);break;
			case 3: timkiem(SP,n); break;
			case 4: return;
		}
		printf("\n");
	}
}
