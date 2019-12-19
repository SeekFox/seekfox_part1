#include <stdio.h>
#include <stdlib.h>

void allouerMemoire(int **tab,int taille){
	*tab = (int*)calloc(taille,sizeof(int)*taille);
	if(tab == NULL) exit(EXIT_FAILURE);
}

int main(void){
	int *tab = NULL;
	allouerMemoire(&tab,5);
	for(int i=0;i<5;i++){
		tab[i] = i;
		printf("%d",tab[i]);
		}	
	return 0;
}
