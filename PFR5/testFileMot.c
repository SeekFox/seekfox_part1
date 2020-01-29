#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MOT.h"
#include "File_mots.h"

int main(void){
	FIFO_M fifo_test,fifo2;
	char* dansFifo ="";
	char* dansFifo2 = "";

	printf("Test INIT\n");
	Finit(&fifo_test);
	printf("Test estVide\n");
	if (FestVide(&fifo_test))
		printf("F bien vide après init\n");
	printf("TEST ENFILER\n");
	enfiler_M(&fifo_test, "patate");
	Affiche_file(&fifo_test);
	printf("TEST TO STRING \n");
	dansFifo = fToString(&fifo_test);
	printf("ToString : %s\n", dansFifo);
	printf("Test motExiste\n");
	if (motExiste(&fifo_test, dansFifo))
		printf("mot existe fonctionne bien \n");
	printf("Test comparer FIFO \n");
	printf("File avec elle meme \n");
	printf("%.2f %\n", comparerF(&fifo_test, &fifo_test));
	printf("File avec une qui a un mot en communn\n");
	Finit(&fifo2);
	enfiler_M(&fifo2, "patate");
	enfiler_M(&fifo2, "otrmot");
	dansFifo2 = fToString(&fifo2);
	printf("Fifo 1 : %s \n", dansFifo);
	printf("Fifo 2: %s \n", dansFifo2);
	printf("%.2f %\n", comparerF(&fifo_test, &fifo2));
	printf("fin\n");
	return(0);
}
