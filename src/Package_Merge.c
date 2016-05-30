
Skip to content
This repository

    Pull requests
    Issues
    Gist

    @Heloise-fernandes

4
1

    0

Heloise-fernandes/PLS
Code
Issues 0
Pull requests 0
Wiki
Pulse
Graphs
Settings
PLS/src/Package_Merge.c
bda708e 7 hours ago
@Heloise-fernandes Heloise-fernandes Package merge tri
178 lines (147 sloc) 3.54 KB
/*
 * Package_Merge.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#include "../include/Lecture_Ecriture_B.h"

#define TAILLE_TAB 256

typedef struct _Arbre{
	signed char cle;
	int dispo;
	struct _Arbre *ag;
	struct _Arbre *ad;
} Arbre, *pArbre;

typedef struct _l{
	pArbre A;
	int poids;
	struct _l *next;
} l,*pl;

//Creer structure Liste arbre
//Creer structure arbre

//Construire arbre

//1 - faire liste arbre d'origine
//2 - faire 
//2 - faire arbre changer pointeur
pl getElmt(pl pointeur, int indice)
{
	if(indice == 0){return pointeur;}
	else
	{	indice = indice - 1;
		return getElmt(pointeur->next, indice);}
	return NULL;
}

void afficherListe(pl pointeurListe)
{
	pl pointeur,affiche;
	int i;
	pointeur = pointeurListe;
	for( i = 0; i <TAILLE_TAB; i++)
	{
		affiche = getElmt(pointeur, i);
		printf("Element : %d, nombre : %d\n",i,affiche->poids);
	}
}

void afficherPointeur(pl pointeurListe)
{
	printf("Element : %d, nombre : %d\n",(unsigned char) pointeurListe->A->cle,pointeurListe->poids);
}

pl suprElmt(pl pointeurCourant,pl parent, int indice)
{
	if(indice == 0)
	{	if(parent!=NULL)
		{
			parent->next = pointeurCourant->next;
			pointeurCourant->next = NULL; 
		}
		else
		{
			parent = pointeurCourant->next;
			pointeurCourant->next = NULL;
		}
		return pointeurCourant;
	}
	else
	{	indice = indice - 1;
		return suprElmt(pointeurCourant->next,pointeurCourant, indice);
	}
	return NULL;
}


pl trier_Liste(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	
	pl pointeurSauvegarde;
	pl pointeurJ;
	int i,j;
	for(i = 1; i < TAILLE_TAB; i++)										//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt(pointeur,NULL, i);				//x = T[i]
		j = i;															//j<-i
		pointeurJ = getElmt(pointeur, j-1);
		while((j>0)&&(pointeurJ->poids > pointeurSauvegarde->poids))	//tantque j>0 et T[j - 1] > x
		{
			j--;
			if(j>0){pointeurJ = getElmt(pointeur, j-1);}					//T[i]<-T[j-1]; j<-j-1
			
		}
		if(j==0)
		{
			pointeurSauvegarde->next = pointeur;
			pointeur = pointeurSauvegarde;
		}
		else
		{
			pointeurSauvegarde->next = pointeurJ->next;
			pointeurJ->next = pointeurSauvegarde;						//T[j] ← x
		}
											
	}
	return pointeur;
}

void package_merge(char* chemin)
{
	int* tableau = malloc(sizeof(int)*TAILLE_TAB);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	pointeurConstruction = pointeurListe;
	//FILE* fichier = ouvertureFichierLecture(chemin);
	
	//Remplir le tableau
	//remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	//Initialisation d'un tableau
	for(i = 0; i <TAILLE_TAB; i++)
	{
		tableau[i]=0;
	}
	
	tableau[0] = 50; 
	tableau[1] = 5;
	tableau[2] = 25;
	tableau[3] = 1;
	tableau[4] = 70;
	tableau[5] = 200;
	tableau[6] = 80;
	tableau[7] = 17;
	tableau[8] = 2;
	tableau[9] = 32;
	
	//Création de la liste
	for(i = 0; i < TAILLE_TAB; i++)
	{
		pointeurConstruction->A = malloc(sizeof(Arbre));
		pointeurConstruction->A->cle = i;
		pointeurConstruction->A->dispo = tableau[i];
		pointeurConstruction->A->ag = NULL;
		pointeurConstruction->A->ad = NULL;
		pointeurConstruction->poids = tableau[i];
		pointeurConstruction->next = malloc(sizeof(l));
		pointeurConstruction = pointeurConstruction->next;
	}
	
	//Trie et affichage de la liste
	pl trie = trier_Liste(pointeurListe);
	afficherListe(trie);
	
	//Pacourir 2 à 2 et ajouter les nv élements dans une tierce liste sauf si proba 0
	
	//Ajouter les élement dans la liste si non existant si hauteur !=0 et pas dans la tirece liste supression
	
	//Recommencer operation 8 fois
}


int main(int argc, char **argv)
{
	package_merge("chemin");
	
	return 0;
}

