/*
 * Main
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>

#include "Lecture_Ecriture_B.h"
#include "package_merge.h"
#include "anlyseTexte.h"
#include "huffman_liste.h"
#include "huffman_part2.h"
#include "RLE.h"
#include "MTF.h"
#include "pretraitement.h"

#define MODEDEMPLOIE "\nNAME : Decompression\n\nSYNOPSIS : \n	./decompresser Fichier nom extention\n\n"

void extentionDossierCalcul(char* chemin, int* exten, int* repository)
{
	int taille = strlen(chemin);
	int indice = taille - 1;
	int extention = 0;
	while(chemin[indice]!='/')
	{
			if(chemin[indice]=='.'){extention = indice;}
			indice--;
	}
	extention++;
	*repository = indice+1;
	*exten = taille - extention;
}

void extentionDossierCreation(char* chemin, char* exten, char* repository,int* e, int* r)
{
	int i;
	int taille = strlen(chemin);
	
	int extention = taille-*e;
	
	for(i = 0; i < *e; i++)
	{
		exten[i] = chemin[extention+i];
	}
	exten[i] = '\0';
	
	for(i = 0; i < *r; i++)
	{
		repository[i] = chemin[i];
	}
	repository[i] = '\0';
	printf("blopextent\n");
	printf("\n");
}
 
void decompressionSimple(char* chemin, char* name, char* extention, char * deco)
{
	int f,d;
		
	extentionDossierCalcul(chemin,&f,&d);
	
	char* format = malloc(sizeof(char)*(f+1));
	char* dossier = malloc(sizeof(char)*(d+1));
	
	extentionDossierCreation(chemin,format,dossier,&f,&d);	

	char fichierRetour[strlen(dossier)+strlen(name)+1+strlen(extention)];
	
	if (strcmp("",extention)==0)
	{
		strcpy(fichierRetour,dossier);
		strcat(fichierRetour,name);
	}
	else 
	{
		
		strcpy(fichierRetour,dossier);
		strcat(fichierRetour,name);
		strcat(fichierRetour,".");
		strcat(fichierRetour,extention);
	}

	//decodage
	printf("Après chemin retour\n");
	if (strcmp("-m",deco)==0)
	{
		printf("Lancement avec prétraitement mtf \n");
		
		FILE *F3= ouvertureFichierLecture(chemin);
		FILE *F4 = ouvertureFichierEcriture ("../bin/temp.txt");
		decodage(F3,F4);
		fermetureFichier(F3);
		fermetureFichier(F4);
		FILE* src=ouvertureFichierLecture("../bin/temp.txt");
		FILE* resultat=ouvertureFichierEcriture(fichierRetour);
		unMTF(src,resultat);
		fermetureFichier(src);
		fermetureFichier(resultat);
	}
	else if (strcmp("-r",deco)==0)
	{
		printf("Lancement  avec prétraitement rle\n");
		FILE *F3= ouvertureFichierLecture(chemin);
		FILE *F4 = ouvertureFichierEcriture ("../bin/temp.txt");
		decodage(F3,F4);
		fermetureFichier(F3);
		fermetureFichier(F4);
		FILE* src=ouvertureFichierLecture("../bin/temp.txt");
		FILE* resultat=ouvertureFichierEcriture(fichierRetour);
		unRLE(src,resultat);
		fermetureFichier(src);
		fermetureFichier(resultat);
	}
	else if (strcmp("-mr",deco)==0)
	{
		printf("Lancement  prétraitement avec mtf et rel \n");
		FILE *F3= ouvertureFichierLecture(chemin);
		FILE *F4 = ouvertureFichierEcriture ("../bin/temp.txt");
		decodage(F3,F4);
		fermetureFichier(F3);
		fermetureFichier(F4);
		FILE* src=ouvertureFichierLecture("../bin/temp.txt");
		FILE* resultat=ouvertureFichierEcriture(fichierRetour);
		decomp_MTF_RLE(src,resultat);
		fermetureFichier(src);
		fermetureFichier(resultat);
	}
	else if (strcmp("-rm",deco)==0)
	{
		printf("Lancement  prétraitement avec mtf et rel \n");
		FILE *F3= ouvertureFichierLecture(chemin);
		FILE *F4 = ouvertureFichierEcriture ("../bin/temp.txt");
		decodage(F3,F4);
		fermetureFichier(F3);
		fermetureFichier(F4);
		FILE* src=ouvertureFichierLecture("../bin/temp.txt");
		FILE* resultat=ouvertureFichierEcriture(fichierRetour);
		decomp_RLE_MTF(src,resultat);
		fermetureFichier(src);
		fermetureFichier(resultat);
	}
	else if (strcmp("",deco)==0)
	{
		FILE *F3= ouvertureFichierLecture(chemin);
		FILE *F4 = ouvertureFichierEcriture (fichierRetour);
		decodage(F3,F4);
		fermetureFichier(F3);
		fermetureFichier(F4);
	}
	else{printf("%s",MODEDEMPLOIE);}
	
}

int main(int argc, char **argv)
{
	char* modeDEmploie = "\nNAME : Decompression\n\nSYNOPSIS : \n	./decompresser Fichier nom extention\n\n";
	if(argc < 3)
	{
		printf("%s", modeDEmploie);
	}
	else if (argc == 3)
	{
		printf("Compression sans pretraitement avec huffman\n");
		decompressionSimple(argv[1], argv[2],"","");
	}
	else if (argc == 4)
	{
		printf("Compression sans pretraitement avec huffman\n");
		if (strcmp("",argv[3])==0){decompressionSimple(argv[1], argv[2],argv[3],"");}
		else{decompressionSimple(argv[2], argv[3],"",argv[1]);}
	}
	else if (argc == 5)
	{
		printf("Compression avec pretraitement avec huffman\n");
		decompressionSimple(argv[2], argv[3],argv[4],argv[1]);		
	}
	else
	{
		printf("%s",modeDEmploie);
	}
	
	return 0;
}

