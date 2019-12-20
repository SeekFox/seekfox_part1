#ifndef INDEXATION_H
#define INDEXATION_H

typedef struct desc {       // Cellule de la pile contenant un descripteur
    char * strDesc;         // Pointeur vers la chaîne de caractères représentant le descripteur
    struct desc * suivant;  // Descripteur suivant dans la pile
} DESC;

typedef struct piledesc {   // Structure contenant la pile de descripteurs
    DESC * premier;         // Premier descripteur de la pile
    DESC * dernier;         // Dernier descripteur de la pile
    int nbDesc;             // Nombre de descripteurs dans la pile
} PILEDESC;

/* FONCTIONS DE MANIPULATION DES STRUCTURES */
DESC * initDesc ();                             // Crée une cellule descripteur vide
DESC * creerDesc (char *);                      // Ajoute une cellule descripteur à partir de la chaîne de caractères le représentant
PILEDESC * creerPileDescVide ();                // Crée une pile de descripteurs vide
void ajouterDescPile (PILEDESC *, DESC *);      // Ajoute un descripteur à la pile

/* FONCTIONS UTILITAIRES DIVERSES */
char * extensionFichier (char *);               // Renvoie l'extension du fichier dont le nom a été donné en paramètre
int dejaIndexe (char *);                        // Renvoie 0 si le fichier dont l'adresse est passée en paramètre est déjà indexé, 1 sinon
void displayError (char *);                     // Ecrit le message d'erreur passé en paramètre en rouge - /!\ A virer pour l'intégration (récupéré de Clément)

/* FONCTIONS D'INDEXATION EFFECTIVE */
void empilementDesDescripteurs (PILEDESC *, PILEDESC *);                 // Fait l'indexation de tous les fichiers de la base de document et met les descripteurs dans p1, puis les adresses des fichiers dans p2
void suppressionOrphelins ();                   // Retire de la liste des fichiers indexés les fichiers qui ne sont plus dans la base de documents
void indexationTotale ();                       // Refait l'indexation de 0, utilisé au premier lancement ou par lancement manuel - PREMIER MODE MANUEL
void indexationUnique (char *);                 // Fait l'indexation d'un fichier dont l'adresse est donnée en paramètre - DEUXIEME MODE MANUEL
void indexationAutomatique ();                  // MODE AUTOMATIQUE : si rien d'indexé, fait une indexation totale, sinon supprime les descripteurs orphelins

#endif