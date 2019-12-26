#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef int **matrice;
typedef int *bits;


int main(void){
	char s[5];
	FILE *f,*f2;
	int i,x=0;
	f = fopen("fichiertexte.txt","a+");
	//if(i == EOF)printf("le fichier est vide\n");
	fscanf(f,"%s",s);
	printf("%s\n",s);
	fclose(f);
return 0;
}