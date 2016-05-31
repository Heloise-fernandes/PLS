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
	printf("\n");
}
//~ 
void lancementSimple(char* chemin, char* name)
{
	int T[N];
	int nb_occurence[N];
	int i;
	int f,d;
	
	extentionDossierCalcul(chemin,&f,&d);
	
	char* format = malloc(sizeof(char)*(f+1));
	char* dossier = malloc(sizeof(char)*(d+1));
	
	extentionDossierCreation(chemin,format,dossier,&f,&d);	
	
	char fichierCode[strlen(dossier)+strlen(name)+4];
	char fichierRetour[strlen(dossier)+strlen(name)+1+strlen(format)];
	
	strcpy(fichierCode,dossier);
	strcat(fichierCode,name);
	strcat(fichierCode,"txt");
	
	strcpy(fichierRetour,dossier);
	strcat(fichierRetour,name);
	strcat(fichierRetour,".");
	strcat(fichierRetour,format);

	pArbre res = huffman(chemin,nb_occurence);
	for (i=0;i<N;i++){
		T[i]=0;
	}
	
	profondeur(res,T,0);
	char nb_symbole=0;
	for (i=0;i<N;i++){ if (T[i]!=0) nb_symbole++;}
	
	
	//calcul de la taille
	int taille=0;
	for (i=0;i<N;i++){
		taille= taille + nb_occurence[i]*T[i];
	}
	
	
	pArbre A=construction_arbre_canonique(T);
	
	FILE *F1= ouvertureFichierLecture(chemin);
	
	FILE *F2 = ouvertureFichierEcriture (fichierCode);
	
	//ecriture du nombre de symbole 
	putByte(F2,nb_symbole);
	
	
	codage(F1,F2,A,taille);
	
	fermetureFichier(F1);
	fermetureFichier(F2);
	
	//decodage
	FILE *F3= ouvertureFichierLecture(fichierCode);
	FILE *F4 = ouvertureFichierEcriture (fichierRetour);
	decodage(F3,F4);
	fermetureFichier(F3);
	fermetureFichier(F4);
	remove(fichierCode);
	return 0;

}


//~ void lancementSimple(char* chemin, char* name)
//~ {
	//~ int T[N];
	//~ int nb_occurence[N];
	//~ int i;
//~ 
	//~ pArbre res = huffman("../fichier_test/test3.txt",nb_occurence);
//~ 
	//~ afficher_Arbre2(res);
	//~ printf("\n------------------\n");
	//~ afficher_Arbre(res);
	//~ printf("\nAffichage ok\n");
	//~ for (i=0;i<N;i++){
		//~ T[i]=0;
	//~ }
	//~ printf("\nInit\n");
	//~ 
	//~ profondeur(res,T,0);
	//~ afficherT(T);
	//~ printf(" j'ai reussi a calculer les profondeurs\n");
	//~ //recuperation du nombre de symbole 
	//~ printf("\nProfondeur\n");
	//~ char nb_symbole=0;
	//~ for (i=0;i<N;i++){ if (T[i]!=0) nb_symbole++;}
	//~ 
	//~ 
	//~ //calcul de la taille
	//~ int taille=0;
	//~ printf("=================\n calcul de la taille \n affichage du nb_occurence:\n");
	//~ afficherT(nb_occurence);
	//~ printf("\nT:\n");
	//~ afficherT(T);
	//~ for (i=0;i<N;i++){
		//~ taille= taille + nb_occurence[i]*T[i];
	//~ }
	//~ printf(" la taille du fichier est :%d\n",taille);
	//~ 
	//~ 
	//~ pArbre A=construction_arbre_canonique(T);
	//~ printf("\nConstruction cano\n");
	//~ afficher_Arbre(A);
	//~ printf("\nCanonique\n");
	//~ //generation_description_arbre(A,T2);
	//~ 
	//~ FILE *F1= ouvertureFichierLecture("../fichier_test/test3.txt");
	//~ 
	//~ //FILE *F1= ouvertureFichierLecture(argv[1]);
	//~ FILE *F2 = ouvertureFichierEcriture ("../fichier_test/code.txt");
	//~ 
	//~ //ecriture du nombre de symbole 
	//~ putByte(F2,nb_symbole);
	//~ printf("\nle nombre de symbole est : %d\n",nb_symbole);
	//~ 
	//~ 
	//~ codage(F1,F2,A,taille);
	//~ 
	//~ fermetureFichier(F1);
	//~ fermetureFichier(F2);
	//~ 
	//~ //decodage
	//~ FILE *F3= ouvertureFichierLecture("../fichier_test/code.txt");
	//~ FILE *F4 = ouvertureFichierEcriture ("../fichier_test/decodage.txt");
	//~ printf("\n\n Decodage:\n");
	//~ decodage(F3,F4);
	//~ printf("Fin du decodage\n");
	//~ fermetureFichier(F3);
	//~ fermetureFichier(F4);
//~ 
//~ }


int main(int argc, char **argv)
{
	
	char* modeDEmploie = "\nNAME : Compression\n\nSYNOPSIS : \n	./compresser [OPTIONS] nomFichier \n\nDESCRIPTION : 	\n	-p\n		compression package merge sans prétraitement\n\n	-r,-m,-rm\n		compression avec prétraitement rle(r) ou mtf(m) ou rle et mtf (mr)\n\nExemple : ./compresser -p nomFichier, ./compresser -r nomFichier, ./compresser -p -m nomFichier\n\n";
	if(argc < 2)
	{
		printf("%s", modeDEmploie);
	}
	else if (argc == 3)
	{
		printf("Compression sans pretraitement avec huffman\n");
		lancementSimple(argv[1], argv[2]);
		
	}
	else if (argc < 6)
	{
		if(argc==4)
		{
			char* chemin = argv[3];
			if(strcmp("-p",argv[2])==0)
			{
				printf("Lancement  avec package merge\n");	
				
				
					
			}
			else if (strcmp("-m",argv[2])==0)
			{printf("Lancement avec prétraitement mtf \n");}
			else if (strcmp("-r",argv[2])==0)
			{printf("Lancement  avec prétraitement rle\n");}
			else if (strcmp("-mr",argv[2])==0)
			{printf("Lancement  prétraitement avec mtf et rel \n");}
			else{printf("%s",modeDEmploie);}
		}
		else
		{
			char* chemin = argv[4];
			if (strcmp("-p",argv[2])==0)
			{
				if (strcmp("-m",argv[3])==0)
				{printf("Lancement codage package merge avec prétraitement mtf\n");}
				else if (strcmp("-r",argv[3])==0)
				{printf("Lancement  codage package merge avec prétraitement rle\n");}
				else if (strcmp("-mr",argv[3])==0)
				{printf("Lancement  codage package merge avec prétraitement mtf et rel\n");}
				else{printf("%s",modeDEmploie);}
			}
			else{printf("%s",modeDEmploie);}
		}
	}
	else
	{
		printf("%s",modeDEmploie);
	}
	
	return 0;
}
