#include <stdlib.h>
#include <stdio.h>
#include "FIFO.h"

void Init_File(FIFO f){
	f.debut_file=NULL;
	f.fin_file=NULL;
}

void Affiche_file(FIFO *f){
	if(File_estVide(*f))
		printf("Pile est Vide");
	else {
		Cell *temp =f->debut_file;
		while(temp !=NULL){
			printf("%c ",(*temp).e);
			temp=(*temp).ptr_suiv;
		}
		printf("\n");
	}
}

int File_estVide(FIFO f){
	return(f.debut_file==NULL);
}

FIFO Enfiler(FIFO *f, char e){
	Cell *temp;
	temp=(Cell*)malloc(sizeof(Cell));
	(*temp).e=e;
	(*temp).ptr_suiv = f->fin_file;
	if (f->debut_file == NULL)
		f->debut_file = temp;
	else {
		/*	(*f.fin_file).ptr_suiv=temp;
		f.fin_file=temp;*/
		Cell* actuel = f->debut_file;
		while (actuel->ptr_suiv != NULL)
			actuel = actuel->ptr_suiv;
		actuel->ptr_suiv = temp;
	}
	return(*f);	
}

FIFO Defiler(FIFO *f, char *adr){
	if(!File_estVide(*f)){
		Cell *temp = f->debut_file;
		*adr=(*f->debut_file).e;
		printf("La valeur enlevée est ");
		printf("%c",*adr);
		printf("\n");
		f->debut_file=temp->ptr_suiv;
		free(temp);
		}
	return(*f);
}

int FIFO_diff(FIFO *f1, FIFO *f2) {
	int diff = 0;
	Cell *temp1 = f1->debut_file, *temp2 = f2->debut_file;
	do{
		if (temp1->e != temp2->e) {
			diff = 1;
		//	break;
		}
		temp1 = (*temp1).ptr_suiv;
		temp2 = (*temp2).ptr_suiv;
	} while (temp1 != NULL || temp2);
	return(diff);
}