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
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

#ifndef __INTERACT__
    #include <../include/interact.h>
#endif




void displayMenu(int *isAdmin){
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

void connectAdmin(int * isAdmin){
    char ch;
    char password[32] = ""; //Chaine du mot de passe

    printf("Veuillez entrer le mot de passe administrateur : \n");
    for (;;) {
      ch = getch();
      if(ch == '\n' || strlen(password)>31){ //Verifier que le mot de passe ne soit pas trop long OU que l'user ne presse pas le bouton entrer
        break;
      }else{
        printf("*"); //Masquage du mot de passe
        sprintf(password,"%s%c",password,ch); //Ajout du nouveau caractere dans password
      }
    }
    printf("\npassword : <%s>\n",password);
    sprintf(password,"%s",(char*)crypt(password,"456b7016a916a4b178dd72b947c152b7"));
    printf("password : <%s>\n",password);
    //TEST VALIDITE MOT DE PASSE
}








/**-------------------------------------------------------------------------------**/
int getch(){
    struct termios oldtc, newtc;
    int ch;

    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);

    return ch;
}