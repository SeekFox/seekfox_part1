/**
 * @file element.c
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 07/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef __ELEMENT__
    #include "../include/element.h"
#endif

typedef struct element{
    int i;
    //char c;
    struct element * next;
}element_s;


ELEMENT init_ELEMENT(){
    ELEMENT elt = (ELEMENT)malloc(sizeof(element_s));
    elt->next=NULL;
    return elt;
}

int getI(ELEMENT e){
    return e->i;
}

ELEMENT getNext(ELEMENT e){
    return e->next;
}

void setNext(ELEMENT e, ELEMENT eNext){
    e->next = init_ELEMENT();
    e->next = eNext;
}

void affiche_ELEMENT(ELEMENT elt){
    printf("%d ",elt->i);
    //printf("%c%d ",elt->c,elt->i);
}

ELEMENT saisir_ELEMENT(){
    //char * s = (char *)malloc(32*sizeof(char));
    int i;
    ELEMENT elt = init_ELEMENT();

    scanf("%d",&i);
    //scanf("%s",s);
    //printf("\t%s - %c%d\n",s,s[0],s[1]-'0');
    //elt->c=s[0];
    elt->i=i;
    //elt->i=(int)(s[1]-'0');
    

    CLEAR_STDIN

    return elt;
}

void affect_ELEMENT(ELEMENT elt, int i){
//void affect_ELEMENT(ELEMENT elt, int i, char c){
    //elt->c=c;
    elt->i=i;
}

int compare_ELEMENT(ELEMENT elt1, ELEMENT elt2){
    if(elt1->i<elt2->i){
        return -1;
    }else if(elt1->i==elt2->i){
        return 1;
    }else{
        return 0;
    }
}