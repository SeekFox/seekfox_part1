/**
 * @file elementAudio.h
 * @author Gael Gamba
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ELEMENT_H
#define ELEMENT_H
typedef struct ELEMENT{
	int val;
}ELEMENT;

void affiche_ELEMENT(ELEMENT display);
ELEMENT saisir_ELEMENT();
ELEMENT affect_ELEMENT(int value);
int compare_ELEMENT(ELEMENT a, ELEMENT b);

#endif
