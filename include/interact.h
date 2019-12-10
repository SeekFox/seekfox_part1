/**
 * @file interact.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 21/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __INTERACT__

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif
/* Param�tre  Couleur
    30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
    
    "1" active la haute intensit� des caract�res.
*/

/**
 * @brief Machine � etat
 * 
 */
enum FSM{
    TITLE,              //Welcome
    CONNECT,            //Connect Page
    ADMIN,              //Admin interface
    CUSTOMER,           //Customer interface
    INFO,               //Informations
    END,                //Goodbye !
}FSM;
extern enum FSM state;

/**
 * @brief Affichage du menu
 * 
 * @param isAdmin 
 */
void displayMenu(int *isAdmin);

/**
 * @brief Affichage des informations du projet
 * 
 */
void displayInformations();

/**
 * @brief Affiche un message en erreur (affichage en rouge)
 * 
 * @param msg 
 */
void displayError(char * msg);