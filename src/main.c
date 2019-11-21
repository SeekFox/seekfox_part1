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

#include "../include/test.h"

int main(int argc, char * argv[]){
    startTest();

    if((argc==2) && (strcmp(argv[1],"admin")==0)){
       printf("\tInterface ADMIN\n");
    }

    printf("Hello World!\n");
    return 0;
}
