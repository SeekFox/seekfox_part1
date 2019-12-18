/**
 * @file file.c
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 28/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#ifndef __FILE_DYNAMIQUE__
    #include "../include/file.h"
#endif

#ifndef __ELEMENT__
    #include "../include/element.h"
#endif



typedef struct file{
    ELEMENT tete;    
    ELEMENT queue;
}file;


void initFile(File * f){
    (*f) = (File)malloc(sizeof(file));
    (*f)->tete = init_ELEMENT();
    (*f)->tete = NULL;
    (*f)->queue = init_ELEMENT();
    (*f)->queue = NULL;
}

void afficheFile(File f){
    ELEMENT eltP = init_ELEMENT();
    eltP = f->tete;
    printf("[ ");
    while (eltP != NULL){
        affiche_ELEMENT(eltP);
        eltP=getNext(eltP);
    }
    printf("]\n");
}

int fileIsEmpty(File f){
    return (f->queue==NULL);
}

void enFile(File * f, ELEMENT elt){   
    if(fileIsEmpty(*f)){
        (*f)->tete = elt;
    }else{
        setNext((*f)->queue,elt);
    }
    (*f)->queue = elt;
}

void deFile(File * f){
    ELEMENT eltP = (*f)->tete;
    if(!fileIsEmpty(*f)){
        (*f)->tete = getNext((*f)->tete);
    }
    free(eltP);
}

File saisirFile(){
    File f;
    initFile(&f);
    ELEMENT elt;
    int nbrASaisir;

    printf("Indiquez le nombre d'element a saisir : ");
    scanf("%d",&nbrASaisir);

    for(int i=0; i<nbrASaisir; i++){
        elt = saisir_ELEMENT();
        enFile(&f,elt);
    }
    printf("\n");

    return f;
}

int sommeFile(File f){
    int somme = 0;
    ELEMENT eltP = init_ELEMENT();
    eltP = f->tete;
    while (eltP != NULL){
        somme+=getI(eltP);
        eltP=getNext(eltP);
    }
    return somme;
}