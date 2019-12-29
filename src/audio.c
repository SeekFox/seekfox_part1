/**
 * @file audio.c
 * @author Gael Gamba
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/audio.h"






	///////////////////////////////////
	//    Librarie du descripteur    //
	///////////////////////////////////

Histogramme initHistogramme(){return NULL;}

Histogramme addFenetre(Histogramme oldHistogram){

	Histogramme newHistogram = (Histogramme)malloc(sizeof(Fenetre));

	newHistogram->nextFenetre = oldHistogram;
	newHistogram->subdivision = init_PILE();
	if(oldHistogram == NULL)
		newHistogram->name = 0;
	else
		newHistogram->name = oldHistogram->name+1;
	return newHistogram;
}


	//////////////////////////////
	//   CREER UN DESCRIPTEUR   //
	//////////////////////////////
void resetFileCursor(FILE* p_file, int fileType){
	if(fileType == WAV_FILE)	//Les .wav ont un en tete de 56 octets qui ne nous est pas utile ici
		fseek(p_file, WAV_OFFSET, SEEK_SET);
	else
		fseek(p_file, 0, SEEK_SET);
}


unsigned int getAudioFileSize(FILE* p_file, int fileType){ //Calculer la taille d'un fichier audio, /!\ change le curseur de position, possible TODO a faire
	unsigned int size;
	double placeholder; //On est pas intéressé par les valeurs, faut juste une variable pour pouvoir lire

	resetFileCursor(p_file, fileType);

	do{
		fread(&placeholder, sizeof(double), 1, p_file);
		size++;
	}while(!feof(p_file));

	return size;
}
 
int getSubdivisionValue(double val, int nbSubdivisions){	//Les sous-divisions sont comprises entre -1 et 1
	double temp;
	temp = (nbSubdivisions/2)*val + (nbSubdivisions/2); 
	return (int)temp;
}

DescripteurAudio creerDescripteurAudio(FILE* p_file, int tailleFenetre, int nbSubdivisions, int fileType){	
	
	DescripteurAudio newDescripteur;
	
	//unsigned int fileSize;
	double newFenetre[tailleFenetre];					//Nouvelle fenêtre de travail
	//int sizeSubdivision = tailleFenetre/nbSubdivisions;	//Taille d'une subdivision
	int newHistogramLine[nbSubdivisions+1];			//Nouvelle ligne de l'histogramme final
	int subPosition;
	ELEMENT temp;
	int FenetresCount = 0;

	//fileSize = getAudioFileSize(p_file, fileType);
	resetFileCursor(p_file, fileType);

	Histogramme newHistogram = initHistogramme();

	do{																
		for(int x = 0; x < nbSubdivisions; x++)
			newHistogramLine[x] = 0;	//RAZ de l'histogramme

		fread(&newFenetre, sizeof(double),tailleFenetre, p_file);	//Lire une nouvelle fenetre
		FenetresCount++;
		newHistogram = addFenetre(newHistogram);					//La rajouter à l'histogramme

		for(int i = 0; i < tailleFenetre; i++){									//Remplir les sousdivisions de cette fenetre
			subPosition = getSubdivisionValue(newFenetre[i], nbSubdivisions);
			newHistogramLine[subPosition]++;			//TODO(ish) : Possibilité d'améliorer la performance stockant directement
		}

		for(int i = 0; i < nbSubdivisions; i++){										//Pile possiblement stockée a l'envers, on vois plus tard si ça pose soucis
			temp = affect_ELEMENT(newHistogramLine[i]);									//Deso Gaël du futur pour ce que je m'apprête a ne pas faire
			newHistogram->subdivision = emPILE(newHistogram->subdivision, temp);		//De toute façon si tout est formé de la même manière ça devrait pas changer les comparaisons
		}


	}while(!feof(p_file));

	newDescripteur.data = newHistogram;
	newDescripteur.nbFenetres = FenetresCount;
	return newDescripteur;
}

void displayFenetre(Histogramme display){
	if(display == NULL)
		printf("Fenetre est vide\n");
	else{
		printf("nom : %3d comprenant : ", display->name);
		affiche_PILE(display->subdivision);
		printf("\n");
	}
}

void displayDescripteur(DescripteurAudio display){
	Histogramme index;

	index = display.data;
	for(int i = 0; i < display.nbFenetres; i++){
		displayFenetre(index);
		index = index->nextFenetre;
	}
}
//TODO : Transformer un descripteur en string

//TODO : Transformer un string en descripteur
//TODO : Comparer 2 descripteurs