#ifndef AUDIO_H
#define AUDIO_H

typedef struct{
	int size;
	char* data;
}DescripteurSon;

DescripteurSon creerDescripteurSon(char* fileAddress);
float comparerDescripteurSon(DescripteurSon audio1, DescripteurSon audio2);

#endif