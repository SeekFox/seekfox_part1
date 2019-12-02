/**
 * @file interact.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 21/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef __INTERACT__
    #include <../include/interact.h>
#endif

void displayMenu(int isAdmin){
    //Affichage du menu
}

void displayInformations(){
    //Affichage des infos du projets (Par qui ? )
}

void displayError(char * msg){
    color("31");
    printf("[ERREUR] %s\n",msg);
    color("0");
}