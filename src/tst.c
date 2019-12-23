#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int** allouerMemoire(int **tab,int lignes,int colonnes){

	tab = malloc(lignes*sizeof(int));
	if(tab == NULL)exit(EXIT_FAILURE);

	for(int i=0;i<lignes;i++){
		tab[i] = malloc(colonnes*sizeof(int));
		if(tab[i] == NULL)exit(EXIT_FAILURE);
	}

	return tab;
}

int main(void){
	int **tab;
	tab = allouerMemoire(tab,2,2);
	tab[0][0] = 2;
	printf("%d\n",tab[0][0]);
}