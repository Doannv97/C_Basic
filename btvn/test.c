#include<string.h>
#include<stdio.h>

int stringcmp(char a[], char b[]){
	int i=0, lena=strlen(a), lenb=strlen(b);
	while (1){
		if (a[i]<b[i]) return -1;
		else if (a[i]>b[i]) return 1;
		else{
			i++;
			if (i==lena && i==lenb) return 0;
			if (i==lena) return -1;
			if (i==lenb) return 1;
		}
	}
}

int main()
{
	char a[10],b[10];
	scanf("%s%s",a,b);
	
	printf("%d\n",stringcmp(a,b));
	
	strcpy(a,b); printf("a\n");
}
