#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"

typedef struct audioDesc{
	unsigned int size;
	File data;
	//TODO ajouter l'identifiant du fichier
}DescripteurAudio;



//TODO : Lire un fichier et en faire un descripteur
DescripteurAudio creerDescripteurAudio(FILE* p_file){
	DescripteurAudio newDescripteur;
	double whatsinthere = 0;
	return newDescripteur;
}

int main(){
	FILE *p_file;
	char temp[sizeof(double)];
	double whatsinthere = 0;
	p_file = fopen("../data/TEST_SON/jingle_fi.bin","rb");
	
	for (int i = 0; i < sizeof(double); ++i)
	{
		fread(&whatsinthere, sizeof(double), 1, p_file);
		printf("%lf\n", whatsinthere);
	}
	
	fclose(p_file);
	while(1);
}
//TODO : Transformer un descripteur en string

//TODO : Transformer un string en descripteur

//TODO : Comparer 2 descripteurs