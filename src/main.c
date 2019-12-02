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

#ifdef __TEST__
    #include "../include/test.h"
#endif

#ifdef __INTERACT__
    #include <../include/interact.h>
#endif
#include <../include/interact.h>

int main(int argc, char * argv[]){
    startTest();
    enum FSM state = TITLE;

    if((argc==2) && (strcmp(argv[1],"admin")==0)){
       printf("\tInterface ADMIN\n");
    }

    
    printf("Hello World!\n");

    return 0;
}
