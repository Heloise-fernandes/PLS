/*
 * Lecuture_Ecriture_B.c
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Lecture_Ecriture_B.h"

#define BIT_0 1
#define BIT_1 2
#define BIT_2 4
#define BIT_3 8
#define BIT_4 16
#define BIT_5 32
#define BIT_6 64
#define BIT_7 128
#define INDICE_MAX 7

FILE* ouvertureFichierLecture(char* chemin)
{
	FILE* fichier = fopen(chemin,"rb");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en lecture %s\n", chemin); exit(0);}
	return fichier;
}

FILE* ouvertureFichierEcriture(char* chemin)
{
	FILE* fichier = fopen(chemin,"wb+");
	if(fichier==NULL){printf("Ce fichier ne peut être ouvert en écriture %s\n", chemin); exit(0);}
	return fichier;
}

void fermetureFichier(FILE* fichier)
{
	fclose(fichier);
}

/* Renvoie 0 si aucun octet lu(fin du fichier) sinon renvoie 1
 * Paramètre :
 * fichier : le fichier à lire
 * bit : le bit lu
 * */
int getByte(FILE* fichier, char *octet)
{
	int tailleLu;
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	tailleLu = fread(octet,sizeof(char),1,fichier);
	return tailleLu;
}

/* Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * */
void putByte(FILE* fichier,char octet)
{
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	fwrite(&octet,sizeof(char),1,fichier);
}


/*Renvoie un entier qui correspond à l'indice du prochain bit pouvant être écrit
 * Paramètre :
 * fichier : le fichier à modifier
 * bit : un char qui vaut 0 ou 1
 * indice : indice ou écrire le bit, il doit être compris en 0 et 7
 * */
void putBit(FILE* fichier,char bit, int *indice)
{

	char *octet = malloc(sizeof(char));
	int tailleLu;
	
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	if((bit != 1)&&(bit != 0)){printf("Ce n'est pas un bit %d\n",bit); exit(0);}
	
	tailleLu = getByte(fichier, octet);//On recupere l'octet pointé par le curseur
	
	
	unsigned char bitUnsigned = (unsigned char) bit<<(INDICE_MAX-(*indice));
	printf("Bit à écrire : %d -- Indice : %d\n", bitUnsigned, *indice);
	if ((tailleLu != 1))//On va ajouter un nouvel octet
	{
		putByte(fichier, bitUnsigned);//On ajoute l'octet
	}
	else
	{		
		fseek(fichier,-1,SEEK_CUR);	
		switch(*indice)//On ajoute le bit à l'octet
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
	if((*indice>=0)&&(*indice<7)){fseek(fichier,-1,SEEK_CUR);}
	//Si tout l'octet n'a pas été lu(le bit d'indice 7 n'as pas été lu) on repositionne le curseur sur l'octet en cours de lecture	
	*indice = ((*indice)+1)%8;
	
}

/* Renvoie un entier qui correspond a l'indice du prochain bit pouvant être lu
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire, il doit être compris en 0 et 7
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int *indice, char *bit)
{
	char *octet = malloc(sizeof(char));
	int tailleLU;
	unsigned char *bitUnsigned;
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	
	tailleLU = getByte(fichier, octet);//On recupere l'octet pointé par le curseur
	
	if(tailleLU != 1)
	{
		tailleLU = 0;
		bit = octet;
	}
	else
	{
		
		tailleLU = 1;
		switch(*indice)
		{
			case 0 : *bitUnsigned = (*octet&BIT_7); break;
			case 1 : *bitUnsigned = (*octet&BIT_6); break;
			case 2 : *bitUnsigned = (*octet&BIT_5); break;
			case 3 : *bitUnsigned = (*octet&BIT_4); break;
			case 4 : *bitUnsigned = (*octet&BIT_3); break;
			case 5 : *bitUnsigned = (*octet&BIT_2); break;
			case 6 : *bitUnsigned = (*octet&BIT_1); break;
			case 7 : *bitUnsigned = (*octet&BIT_0); break;
			default:printf("L'indice est faux!!!!!\n"); exit(0);
			
		}
		*bitUnsigned = *bitUnsigned>>(INDICE_MAX-(*indice));
		*bit = *bitUnsigned;
		printf("Bit : %d\n", *bit);
		if((*indice>=0)&&(*indice<7)){fseek(fichier,-1,SEEK_CUR);}//Si tout l'octet n'a pas été lu(le bit d'indice 7 n'as pas été lu) on repositionne le curseur sur l'octet en cours de lecture	
	}
	*indice = ((*indice)+1)%8;
	return tailleLU;
}

void putInt (FILE *F,int size, int *indice)
{
	//Supprimer 0
	int taille = sizeof(int);
	int nbBits = taille*8;
	printf("Nombre de bits : %d\n", nbBits);
	int mask, bit,i,j;
	char bitAAjouter;
	for(j=nbBits; j >= 0 ; j--)
	{
		mask = (int) pow(2,j);
		bit = (size&mask)>>j;
		printf("Indice : %d, Bits : %d\n",j, bit);
		if(bit==1){break;}
	}
	if(j+1 == 0){printf("La taille est nul\n");exit(0);}
	printf("=====>Ecriture\n");
	for(i=j;i>=0;i--)
	{
		mask = (int) pow(2,i);
		bit = (size&mask)>>i;
		printf("Indice : %d, Bits : %d\n",i, bit);
		if(bit == 1){bitAAjouter=1;}
		else{bitAAjouter=0;}
		putBit(F,bitAAjouter,indice);
	}
}

int main(int argc, char **argv)
{
	
	if(argc==3)
	{
		/*printf("======================================>Lecture d'un octet\n");
		char car = 0;
		int taille;
		FILE* fichier = ouvertureFichierLecture(argv[1]);
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//a
		fermetureFichier(fichier);
		*/
		
		/*printf("======================================>Lecture de bit\n");
		FILE* fichier = ouvertureFichierLecture(argv[1]);
		int i,taille;
		char car;
		int indice = 0;
		for(i=0; i<=7; i++)
		{
			if(i%8==0){printf("===========================================\n");}
			taille = getBit(fichier,&indice,&car);
			printf("Taille :  %d octet / Valeur : %d\n",taille,car);
			
		}
		
		printf("======================================>Lecture octet bits\n");
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);
		
		printf("===========================================\n");
		for(i=0; i<=7; i++)
		{
			indice = i%8;
			taille = getBit(fichier,&indice,&car);
			printf("Taille :  %d octet / Valeur : %d\n",taille,car);
			
		}
		fermetureFichier(fichier);*/
		
		/*printf("======================================>Ecrire un octet\n");
		FILE* fichier = ouvertureFichierEcriture(argv[2]);
		putByte(fichier,90);
		fermetureFichier(fichier);*/
		
		
		/*printf("======================================>Ecriture bits\n");
		int i;
		int indice = 0;
		FILE* fichier = ouvertureFichierEcriture(argv[2]);
		char motEcrire[] = {0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1};
		for(i=0;i<32;i++)
		{
			putBit(fichier,motEcrire[i],&indice);
			
		}
		fermetureFichier(fichier);
		*/
		
		/*
		printf("======================================>Lecture octet grace à la fonction bits\n");
		int indice = 0;
		FILE* fichier = ouvertureFichierLecture(argv[2]);
		int i,taille;
		char car;
		for(i = 0; i<=7; i++)
		{
			indice = i%8;
			taille = getBit(fichier,&indice,&car);
			if(taille!=0)
			{
				printf("Nous avons lu un bit de %d octet qui est %d\n",taille,car);
			}
			else{break;}
		}
		fermetureFichier(fichier);*/
		
		
		printf("======================================>Ecriture entier\n");
		int indice = 0;
		int i,taille;
		char car;
		
		printf("=========> ECRITURE\n");
		FILE* fichier = ouvertureFichierEcriture(argv[2]);
		putInt(fichier,128,&indice);
		fermetureFichier(fichier);
		printf("=========> LECTURE\n");
		indice =0;
		fichier = ouvertureFichierLecture(argv[2]);
		for(i = 0; i<=7; i++)
		{
			indice = i%8;
			taille = getBit(fichier,&indice,&car);
			if(taille!=0)
			{
				printf("Nous avons lu un bit de %d octet qui est %d\n",taille,((unsigned char) car));
			}
			else{break;}
		}
		fermetureFichier(fichier);
	
	}
	
	
	return 0;
}