#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"

#define WAV_OFFSET 56

typedef struct audioDesc{
	unsigned int size;
	char* data;
	char* fileID;
}DescripteurAudio;




	//////////////////////////////
	//   CREER UN DESCRIPTEUR   //
	//////////////////////////////


int getAudioFileSize(FILE* p_file, int fileType){ //Calculer la taille d'un fichier audio, /!\ change le curseur de position, possible TODO a faire
	unsigned int size;
	double placeholder; //On est pas intéressé par les valeurs, faut juste une variable pour pouvoir lire

	if(fileType == 1)	//Les .wav ont un en tete de 56 octets qui ne nous est pas utile ici
		fseek(p_file, WAV_OFFSET, SEEK_SET);
	else
		fseek(p_file, 0, SEEK_SET);

	do{
		fread(&placeholder, sizeof(double), 1, p_file);
		size++;
	}while(!feof(p_file));

	return size;
}
																						//Filetype : 2.bin, 1.wav, 0.txt
DescripteurAudio creerDescripteurAudio(FILE* p_file, int tailleFenetre, int subdivisionFenetre, int fileType){	
	
	DescripteurAudio newDescripteur;
	unsigned int fileSize;
	double newFenetre[tailleFenetre];

	if(fileType == 1)	//Les .wav ont un en tete de 56 octets qui ne nous est pas utile ici
		fseek(p_file, WAV_OFFSET, SEEK_SET);
	if(!feof(p_file)){
		for(int i = 0; i < tailleFenetre; i++){
			//newFenetre[i] = 
		}
	}

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

	printf("Taille du fichier : %i",getAudioFileSize(p_file, 2));
	fclose(p_file);
	return 0;
}
//TODO : Transformer un descripteur en string

//TODO : Transformer un string en descripteur

//TODO : Comparer 2 descripteurs