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

/**
 * @brief Vide le buffer 
 * 
 */
#ifndef CLEAR_STDIN
	#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

/**
 * @brief Paramètre  Couleur
 * @brief 30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 * @brief "1" active la haute intensité des caractères.
 *  
*/
#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif


/**
 * @brief Machine à etat
 * 
 */
enum FSM{
    TITLE,              //Welcome
    CONNECT,            //Connect Page
    ADMIN,              //Admin interface
    RESEARCH,           //Recherche
    INFO,               //Informations
    END,                //Goodbye !
}FSM;
extern enum FSM state;

/**
 * @brief Affichage du menu
 * 
 * @param isAdmin 
 */
void displayMenu(int *isAdmin, enum FSM * state);

/**
 * @brief Affichage de menu de recherche
 * 
 */
void displayMenuResearch();

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

/**
 * @brief Interface de connexion au compte admin
 * 
 * @param isAdmin 
 */
void connectAdmin(int * isAdmin);

/**
 * @brief 
 * 
 * @return int 
 */
int getch();

/**
 * @brief Convertis une chaine de caractere de choix en int 
 * 
 * @param str 
 * @param max
 * @return int 
 */
int convertStringChoiceToInt(char * str, int max);