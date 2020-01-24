#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"

void main(void){
	FIFO f;
	FIFO test;
	char a;
	Init_File(f);
	Init_File(test);
	if(File_estVide(f))
		printf("File 1 est bien vide apres init \n"); 
	if(File_estVide(test))
		printf("File 2 est bien vide apres init \n");
	Enfiler(&f,'z');
	if (File_estVide(f))
		printf("Probleme fonction enfiler");
	else {
		printf("File 1 n'est plus vide apres empiler \n");
		Enfiler(&f, 'a');
		Enfiler(&f, 'b');
		printf("TEST AFFICHE \n File 1 : ");
		Affiche_file(&f);
		printf("TEST DEFILE \n");
		Defiler(&f, &a);
		printf("File 1 : ");
		Affiche_file(&f);
		Enfiler(&test, 'a');
		printf("File 2 : ");
		Affiche_file(&test);
		printf("TEST FIFO_DIFF \n");
		if(FIFO_diff(&test,&f))
			printf("Les 2 FIFO sont bien differentes \n");
		Enfiler(&test, 'b');
		printf("FILE 1 : ");
		Affiche_file(&f);
		printf("FILE 2 : ");
		Affiche_file(&test);
		if (FIFO_diff(&test, &f))
			printf("Les 2 FIFO sont bien identiques \n");
	
	}
}
