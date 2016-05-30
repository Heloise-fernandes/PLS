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

//affiche un tableau
void afficherT (int T[]);

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
pl suprElmt(pl pointeurCourant,pl parent, int indice);
pl trier_Liste(pl pointeurListe);

pl insertElm(pl pointeurListe, pArbre a);




/*=====================================*
 * Fonction sur les arbres 
 * ====================================*/

Arbre  *ajouter_noeud (Arbre *a, Arbre *n);

pArbre ajouter_dispo (pArbre a, int dispo);
pArbre fusion(pArbre a,pArbre b);
void profondeur (pArbre A,int * T, int p);
#endif
