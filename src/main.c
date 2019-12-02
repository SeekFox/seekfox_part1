/**
 * @file main.c
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief
 * @version 0.1
 * @date 21/11/2019
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
    #include <../include/interact.h>
#endif

int main(int argc, char * argv[]){
    //Initialisation
    enum FSM state = END; //Machine a état


    //Execution
    startTest();

    if((argc==2) && (strcmp(argv[1],"admin")==0)){
       printf("\tInterface ADMIN\n");
    }

    while(state != END){
        //Menu

        //Switch case FSM
    }

    
    printf("Hello World!\n");

    return 0;
}
