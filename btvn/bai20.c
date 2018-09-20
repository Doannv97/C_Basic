#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const char filename[]="sinhvien.dat";

typedef struct
{
	char mssv[10],hoten[20];
	double diem;
} sinhvien;

typedef struct node
{
	sinhvien data;
	struct node* next;
}node;

node* nhapdulieu(node* root)
{
	node* cur=root;
	int i,n;
	printf("Nhap so luong sinh vien: ");  scanf("%d",&n);
	printf("\n****Nhap thong tin cho sinh vien****\n");
		
	for (i=0; i<n; i++)
	{
		node *new=(node*)malloc(sizeof(node));
		printf("\n--Sinh vien thu %d\n",i+1);
		printf("  Maso SV: ");  scanf("%s",(new->data).mssv);
		printf("  Ho va ten: ");  while (getchar()!='\n');
		gets((new->data).hoten);
		printf("  Diem thi: ");  scanf("%lf",&((new->data).diem));
		
		if (root==NULL) 
		{
			root=new; 
			new->next=NULL;
		}else
		{
			cur->next=new;
			new->next=NULL;
		}
		cur=new;
	}
	return root;
}

void indanhsach(node* root)
{	
	printf("\n***Danh sach sinh vien***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
	
	node *cur=root;
	while (cur!=NULL)
	{
		printf("%-10s%-20s%-10.2f\n",(cur->data).mssv,
		  (cur->data).hoten,(cur->data).diem);
		cur=cur->next;
	}
}


node* themsv(node* root)
{
	printf("\nNhap thong tin sv can nhap them: \n");
	node *new=(node*)malloc(sizeof(node));
	printf("  Maso SV: ");  scanf("%s",(new->data).mssv);
	printf("  Ho va ten: ");  while (getchar()!='\n');
								gets((new->data).hoten);
	printf("  Diem thi: ");  scanf("%lf",&((new->data).diem));

	node* cur=root;
	while (cur->next!=NULL) cur=cur->next;

	cur->next=new;
	new->next=NULL;
		
	printf("\n");
	return root;
}

void timsv(node* root)
{
	char str[10];
	printf("Nhap mssv can tim: "); scanf("%s",str);

	node* cur=root;
	while (cur!=NULL)
	{
		if (strcmp((cur->data).mssv,str)==0)
		{
			printf("SV can tim la:\n  MSSV=%s\n  Ho ten=%s\n  Diem=%.2f\n",
			  (cur->data).mssv,(cur->data).hoten,(cur->data).diem);
			return ;
		}
		cur=cur->next;
	}
	printf("Khong tim thay\n");
}

node* xoasv(node* root)
{
	char str[10];
	printf("Nhap mssv can xoa: "); scanf("%s",str);

	node* cur,*curprev;
	cur=root;
	
	if (strcmp((cur->data).mssv,str)==0)
	{
		root=cur->next;
		free(cur);
		printf("Xoa thanh cong\n");
		return root;
	}
	
	while (cur->next!=NULL)
	{
		curprev=cur;
		cur=cur->next;
		if (strcmp((cur->data).mssv,str)==0)
		{
			curprev->next=cur->next;
			free(cur);
			printf("Xoa thanh cong\n");
			return root;
		}
	}
	printf("Xoa that bai!\n");
	return root;
}

void ghiratep(node* root)
{
	FILE* fptr;
	if ((fptr=fopen("sinhvien.dat","wb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return;
	}else
	{

		node* cur=root;

		while (cur!=NULL)
		{
			int irc=fwrite(&(cur->data),sizeof(sinhvien),1,fptr);
			cur=cur->next;
		}

		fclose(fptr);
		printf("Chep Thanh Cong\n");
	}
}

node* doctep(node* root)
{
	FILE *fptr;
	if ((fptr=fopen(filename,"rb"))==NULL)
	{
		printf("Khong mo duoc file %s\n",filename);
		return root;
	}else
	{
		node* cur=root;

		do
		{
			if (feof(fptr)!=0) break;
			node* new=(node*)malloc(sizeof(node));
			int irc=fread(&(new->data),sizeof(sinhvien),1,fptr);
			if (feof(fptr)!=0)
			{
				free(new);
				break;
			}
			if (root==NULL) root=new; else cur->next=new;		
			cur=new;
		}
		while (1);	
		cur->next=NULL;
		fclose(fptr);
		printf(" Doc tep thanh cong! \n");
		return root;
	}
	
}

int choncachnhap()
{
	int c=0;
	printf("Chon cach nhap du lieu:\n  1.Tu ban phim\n  2.Tu tep nhi phan\n");
	printf("Chon: "); scanf("%d",&c);
	while (c!=1 && c!=2)
	{
		printf("Hay chon lai cach nhap: ");
		scanf("%d",&c);
	}

	printf("\n");
	return c;
}

void ketquathi(node* root)
{
	int dat=0,sum=0;
	node* cur=root;
	printf("\n***Danh sach sinh vien thi dat***\n");
	printf("%-10s%-20s%-10s\n","MSSV","Ho va ten","Diem");
	
	while (cur!=NULL)
	{
		sum++;
		if ((cur->data).diem >=4)
		{
			printf("%-10s%-20s%-10.2f\n",(cur->data).mssv,
		  		(cur->data).hoten,(cur->data).diem);
		  	dat++;
		}
		cur=cur->next;
	}
	printf("\n--Ti le sinh vien thi dat la: %d%%\n",(dat*100)/sum);
}

node* giaiphongds(node* root)
{
	node *del=root;

	while (del!=NULL)
	{
		root=root->next;
		free(del);
		del=root;
	}
	return root;
}


int chonchucnang()
{
	int c=0;
	printf("\n***Chon Cong viec\n");
	printf("1.Them 1 sinh vien\n");
	printf("2.Tim kiem 1 sinh vien\n");
	printf("3.Xoa 1 sinh vien\n");
	printf("4.Hien thi danh sach sinh vien\n");
	printf("5.Chep ds ra tep nhi phan\n");
	printf("6.Ds sv thi dat\n");
	printf("7.Thoat chuong trinh!\n");
	printf("CHon: ");  scanf("%d",&c);
	while (c>7 || c<1)
	{
		printf("Nhap sai! Nhap lai: ");
		scanf("%d",&c);
	}
	printf("\n");
	return c;
}


int main()
{
	node* root=NULL;

	int c=choncachnhap();
	if	(c==1) root=nhapdulieu(root); else doctep(root);

	if (root==NULL)
	{
		printf("\n!!!Danh sach rong - Chuong trinh ket thuc");
		return 0;
	}

	while (1)
	{
		c=chonchucnang();
		switch (c)
		{
			case 1: root=themsv(root); break;
			case 2: timsv(root); break;
			case 3: root=xoasv(root); break;
			case 4: indanhsach(root); break;
			case 5: ghiratep(root); break;
			case 6: ketquathi(root); break;
			case 7: return 1;
		}
		printf("\n");
	}
	root=giaiphongds(root);
}
