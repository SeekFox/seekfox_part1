/**
 * @file main.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Fonction Main
 * @version 0.11
 * @date 10/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef __INTERACT__
    #include "../include/interact.h"
#endif

#ifndef __CONFIG__
    #include "../include/config.h"
#endif

#ifndef __INDEXATION__
  #include "../include/indexation.h"
#endif

/**
 * @brief Variable globale config
 * 
 */
Config config;


int main(int argc, char * argv[]){
    //Initialisation
    enum FSM state = TITLE; //Machine a etat
    int isAdmin = 0;
    char file[32] = "";
    system("./bin/readRequete.sh");

    config = loadConfig();

    indexationAutomatique();
    //Execution
    printSeekFox();

    //Connexion Admin
    if((argc==2) && (strcmp(argv[1],"admin")==0)){
        connectAdmin(&isAdmin);
        state = (isAdmin==1 ? ADMIN : TITLE);
    }

    //Menu
    //Boucle sur la machinea etat
    while(state != END){
        displayMenu(&isAdmin,&state,file);
    }

    return 0;
}
