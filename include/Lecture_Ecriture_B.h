/*
 * Lecture_Ecriture_B.h
 * 
 * 
 * 
 */

/*Ouvre le ficher en lecture seulement
 * Paramètre : chemin du fichier à ouvrir*/
FILE* ouvertureFichierLecture(char* chemin);

/*Ouvre le fichier en lecture et en écriture
 * Paramètre : chemin du fichier à ouvrir*/
FILE* ouvertureFichierEcriture(char* chemin);

/*Fermer le fichier
 * Paramètre : fichier à fermer*/
void fermetureFichier(FILE* fichier);

/* Lire un octet,renvoie 0 si aucun octet lu(fin du fichier) sinon renvoie 1
 * Paramètre :
 * fichier : le fichier à lire
 * octet : l'octet lu
 * */
int getByte(FILE* fichier, char *octet);

/* Ecrit un octet dans un fichier
 * Paramètre :
 * fichier : le fichier à modifier
 * octet : un char qui vaut 0 ou 1
 * */
void putByte(FILE* fichier,char octet);

/* Ecrit un bit dans un octet dans un fichier selon un indice
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * indice : indice ou écrire le bit dans l'octet, il doit être compris en 0 et 7
 * */
void putBit(FILE* fichier,char bit, int *indice);

/* Lire un bit, renvoie 0 si aucun bit lu 1 sinon
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire dans l'octet, il doit être compris en 0 et 7
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int *indice, char *bit);

/* Ecrit un entier dans un fichier en suppriment les 0 de début
 * Paramètre :
 * F : ficher à modifier
 * size : entier à écrire
 * indice : indice pour savoir ou écrire les differents bits*/
void putInt (FILE *F,int size, int *indice);

/* Ecrit un entier dans un fichier
 * Pramètre :
 * F : fichier à modifier
 * taille : entier à ajouter*/
void putTaille (FILE *F,int taille);
