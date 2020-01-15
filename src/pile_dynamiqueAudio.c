/**
 * @file pyle_dynamiqueAudio.c
 * @author Gael Gamba
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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

PILE emPILEVal(PILE p_oldPile, int valeur){
	PILE p_newPile;
	ELEMENT e;

	e = affect_ELEMENT(valeur);
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

PILE coPILE(PILE* cpy){	
	int temp;
	PILE INV_temp = init_PILE();	//Pile pour inverser
	PILE newPile = init_PILE();
	
	if(*cpy != NULL){
		while(!PILE_estVide(*cpy)){					//Copier la pile dans une pile tampon pour l'inverser, on doit la copier 2 fois 
			*cpy = dePILE(*cpy, &temp);				//pour qu'elle garde son sens
			INV_temp = emPILEVal(INV_temp, temp);	//
		}

		while(!PILE_estVide(INV_temp)){				//Recopier le tampon dans les 2 piles
			INV_temp = dePILE(INV_temp, &temp);		//
			newPile = emPILEVal(newPile, temp);		//
			*cpy = emPILEVal(*cpy, temp);		
		}
	}

	return newPile;
}


int taillePILE(PILE pileATester){
	int nbElements = 0;
	PILE curseur = pileATester;
	while(curseur != NULL){
		nbElements++;
		curseur = curseur->nextCell;
	}
	return nbElements;
}

int getElementValue(PILE pileAVider, int elementNb){
	PILE curseur = pileAVider;

	if(taillePILE(pileAVider) <= elementNb)
		return -1;

	for(int i = 0; i<elementNb ; i++)
		curseur = curseur->nextCell;

	return curseur->valeur.val; 
}
 