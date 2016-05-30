/*
 * package_merge.h
 * 
 */

#define TAILLE_TAB 256

typedef struct _liste{
	int nbElmt;
	int poids;
	struct _liste *next;
	unsigned char* elmt;
} liste,*pliste;

//============================================>FONCTIONS MANIPULATION DE LISTE

/*Fonction  maximum
 * Paramètre :
 *     a,b : les entier à comparer
 * Return
 *     int : element maximum*/
int max(int a, int b);


/* Fonction qui calcul la taille d'une liste
 * Paramètre
 *     pointeurListe : la liste à traiter
 * Return 
 *     int : taille de la liste*/
int tailleListe(pliste pointeurListe);


/* Fonction qui recupère un elément d'un liste selon l'indice
 * Paramètre :
 *     pointeurListe : la liste à traiter
 *     indice : l'indice de l'élément souhaité
 * Return
 *     pliste : pointeur sur l'élément de la liste*/
pliste getElmt(pliste pointeurListe, int indice);


/* Fonction qui elève un élément d'une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter
 *     indice : l'indice de l'élément souhaité
 * Return
 *     pliste : pointeur sur l'élément de la liste*/
pliste suprElmt(pliste pointeur,int indice);


/* Fonction qui libere une liste
 * Paramètre :
 *     listeLiberer : la liste à traiter*/
void libererListe(pliste listeLiberer);


//============================================>AFFICHAGE

/* Fonction d'affichage d'un élément d'une liste
 * Paramètre :
 *     pointeur : la liste à traiter*/
void afficherPointeur(pliste pointeur);

/* Fonction d'affichage d'une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter*/
void afficherListe(pliste pointeurListe);

//============================================>TRIE

/* Fonction qui tri par insertion une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter
 * Return
 *     pliste : pointeur sur la liste trié*/
pliste trier_Liste(pliste pointeurListe);


//============================================>CONSTRUCTION LISTE

/* Fonction qui construit une liste de 256 éléments
 * Paramètre :
 *     pointeurListe : la liste à creer
 *     tableau : les valeurs à ajouter dans la liste*/
void construireListe(pliste pointeurListe, int *tableau);

/* Fonction qui construit la liste de package de l'algorithme package merge
 * Paramètre :
 *     listeSymbole : la liste à traiter
 *     tailleListeDouble : taille Maximale de la liste de package
 * Return
 *     pliste : pointeur sur la liste creer*/
pliste constructionListeDouble(pliste listeSymbole,int tailleListeDouble);


/* Fonction qui créer la liste qui correspond à l'union entre la liste d'origine et la liste de package
 * Paramètre :
 *     listeSymbole,listeDouble : les deux listes utilisé pour creer la troisième
 * Return
 *     pliste : pointeur sur la liste creer*/
pliste constructionListeFinale(pliste listeSymbole,pliste listeDouble);

/* Fonction qui retire les éléments de poids 0
 * Paramètre :
 *     trie : la liste à traiter
 * Return
 *     pliste : pointeur sur la liste reduite*/
pliste reduireListe(pliste trie);


//============================================>CALCUL ITERATION ET OCCURENCE

/* Fonction qui calcul le nombre d'occurence d'un élément dans une liste
 * Paramètre :
 *     listeOc : la liste à traiter
 *     e : element cherché
 *     t : taille de la liste
 * Return
 *     int : nombre d'occurence*/
int nombreOccurence(pliste listeOc, unsigned char e, int t);

/* Fonction qui calcul le nombre d'occurence de tout les éléments 
 * Paramètre :
 * 	   tableauOccurence : tableaux ou stocker les nombres d'occurence
 *     listeCreationArbre : la liste à traiter*/
void calculOccurence(int *tableauOccurence,pliste listeCreationArbre);

/* Fonction qui calcul Lmax
 * Paramètre :
 *     taille : nombre de symbole
 * Return
 *     int : Lmax*/
int claculIteration(int taille);

//============================================>PACKAGE-MERGE

/* Fonction package-merge
 * Paramètre :
 *     chemin : le chemin du fichier à lire*/
void package_merge(char* chemin);




