#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* allouerMemoire(int *tab,int taille){
	tab = malloc(taille*sizeof(int));
	if(tab == NULL)exit(EXIT_FAILURE);
	return tab;
}

int main(void){
	int *tab;
	tab = allouerMemoire(tab,2);
	tab[1] = 2;
	printf("%d\n",tab[1]);
	return 0;
	}
