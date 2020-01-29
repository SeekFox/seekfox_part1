#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MOT.h"

int main(void){
	MOT mot_test;
	MOT mot_test2;
	char* valeur_test;
	printf("TEST MINIT\n");
	Minit(&mot_test);
	if (motEstVide)
		printf("Mot bien vide après Init\n");
	printf("TEST REMPLIR MOT\n");
	mot_test = remplirMot(mot_test, 4, "oui");
	printf("TEST MMOTOSTRING \n");
	valeur_test = motToString(mot_test);
	printf("%s\n", valeur_test);
	printf("TEST COMPARAISON MOTS\n");
	Minit(&mot_test2);
	mot_test2 = remplirMot(mot_test2, 4, "ohno");
	if (motsIdentiques(mot_test.mot, mot_test.mot))
		printf("Le meme mot est bien identique à lui meme \n");
	printf("%.2f\n", comparerMots(mot_test.mot, mot_test2.mot));
	printf("fin\n");
	return(0);
}
