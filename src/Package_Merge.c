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
	
	trier_Liste(pl pointeurListe);
}

void trier_Liste(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	
	pl pointeurSauvegarde;
	pl pointeurparcours;
	
	int i,j;
	
	for(i = 0; i < TAILLE_TAB; i++)															//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt(pointeur,null, i);									//x = T[i]
		j = i;																				//j<-i
		while((j>0)&&((getElmt(pointeur, j-1))->A->dispo > pointeurSauvegarde->A->dispo))	//tantque j>0 et T[j - 1] > x
		{
			
		}
	}
	
	
	/*  procédure tri_insertion(tableau T, entier n)
      pour i de 1 à n-1
          x ← T[i]
          j ← i
          tant que j > 0 et T[j - 1] > x
              T[j] ← T[j - 1]
              j ← j - 1
          fin tant que
          T[j] ← x
     fin pour
  fin procédure*/
	
}

pl getElmt(pl pointeur, int indice)
{
	if(indice == 0){return pointeur;}
	else{getElmt(pointeur->next, indice--);}
}

pl suprElmt(pl pointeurCourant,pl parent, int indice)
{
	if(indice == 0)
	{	if(parent!=NULL)
		{
			parent->next = pointeurCourant->next;
			pointeurCourant->next == null; 
		}
		else
		{
			parent = pointeurCourant->next;
			pointeurCourant->next = NULL;
			 }
		return pointeurCourant;
	}
	else{getElmt(pointeurCourant->next,pointeurCourant, indice--);}
}

int main(int argc, char **argv)
{
	
	return 0;
}

