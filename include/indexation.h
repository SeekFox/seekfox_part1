/**
 * @file indexation.h
 * @author Etienne Combelles
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef __INDEXATION__
#define __INDEXATION__

/**
 * @brief Cellule de la pile contenant un descripteur
 * 
 */
typedef struct desc {
    char * strDesc;         // Pointeur vers la chaîne de caractères représentant le descripteur
    struct desc * suivant;  // Descripteur suivant dans la pile
} DESC;

/**
 * @brief Structure contenant la pile de descripteurs
 * 
 */
typedef struct piledesc {
    DESC * premier;         // Premier descripteur de la pile
    DESC * dernier;         // Dernier descripteur de la pile
    int nbDesc;             // Nombre de descripteurs dans la pile
} PILEDESC;

/* FONCTIONS DE MANIPULATION DES STRUCTURES */

/**
 * @brief Crée une cellule descripteur vide
 * 
 * @return DESC* 
 */
DESC * initDesc ();     

/**
 * @brief Ajoute une cellule descripteur à partir de la chaîne de caractères le représentant
 * 
 * @return DESC* 
 */
DESC * creerDesc (char *);

/**
 * @brief Crée une pile de descripteurs vide
 * 
 * @return PILEDESC* 
 */
PILEDESC * creerPileDescVide ();

/**
 * @brief Ajoute un descripteur à la pile
 * 
 */
void ajouterDescPile (PILEDESC *, DESC *);

/* FONCTIONS UTILITAIRES DIVERSES */

/**
 * @brief Renvoie 1 si le fichier dont l'adresse est passée en paramètre existe et est lisible, 0 sinon
 * 
 * @param adrDoc 
 * @return int 
 */
int isFileExist(char * adrDoc);

/**
 * @brief Renvoie 0 si le fichier dont l'adresse est passée en paramètre est déjà indexé, 1 sinon
 * 
 * @return int 
 */
int dejaIndexe (char *);

/**
 * @brief Renvoie le nombre de lignes du fichier dont l'adresse est passée en paramètre
 * 
 * @return int 
 */
int nbLignesFichier (char *);

/**
 * @brief Supprime les lignes dont les numéros sont passés en paramètre de la liste des fichiers indexés
 * 
 */
void supprLignesIndex (int *);

/**
 * @brief Place le fichier adrDoc dans le repertoire base_de_documents
 * 
 * @param adrDoc 
 * @return char* 
 */
char * moveFileInBDB(char * adrDoc);

/**
 * @brief Affiche les fichiers déjà indexes
 * 
 */
void displayFichierIndexes();

/* FONCTIONS D'INDEXATION EFFECTIVE */

/**
 * @brief Fait l'indexation de tous les fichiers de la base de document et met les descripteurs dans p1, puis les adresses des fichiers dans p2
 * 
 */
void empilementDesDescripteurs (PILEDESC *, PILEDESC *);

/**
 * @brief Retire de la liste des fichiers indexés les fichiers qui ne sont plus dans la base de documents
 * 
 */
void suppressionOrphelins ();

/**
 * @brief Refait l'indexation de 0, utilisé au premier lancement ou par lancement manuel - PREMIER MODE MANUEL
 * 
 */
void indexationTotale();

/**
 * @brief Fait l'indexation d'un fichier dont l'adresse est donnée en paramètre - DEUXIEME MODE MANUEL
 * 
 */
void indexationUnique (char *);

/**
 * @brief MODE AUTOMATIQUE : si rien d'indexé, fait une indexation totale, sinon supprime les descripteurs orphelins
 * 
 */
void indexationAutomatique();

#endif