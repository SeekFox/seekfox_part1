/*#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int test_matrice(int x,int y,int matrice1[x][y],int matrice2[x][y]){
	int somme = 0;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			matrice1[i][j] = 1;
			matrice2[i][j] = 1;
			somme = somme + matrice1[i][j] + matrice2[i][j];
		}
	}
	return somme;
}
int main(void){
	int x,y;
	scanf("%d%d",&x,&y);
	int m1[x][y],m2[x][y];
	int somme = test_matrice(x,y,m1,m2);
	printf("%d\n",somme);
return 0;
}