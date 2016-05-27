/*
 * Lecuture_Ecriture_B.c
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>

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
	FILE* fichier = fopen(chemin,"wb");
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
	int tailleLu = 0;
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
void putBit(FILE* fichier,char bit, int indice)
{
	char octet = 0;
	int tailleLU;
	
	if(fichier==NULL){printf("Le fichier n'est pas ouvert\n"); exit(0);}
	
	tailleLU = getByte(fichier, &octet);//On recupere l'octet pointé par le curseur
	if(tailleLU != 1)//Nous sommes à la a fin du fichier il faut donc ajouter un octet
	{
		putByte(fichier, bit<<(INDICE_MAX-indice));//On ajoute l'octet
	}
	else
	{
		tailleLU = 1;
		bit = bit<<(INDICE_MAX-indice);
		switch(indice)//On ajoute e bit à l'octet
		{
			case 0 : octet = (octet&(~BIT_7))&bit; break;
			case 1 : octet = (octet&(~BIT_6))&bit; break;
			case 2 : octet = (octet&(~BIT_5))&bit; break;
			case 3 : octet = (octet&(~BIT_4))&bit; break;
			case 4 : octet = (octet&(~BIT_3))&bit; break;
			case 5 : octet = (octet&(~BIT_2))&bit; break;
			case 6 : octet = (octet&(~BIT_1))&bit; break;
			case 7 : octet = (octet&(~BIT_0))&bit; break;
			default:printf("L'indice est faux!!!!!\n"); exit(0);
		}
		putByte(fichier, octet);//On ecrit l'octet avec le bit ajouté		
		if((indice>=0)&&(indice<7)){fseek(fichier,-1,SEEK_CUR);}//Si tout l'octet n'a pas été lu(le bit d'indice 7 n'as pas été lu) on repositionne le curseur sur l'octet en cours de lecture	
	}
	
}

/* Renvoie un entier qui correspond a l'indice du prochain bit pouvant être lu
 * Paramètre :
 * fichier : le fichier à lire
 * indice : bit à lire, il doit être compris en 0 et 7
 * bit : le bit lu
 * */
int getBit(FILE* fichier, int indice, char *bit)
{
<<<<<<< HEAD:Lecuture_Ecriture_B.c
	char *octet = NULL;//initialisation ?
=======
	char *octet=NULL;
>>>>>>> 055453835b872dc5b87902e2758ef2ccc02a231a:pretraitement/Lecture_Ecriture_B.c
	int tailleLU;
	
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
		switch(indice)
		{
			case 0 : *bit = (*octet&BIT_7); break;
			case 1 : *bit = (*octet&BIT_6); break;
			case 2 : *bit = (*octet&BIT_5); break;
			case 3 : *bit = (*octet&BIT_4); break;
			case 4 : *bit = (*octet&BIT_3); break;
			case 5 : *bit = (*octet&BIT_2); break;
			case 6 : *bit = (*octet&BIT_1); break;
			case 7 : *bit = (*octet&BIT_0); break;
			default:printf("L'indice est faux!!!!!\n"); exit(0);
		}
		*bit = *bit>>(INDICE_MAX-indice);
		if((indice>=0)&&(indice<7)){fseek(fichier,-1,SEEK_CUR);}//Si tout l'octet n'a pas été lu(le bit d'indice 7 n'as pas été lu) on repositionne le curseur sur l'octet en cours de lecture	
	}
	return tailleLU;
}
<<<<<<< HEAD:Lecuture_Ecriture_B.c

/*
int main(int argc, char **argv)
{
	
	if(argc==2)
	{
		char car;
		int taille;
		int i;
		FILE* fichier = ouvertureFichierLecture(argv[1]);
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//a
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//2
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//5
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//b
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//\n
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d\n",taille);//rien
		fermetureFichier(fichier);
		
		fichier = ouvertureFichierLecture(argv[1]);
		for(i=0; i<=7; i++)
		{
			taille = getBit(fichier,i,&car);
			printf("Nous avons lu un bit de %d octet qui est %d\n",taille,car);//a
		}
		taille = getByte(fichier,&car);
		printf("Nous avons lu un caractère de %d octet qui est %d\n",taille,car);//\n
		
		
		
		
	}
	
	
	return 0;
}
 */
=======
>>>>>>> 055453835b872dc5b87902e2758ef2ccc02a231a:pretraitement/Lecture_Ecriture_B.c
