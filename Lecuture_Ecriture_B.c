/*
 * Lecuture_Ecriture_B.c
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define BIT_0 = 1;
#define BIT_1 = 2;
#define BIT_2 = 4;
#define BIT_3 = 8;
#define BIT_4 = 16;
#define BIT_5 = 32;
#define BIT_6 = 64;
#define BIT_7 = 128;

FILE* ouvertureFichierLecture(char* chemin)
{
	FILE* fichier = fopen(chemin,"rb");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en lecture"); exit(0);}
	return fichier;
}

FILE* ouvertureFichierEcriture(char* chemin)
{
	FILE* fichier = fopen(chemin,"wb");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en écriture"); exit(0);}
	return fichier;
}

void fermetureFichier(FILE* fichier)
{
	fclose(fichier);
}

/*Renvoie un entier qui correspond à l'indice du prochain bit pouvant être écrit
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * indice : indice ou écrire le bit
 * */
int putBit(FILE* fichier,char bit, int indice)
{
	if(fichier==NULL){printf("Le fichier n'est pas ouvert"); exit(0);}
	
}

/* Renvoie un entier qui correspond a l'indice du prochain bit pouvant être lu
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int indice, char* bit)
{
	if(fichier==NULL){printf("Le fichier n'est pas ouvert"); exit(0);}
	
}

/* Renvoie un entier qui correspond a l'indice du prochain bit pouvant être lu
 * Paramètre :
 * fichier : le fichier à lire
 * bit : le bit lu
 * */
int getByte(FILE* fichier, char* bit)
{
	int tailleLu = 0;
	if(fichier==NULL){printf("Le fichier n'est pas ouvert"); exit(0);}
	tailleLu = fread(bit,sizeof(char),1,fichier);
	return tailleLu;1
}

/*Renvoie un entier qui correspond à la taille du char ou 
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * */
void putByte(FILE* fichier,char bit)
{
	if(fichier==NULL){printf("Le fichier n'est pas ouvert"); exit(0);}
	fwrite(&bit,sizeof(char),1,fichier);
}
