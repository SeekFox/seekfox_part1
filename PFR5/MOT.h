#ifndef MOT_H
#define MOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 1000000

typedef struct MotPourMotCle {
	int occurence;
	char* mot;
}MOT;

void Minit(MOT* m);
char* motToString(MOT m);
float comparerMots(char* m1, char* m2);
int motsIdentiques(char* m1, char* m2);
MOT remplirMot(MOT m, int occurence, char* tab);
int motEstVide(MOT m);

#endif