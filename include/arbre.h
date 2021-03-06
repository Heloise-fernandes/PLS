/*
 * 
 *Arbre.h 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef ARBRE_H
#define ARBRE_H 

#define N 256


typedef struct _Arbre{
	unsigned char cle;
	int dispo;
	struct _Arbre *ag;
	struct _Arbre *ad;
} Arbre, *pArbre;

typedef struct _l{
	pArbre A;
	int poids;
	struct _l *next;
} l,*pl;

//affiche un tableau
void afficherT (int T[]);
void afficherT2 (char T[]);
/*========================================*
 *         Fonction affichage :
 * =======================================*/

void afficher_Arbre (pArbre A);
void affichage_liste (pl liste);
/*=================================*
 * Fonction sur les listes
 * ================================*/

pl getElmt(pl pointeur, int indice);
void afficherPointeur(pl pointeurListe);
void afficherListe(pl pointeurListe);
pl suprElmt(pl pointeurCourant, int indice);
pl trier_Liste(pl pointeurListe);
pl trier_Liste2(pl pointeurListe);
pl insertElm(pl pointeurListe, pArbre a);
int tailleListe1(pl p);


/*=====================================*
 * Fonction sur les arbres 
 * ====================================*/

Arbre  *ajouter_noeud (Arbre *a, Arbre *n);
void afficher_Arbre2 (pArbre A);
pArbre ajouter_dispo (pArbre a, int dispo);
pArbre fusion(pArbre a,pArbre b);
void profondeur (pArbre A,int * T, int p);
#endif
