#include <stdio.h>
#include <stdlib.h>
#include "../include/pile_dynamiqueAudio.h"


PILE init_PILE(){
	return NULL;
}

void affiche_PILE(PILE display){
	PILE p_temp;

	p_temp= display;
	
	if(p_temp == NULL)
		printf("La pile est vide");
	while(p_temp != NULL){
		affiche_ELEMENT(p_temp->valeur);
		p_temp = p_temp->nextCell;printf(" ");
	}
}


PILE emPILE(PILE p_oldPile, ELEMENT e){
	PILE p_newPile;
	
	p_newPile = (PILE)malloc(sizeof(CELLULE));
	
	if (p_oldPile == NULL){
		(*p_newPile).valeur = e;
		(*p_newPile).nextCell = NULL;
	}else{
		(*p_newPile).nextCell = p_oldPile;
		(*p_newPile).valeur = e;
	}
	
	return p_newPile;
}

int PILE_estVide(PILE pileVide){
	if(pileVide == NULL)
		return 1;
	else
		return 0;
		
}

PILE dePILE(PILE newPile, int* oldTete){
	PILE oldAddress;
	*oldTete = -1;
	
	if(newPile != NULL){
		oldAddress = newPile;
		*oldTete = newPile->valeur.val;
		newPile = newPile->nextCell;
		free(oldAddress);
	}
	else{
		fprintf(stderr, "La pile est vide");	
	}
		
	return newPile;
}
