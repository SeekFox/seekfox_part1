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

/**
 * @brief 
 * 
 * @return Histogramme 
 */
Histogramme initHistogramme();

/**
 * @brief 
 * 
 * @param oldHistogram 
 * @return Histogramme 
 */
Histogramme addFenetre(Histogramme oldHistogram);

/**
 * @brief 
 * 
 * @param display 
 */
void displayFenetre(Histogramme display); //For debug reasons

/**
 * @brief 
 * 
 * @param display 
 */
void displayDescripteur(DescripteurAudio display);

/**
 * @brief 
 * 
 * @param p_file 
 * @param fileType 
 */
void resetFileCursor(FILE* p_file, int fileType);

/**
 * @brief Get the Audio File Size object
 * 
 * @param p_file 
 * @param fileType 
 * @return unsigned int 
 */
unsigned int getAudioFileSize(FILE* p_file, int fileType);

/**
 * @brief Get the Subdivision Value object
 * 
 * @param val 
 * @param nbSubdivisions 
 * @return int 
 */
int getSubdivisionValue(double val, int nbSubdivisions);

/**
 * @brief 
 * 
 * @param p_file 
 * @param tailleFenetre 
 * @param nbSubdivisions 
 * @param fileType 
 * @return DescripteurAudio 
 */
DescripteurAudio creerDescripteurAudio(FILE* p_file, int tailleFenetre, int nbSubdivisions, int fileType);

#endif