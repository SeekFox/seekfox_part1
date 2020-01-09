#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(void){
	int *tab;
	tab = calloc(5*5,sizeof(int));
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			tab[i][j]= 3;
			printf("%d ",tab[i][j]);
		}
		printf("\n");
	}

return 0;
}