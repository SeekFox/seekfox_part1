#define TAILLEMAXMOT 128

/**
 * @brief Structure de la liste des mots
 * 
 */
typedef struct listeMots * ListeMots;

/**
 * @brief Structure du descripteur
 * 
 */
typedef struct descripteurTexte * DescripteurTexte;

/**
 * @brief Initialise un descripteur
 * 
 * @return DescripteurTexte 
 */
DescripteurTexte initDescripteurTexte();

/**
 * @brief Crée un descripteur
 * 
 * @param file 
 * @return DescripteurTexte 
 */
DescripteurTexte lireFichierTexte(char * file);

/**
 * @brief Get the Name Descripteur Texte object
 * 
 * @param descripteur 
 * @return char* 
 */
char * getNameDescripteurTexte(DescripteurTexte descripteur);


/**
 * @brief Initialise une liste de mots
 * 
 * @return ListeMots 
 */
ListeMots initListeMots();

/**
 * @brief Supprimes les mots inutiles de la liste
 * 
 * @param liste 
 * @return ListeMots 
 */
ListeMots epurerListe(ListeMots liste);

/**
 * @brief Ajoute un nouveau mot
 * 
 * @param liste 
 * @param mot 
 * @return ListeMots 
 */
ListeMots ajoutMot(ListeMots liste, char * mot);

/**
 * @brief ajoute un mot et son nombre d'occurence
 * 
 * @param liste 
 * @param mot 
 * @param nbOccur 
 * @return ListeMots 
 */
ListeMots ajoutMotEtNbOccur(ListeMots liste, char * mot, int nbOccur);

/**
 * @brief Affiche la liste des mots
 * 
 * @param liste 
 */
void afficheListeMot(ListeMots liste);

/**
 * @brief 
 * 
 * @param descripteur 
 */
void afficheDescripteurTexte(DescripteurTexte descripteur);

/**
 * @brief Get the Nb Mots Descripteur Texte object
 * 
 * @param descripteur 
 * @return int 
 */
int getNbMotsDescripteurTexte(DescripteurTexte descripteur);

/**
 * @brief Transforme le descripteur en chaine de caractere
 * 
 * @param descripteur 
 * @return char* 
 */
char * descripteurTexteToString(DescripteurTexte descripteur);

/**
 * @brief Transforme la chaine de caractere en descripteur Texte
 * 
 * @param descripteur 
 * @return DescripteurTexte 
 */
DescripteurTexte StringTodescripteurText(char * descripteur);

/**
 * @brief compare deux descripteurs texte
 * 
 * @param desc1 
 * @param desc2 
 * @return float 
 */
float comparerDescripteurTexte(DescripteurTexte desc1, DescripteurTexte desc2);