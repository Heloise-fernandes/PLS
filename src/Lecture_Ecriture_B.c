/*
 * Lecture_Ecriture_B.c
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Définition das masks et de l'indice maximale
#define BIT_0 1
#define BIT_1 2
#define BIT_2 4
#define BIT_3 8
#define BIT_4 16
#define BIT_5 32
#define BIT_6 64
#define BIT_7 128

#define INDICE_MAX 7
 
 
/* Ouvre le ficher en lecture seulement
 * Paramètre : chemin du fichier à ouvrir*/
FILE* ouvertureFichierLecture(char* chemin)
{
	FILE* fichier = fopen(chemin,"rb");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en lecture %s\n", chemin); exit(0);}
	return fichier;
}

/* Ouvre le fichier en lecture et en écriture
 * Paramètre : chemin du fichier à ouvrir*/
FILE* ouvertureFichierEcriture(char* chemin)
{
	FILE* fichier = fopen(chemin,"wb+");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en écriture %s\n", chemin); exit(0);}
	return fichier;
}

/* Fermer le fichier
 * Paramètre : fichier à fermer*/
void fermetureFichier(FILE* fichier){fclose(fichier);}

/* Lire un octet,renvoie 0 si aucun octet lu(fin du fichier) sinon renvoie 1
 * Paramètre :
 * fichier : le fichier à lire
 * octet : l'octet lu
 * */
int getByte(FILE* fichier, char *octet)
{
	int tailleLu;
	unsigned char octet_unsigned;
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	tailleLu = fread(&octet_unsigned,sizeof(char),1,fichier);
	*octet=octet_unsigned;
	return tailleLu;
}


/* Ecrit un octet dans un fichier
 * Paramètre :
 * fichier : le fichier à modifier
 * octet : un char qui vaut 0 ou 1
 * */
void putByte(FILE* fichier,char octet)
{
	unsigned char octet_unsigned=(unsigned char)octet;
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	fwrite(&octet_unsigned,sizeof(char),1,fichier);
}


/* Ecrit un bit dans un octet dans un fichier selon un indice
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * indice : indice ou écrire le bit dans l'octet, il doit être compris en 0 et 7
 * */
void putBit(FILE* fichier,char bit, int *indice)
{

	char *octet = malloc(sizeof(char));
	int tailleLu;
	
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	if((bit != 1)&&(bit != 0)){printf("Ce n'est pas un bit %d\n",bit); exit(0);}
	
	tailleLu = getByte(fichier, octet);//On recupere l'octet pointé par le curseur
	
	unsigned char bitUnsigned = (unsigned char) bit<<(INDICE_MAX-(*indice));//On décalle le bit selon l'indice et on le cast en unsigned
	
	if ((tailleLu != 1))//On va ajouter un nouvel octet
	{
		printf("le bit de putBit: %d \n",bitUnsigned);
		putByte(fichier, bitUnsigned);//On ajoute l'octet
	}
	else
	{		
		fseek(fichier,-1,SEEK_CUR);	//Après lecture on retourne sur l'octet lu pour
		switch(*indice)//Ajouter le bit à l'octet
		{
			case 0 : *octet = (*octet&(~BIT_7))+bitUnsigned; break;
			case 1 : *octet = (*octet&(~BIT_6))+bitUnsigned; break;
			case 2 : *octet = (*octet&(~BIT_5))+bitUnsigned; break;
			case 3 : *octet = (*octet&(~BIT_4))+bitUnsigned; break;
			case 4 : *octet = (*octet&(~BIT_3))+bitUnsigned; break;
			case 5 : *octet = (*octet&(~BIT_2))+bitUnsigned; break;
			case 6 : *octet = (*octet&(~BIT_1))+bitUnsigned; break;
			case 7 : *octet = (*octet&(~BIT_0))+bitUnsigned; break;
			default:printf("L'indice est faux!!!!!\n"); exit(0);
		}
		
		putByte(fichier, *octet);//On ecrit l'octet avec le bit ajouté			
	}
	//Si tout l'octet n'a pas été écrit(le bit d'indice 7 n'as pas été écrit) on repositionne le curseur sur l'octet en cours de lecture	
	if((*indice>=0)&&(*indice<7)){fseek(fichier,-1,SEEK_CUR);}
	
	//On incremente l'indice
	*indice = ((*indice)+1)%8;
	
}

/* Lire un bit, renvoie 0 si aucun bit lu 1 sinon
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire dans l'octet, il doit être compris en 0 et 7
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int *indice, char *bit)
{
	char *octet = malloc(sizeof(char));
	int tailleLU;
	unsigned char *bitUnsigned = malloc(sizeof(unsigned char));
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	
	tailleLU = getByte(fichier, octet);//On recupere l'octet pointé par le curseur
	
	if(tailleLU != 1)/*Fin du fichier*/
	{
		tailleLU = 0;
		bit = octet;
	}
	else
	{	
		tailleLU = 1;
		switch(*indice)//Lecture d'un bit dans l'octet lu
		{
			case 0 :*bitUnsigned =(unsigned char) (*octet&BIT_7);break;
			case 1 : *bitUnsigned = (*octet&BIT_6); break;
			case 2 : *bitUnsigned = (*octet&BIT_5); break;
			case 3 : *bitUnsigned = (*octet&BIT_4); break;
			case 4 : *bitUnsigned = (*octet&BIT_3); break;
			case 5 : *bitUnsigned = (*octet&BIT_2); break;
			case 6 : *bitUnsigned = (*octet&BIT_1); break;
			case 7 : *bitUnsigned = (*octet&BIT_0); break;
			default:printf("L'indice est faux!!!!!\n"); exit(0);
			
		}
		
		//Cast en unsigned avant de décaller;
		*bitUnsigned = *bitUnsigned>>(INDICE_MAX-(*indice));
		*bit = *bitUnsigned;
		
		//Si tout l'octet n'a pas été lu(le bit d'indice 7 n'as pas été lu) on repositionne le curseur sur l'octet en cours de lecture	
		if((*indice>=0)&&(*indice<7)){fseek(fichier,-1,SEEK_CUR);}
	}
	//Incrémentation de l'indice
	*indice = ((*indice)+1)%8;
	
	return tailleLU;
}

/* Ecrit un entier dans un fichier en suppriment les 0 de début
 * Paramètre :
 * F : ficher à modifier
 * size : entier à écrire
 * indice : indice pour savoir ou écrire les differents bits*/
void putInt (FILE *F,int size, int *indice)
{
	int taille = sizeof(int);
	int nbBits = taille*8;
	int mask, bit,i,j;
	char bitAAjouter;
	for(j=nbBits; j >= 0 ; j--)
	{
		mask = (int) pow(2,j);
		bit = (size&mask)>>j;
		if(bit==1){break;}
	}
	if(j+1 == 0){printf("La taille est nul\n");exit(0);}
	
	for(i=j;i>=0;i--)
	{
		mask = (int) pow(2,i);
		bit = (size&mask)>>i;
	
		if(bit == 1){bitAAjouter=1;}
		else{bitAAjouter=0;}
		putBit(F,bitAAjouter,indice);
	}
}

/* Ecrit un entier selon une taille donnée
 * Paramètre :
 * F : ficher à modifier
 * size : entier à écrire
 * indice : indice pour savoir ou écrire les differents bits
 * longeur : nombre de bits à écrire*/
void putIntV2 (FILE *F,int size, int *indice, int longueur)
{
	int mask, bit,i;
	char bitAAjouter;
	for(i=longueur-1;i>=0;i--)
	{
		mask = (int) pow(2,i);
		bit = (size&mask)>>i;
		if(bit == 1){bitAAjouter=1;}
		else{bitAAjouter=0;}
		putBit(F,bitAAjouter,indice);
	}
}

/* Ecrit un entier dans un fichier
 * Pramètre :
 * F : fichier à modifier
 * taille : entier à ajouter
 * indice : indice ou écrire l'octet*/
void putTaille (FILE *F,int taille)
{
	int i;
	char c;
	int decallage = 255;
	int mask;
	for(i = sizeof(int)-1; i >=0;i--)
	{
		mask = (unsigned int) decallage<<(i*8);
		c = ( (unsigned int) taille&mask)>>(i*8);
		putByte(F,c);
	}

}



