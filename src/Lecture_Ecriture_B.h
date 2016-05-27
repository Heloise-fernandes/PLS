/*
 * Lecuture_Ecriture_B.h
 * 
 * 
 * 
 */

FILE* ouvertureFichierLecture(char* chemin);

FILE* ouvertureFichierEcriture(char* chemin);

void fermetureFichier(FILE* fichier);

/* Renvoie 0 si aucun octet lu(fin du fichier) sinon renvoie 1
 * Paramètre :
 * fichier : le fichier à lire
 * bit : le bit lu
 * */
int getByte(FILE* fichier, char *octet);

/* Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * */
void putByte(FILE* fichier,char octet);

/*Renvoie un entier qui correspond à l'indice du prochain bit pouvant être écrit
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * indice : indice ou écrire le bit, il doit être compris en 0 et 7
 * */
void putBit(FILE* fichier,char bit, int *indice);

/* Renvoie un entier qui correspond a l'indice du prochain bit pouvant être lu
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire, il doit être compris en 0 et 7
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int *indice, char *bit);

void putInt (FILE *F,int size, int *indice);

