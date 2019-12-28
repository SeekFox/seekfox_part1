/**
 * @file audio.h
 * @author Gael Gamba
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef AUDIO_H
#define AUDIO_H
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
	//char* fileID;
	Histogramme data;
}DescripteurAudio;

Histogramme initHistogramme();
Histogramme addFenetre(Histogramme oldHistogram);
void displayFenetre(Histogramme display); //For debug reasons
void displayDescripteur(DescripteurAudio display);
void resetFileCursor(FILE* p_file, int fileType);
unsigned int getAudioFileSize(FILE* p_file, int fileType);
int getSubdivisionValue(double val, int nbSubdivisions);
DescripteurAudio creerDescripteurAudio(FILE* p_file, int tailleFenetre, int nbSubdivisions, int fileType);

#endif