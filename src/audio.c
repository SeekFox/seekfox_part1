#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/audio.h"

#define SIMLIARITY_MAX_VALUE 0.01
#define SECONDE_PAR_VALEUR 0.0000616795061349 

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

Histogramme deleteFenetre(Histogramme oldHistogram, Fenetre* oldFenetre){
	Histogramme newHistogram = oldHistogram;

	newHistogram = newHistogram->nextFenetre;
	*oldFenetre = *oldHistogram;
	free(oldHistogram);
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
	int sizeSubdivision = tailleFenetre/nbSubdivisions;	//Taille d'une subdivision
	int newHistogramLine[nbSubdivisions+1];			//Nouvelle ligne de l'histogramme final
	int subPosition;
	ELEMENT temp;
	unsigned long int FenetresCount = 0;
	int nbElementsLus = 0;

	//fileSize = getAudioFileSize(p_file, fileType);
	resetFileCursor(p_file, fileType);

	Histogramme newHistogram = initHistogramme();

	do{																
		nbElementsLus = 0;
		for(int x = 0; x < nbSubdivisions; x++)
			newHistogramLine[x] = 0;	//RAZ de l'histogramme

		nbElementsLus = fread(&newFenetre, sizeof(double),tailleFenetre, p_file);	//Lire une nouvelle fenetre
		FenetresCount++;
		newHistogram = addFenetre(newHistogram);					//La rajouter à l'histogramme

		for(int i = 0; i < nbElementsLus; i++){									//Remplir les sousdivisions de cette fenetre
			subPosition = getSubdivisionValue(newFenetre[i], nbSubdivisions);
			newHistogramLine[subPosition]++;			//TODO(ish) : Possibilité d'améliorer la performance stockant directement
		}

		for(int i = 0; i < nbSubdivisions; i++){										//Pile possiblement stockée a l'envers, on vois plus tard si ça pose soucis	
			newHistogram->subdivision = emPILEVal(newHistogram->subdivision, newHistogramLine[i]);		//De toute façon si tout est formé de la même manière ça devrait pas changer les comparaisons
		}


	}while(!feof(p_file));

	newDescripteur.data = newHistogram;
	newDescripteur.nbFenetres = FenetresCount;
	newDescripteur.nbSubdivisions = nbSubdivisions;
	newDescripteur.tailleFenetre = tailleFenetre;
	
	return newDescripteur;
}

void displayFenetre(Histogramme display){
	if(display == NULL)
		printf("Fenetre est vide\n");
	else{
		printf("nom : %5d comprenant : ", display->name);
		affiche_PILE(display->subdivision);
		printf("\n");
	}
}

void displayDescripteur(DescripteurAudio display){
	Histogramme index;

	printf("Descripteur de %u fenetres de %u valeurs, avec %d subdivisions\n", display.nbFenetres, display.tailleFenetre, display.nbSubdivisions);
	index = display.data;
	for(int i = 0; i < display.nbFenetres; i++){
		displayFenetre(index);
		index = index->nextFenetre;
	}
}

//TODO : Transformer un descripteur en string

//TODO : Transformer un string en descripteur

char* fenetreToString(Fenetre workingFenetre, int* size){ //Attention, cela détruit la fenetre
	PILE workingPile = workingFenetre.subdivision;

	unsigned int taillePile = taillePILE(workingPile);
	char* newString = (char*)malloc(sizeof(char) * taillePile*7);//On laisse 5 chiffres + 1 séparateur par élement de la pile+1 de marge au cas où //TODO : protéger contre les gros nombres
	char temp[6] = "";
	int dataToSave = 0;
	unsigned int currentSize = 0;
	sprintf(newString,"%7u:", workingFenetre.name);
	currentSize = 8;
	if(newString == NULL)printf("PUTAIN");

	while(!PILE_estVide(workingPile)){
		workingPile = dePILE(workingPile,&dataToSave);
		sprintf(temp, "%4d,", dataToSave);
		for(int i = 0; i < 5; i++){
			newString[currentSize] = temp[i];
			currentSize++;
		}
	}
	newString[currentSize] = '|';
	currentSize++;
	*size = currentSize; 
	return newString;
}


int descripteurAudioToString(char* sortie, DescripteurAudio descToString){	//nbSubdivisions;tailleFenetre;nbFenetres
	char* newString = (char*)malloc(sizeof(char)*20);
	long unsigned int currentSize = 20;

	char* newFenetreString;
	sprintf(newString,"%4u;%7u;%7u", descToString.nbSubdivisions, descToString.tailleFenetre, descToString.nbFenetres);

	for(long unsigned int i =0; i < descToString.nbFenetres; i ++)
		return 2;
}


float getSimilarityValue(PILE* pile1, PILE* pile2, int tailleFenetre){
	float sommeDesDifferences = 0;
	unsigned int nbSubdivisions = 0;
	int val1 = 0;
	int val2 = 0;
	PILE cpy1, cpy2;		
	cpy1 = init_PILE();
	cpy2 = init_PILE();
	

	cpy1 = coPILE(pile1);
	cpy2 = coPILE(pile2);
	
	
	while((!PILE_estVide(cpy1)) && (!PILE_estVide(cpy2))){
		
		cpy1 = dePILE(cpy1, &val1);
		cpy2 = dePILE(cpy2, &val2);
		sommeDesDifferences += (float)(abs(val1 - val2));
		nbSubdivisions++;
	}

	return (sommeDesDifferences/(tailleFenetre*nbSubdivisions));		//Plus on est proche de 0 plus c'est la même chose
}

PILE comparerDescripteursAudio(DescripteurAudio jingle, DescripteurAudio fichierAudio){
	if(jingle.nbFenetres > fichierAudio.nbFenetres){
		return NULL;
	}
	int jingleEstComprisDansLeFichier = 0;
	int nameToSeconds = 0;
	PILE listeDesTimingsDesJingle = init_PILE();

	if(jingle.tailleFenetre != fichierAudio.tailleFenetre || jingle.nbSubdivisions != fichierAudio.nbSubdivisions)
		return NULL;

	Histogramme jingleHist = jingle.data;		//Juste pour éviter de taper jingle.data a chaque fois	
	Histogramme fileHist = fichierAudio.data;	//



	while(jingleHist != NULL && fileHist != NULL){
		
		if(getSimilarityValue(&jingleHist->subdivision, &fileHist->subdivision, jingle.tailleFenetre) <= SIMLIARITY_MAX_VALUE){	//Si on trouve la premiere fenetre dans le truc, on check les autres
			jingleEstComprisDansLeFichier = 1;
			
			while((jingleHist != NULL) && (fileHist!=NULL) && (jingleEstComprisDansLeFichier == 1)){			// On a la premiere fenetre, on vérifie que toutes les fenetres ressemblent une a une (probablement pas une bonne idée)
				
				if(getSimilarityValue(&jingleHist->subdivision, &fileHist->subdivision, jingle.tailleFenetre) > SIMLIARITY_MAX_VALUE){		// Si le truc est trop différent, on dit que c'est pas bon
					jingleEstComprisDansLeFichier = 0;
					break;
				}else{
					jingleHist = jingleHist->nextFenetre;
					fileHist = fileHist->nextFenetre;
				}
			}

			if(jingleEstComprisDansLeFichier == 1 && fileHist != NULL){	//Si ici on s'est arrété parce que le jingle est fini, et pas parce que y'a eut une différence ou la fin du fichier audio
				nameToSeconds = (int)(fileHist->name *jingle.tailleFenetre* SECONDE_PAR_VALEUR);
				//printf("On est sur le : %d\n", fileHist->name * tailleFenetre * SECONDE_PAR_VALEUR);
				listeDesTimingsDesJingle = emPILEVal(listeDesTimingsDesJingle, nameToSeconds);	//C'est que le jingle est bien compris dedans
			}
			
			jingleHist = jingle.data;	//remise a zero de l'index du jingle
		}
		if(fileHist != NULL)
			fileHist = fileHist->nextFenetre;
	}

	return listeDesTimingsDesJingle;
}