/**
 * @file main.c
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.11
 * @date 10/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TEST__
    #include "../include/test.h"
#endif

#ifndef __INTERACT__
    #include "../include/interact.h"
#endif

int main(int argc, char * argv[]){
    //Initialisation
    enum FSM state = TITLE; //Machine a état
    int isAdmin = 0;
    system("./bin/readRequete.sh");
    //Execution
    startTest();

    //Connexion Admin
    if((argc==2) && (strcmp(argv[1],"admin")==0)){
        connectAdmin(&isAdmin);
        state = (isAdmin==1 ? ADMIN : TITLE);
        if(isAdmin==1) printf("\tInterface ADMIN\n");
    }

    while(state != END){
        //Menu
        displayMenu(&isAdmin,&state);
        //Switch case FSM
       // state = END;
    }

    
    printf("Hello World!\n");

    return 0;
}
