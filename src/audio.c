#include <stdio.h>
#include <stdlib.h>
#include "../include/pile_dynamiqueAudio.h"

#define WAV_OFFSET 56

#define TXT_FILE 2
#define WAV_FILE 1
#define BIN_FILE 0


typedef struct Fenetre{
	unsigned int name; // de 0 a plein, correspond a sa position dans le fichier / taille fenetre
	struct Fenetre* nextFenetre;
	PILE subdivision;
}Fenetre;

typedef Fenetre* Histogramme;

typedef struct audioDesc{
	unsigned int nbFenetres;
	char* fileID;
	Histogramme data;
}DescripteurAudio;


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
	int subdivisionUnit = 2/nbSubdivisions;
	return (int)(val+1)/subdivisionUnit;
}

DescripteurAudio creerDescripteurAudio(FILE* p_file, int tailleFenetre, int nbSubdivisions, int fileType){	
	
	DescripteurAudio newDescripteur;
	
	unsigned int fileSize;
	double newFenetre[tailleFenetre];					//Nouvelle fenêtre de travail
	int sizeSubdivision = tailleFenetre/nbSubdivisions;	//Taille d'une subdivision
	double newHistogramLine[nbSubdivisions];			//Nouvelle ligne de l'histogramme final
	int subPosition = 0;

	fileSize = getAudioFileSize(p_file, fileType);
	resetFileCursor(p_file, fileType);

	do{
		for(int x = 0; x < nbSubdivisions; x++)newHistogramLine[x] = 0;	//RAZ de l'histogramme

		fread(&newFenetre, sizeof(double),tailleFenetre, p_file);
		for(int i = 0; i < tailleFenetre; i++){
			subPosition = getSubdivisionValue(newFenetre[i], nbSubdivisions);
			newHistogramLine[subPosition]++;
			//TODO Stocker ça dans la putain de structure de ces morts
		}

	}while(!feof(p_file));
	return newDescripteur;
}

int main(){
	FILE *p_file;
	char temp[sizeof(double)];
	double whatsinthere = 0;
	
	p_file = fopen("../data/TEST_SON/jingle_fi.bin","rb");
	/*while(!feof(p_file)){
		fread(&whatsinthere, sizeof(double), 1, p_file);
		printf("%lf\n", whatsinthere);
	}*/
	do{
		fread(&whatsinthere, sizeof(double),1, p_file);
		printf("%lf\n", whatsinthere);
	}while(!feof(p_file));
	//printf("Taille du fichier : %i",getAudioFileSize(p_file, 2));
	fclose(p_file);
	while(1);
	return 0;
}
//TODO : Transformer un descripteur en string

//TODO : Transformer un string en descripteur

//TODO : Comparer 2 descripteurs