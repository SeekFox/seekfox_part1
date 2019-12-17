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




void displayMenu(int *isAdmin, enum FSM * state){
  int nextState = (*state);

  switch (*state){
  case TITLE:
    printf("\n1\\- Recherche");
    printf("\n2\\- Administration");
    printf("\n3\\- Informations");
    printf("\n4\\- Quitter Seekfox\n");

    scanf("%d",&nextState);
    CLEAR_STDIN
    (*state) = (nextState==1 ? RESEARCH : (nextState==2 ? CONNECT : (nextState==3 ? INFO : (nextState==4 ? END : TITLE))));
    break;

  case CONNECT:
    connectAdmin(isAdmin);
    (*state)=ADMIN;
    break;
  
  case ADMIN:
    printf("\nMode Admin\n");
    (*state)=TITLE;
    break;

  case RESEARCH:
    printf("\nMode Recherche\n");
    (*state)=TITLE;
    break;

  case INFO:
    displayInformations();
    (*state) = TITLE;
    break;

  default:

    break;
  }
    //Affichage du menu
  
}

void displayInformations(){
  printf("\nwww.seekfox.team\n");
    //Affichage des infos du projets (Par qui ? )
}

void displayError(char * msg){
    color("31");
    printf("[ERREUR] %s\n",msg);
    color("0");
}

void connectAdmin(int * isAdmin){
  (*isAdmin) = 1;
  char ch;
  char password[32] = ""; //Chaine du mot de passe
  char passwordGood[32]; //Bon mot de passe
  FILE * fichier = NULL;

  //RECUPERATION MOT DE PASSE ATTENDU
  fichier = fopen("data/admin.dat","r");
  if(fichier!=NULL){
    fscanf(fichier,"%s",passwordGood);
    //printf("MOT DE PASSE ATTENDU : <%s>\n",passwordGood);
    fclose(fichier);
  }else{
    displayError("Fichier de connexion admin indisponible");
  }


  printf("Veuillez entrer le mot de passe administrateur : \n");
  for(int i=0; (i<3 && strcmp(password,passwordGood));i++){
    for (;;){ //Recuperation du mot de passe 
      ch = getch();
      if(ch == '\n' || strlen(password)>31){ //Verifier que le mot de passe ne soit pas trop long OU que l'user ne presse pas le bouton entrer
        break;
      }else{
        printf("*"); //Masquage du mot de passe
        sprintf(password,"%s%c",password,ch); //Ajout du nouveau caractere dans password
      }
    }
    printf("\n");

    //Chiffrement

    //printf("\npassword : <%s>\n",password);
    sprintf(password,"%s",(char*)crypt(password,"456b7016a916a4b178dd72b947c152b7")); //Chiffrement
    //printf("password : <%s>\n",password);

    //Si le mot de passe n'est pas valide
    if(strcmp(password,passwordGood)!=0){
      memset(password,0,sizeof(password)); //Vider la zone 
      displayError("mot de passe invalide");
    }
  }

  if(strcmp(password,passwordGood)!=0){
    *isAdmin=0;
  }
  printf("\n");
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