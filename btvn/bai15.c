#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char sobd[11],hoten[31];
	double diem;
}sinhvien;


int nhapdulieu(sinhvien SV[])
{
	int n,i,*fptr;
	char fname[]="thisinh.dat",s[4];
	if ((fptr=fopen(fname,"r"))==NULL)
	{
		printf("Canot open %s\n",fname);
		return 0;
	}else
	{
		fscanf(fptr,"%d",&n);
		for (i=0; i<n; i++) 
		{
			while (fgetc(fptr)!='\n') ;
			fgets(SV[i].sobd,11,fptr); SV[i].sobd[10]='\0';
			fgets(SV[i].hoten,31,fptr);	SV[i].hoten[30]='\0';
			fgets(s,5,fptr); 
			SV[i].diem=atof(s);
		}
		fclose(fptr);
    }
	return n;	
}

void hienthi(sinhvien SV[], int n)
{
	printf("%-3s%-10s%-30s%-5s\n","STT","Sobaodanh","Ho va ten","Diem");
	int i;
	for (i=0; i<n; i++)
		printf("%-3d%-10s%-30s%-5.2f\n",i+1,SV[i].sobd,SV[i].hoten,SV[i].diem);
}

void ketqua(sinhvien SV[], int n)
{
	int i,*fptr;
	char fname[]="thisinh2.dat";
	if ((fptr=fopen(fname,"w"))==NULL)
	{
		printf("Canot open %s\n",fname);
		return 0;
	}else
	{
		for (i=0; i<n; i++)
			if (SV[i].diem>=5) fprintf(fptr,"%-10s%-30s%-4.2f\n",
						SV[i].sobd,SV[i].hoten,SV[i].diem);
		fclose(fptr);
		
	}
}

int main()
{
	sinhvien SV[100];
	int n=nhapdulieu(SV);
	hienthi(SV,n);
	ketqua(SV,n);
	
	return 0;	
}
