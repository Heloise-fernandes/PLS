/*
 * Package_Merge.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "anlyseTexte.c"
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


void package_merge(char* chemin)
{
	int* tableau = malloc(sizeof(int)*TAILLE_TAB);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	pointeurConstruction = pointeurListe;
	FILE* fichier = ouvertureFichierLecture(chemin);
	
	//Remplir le tableau
	remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	for(i = 0; i <TAILLE_TAB; i++)
	{
		pointeurConstruction->A->cle = i;
		pointeurConstruction->A->dispo = tableau[i];
		pointeurConstruction->A->ag = NULL;
		pointeurConstruction->A->ad = NULL;
		pointeurConstruction->next = malloc(sizeof(l));
	}
}



int main(int argc, char **argv)
{
	
	return 0;
}

