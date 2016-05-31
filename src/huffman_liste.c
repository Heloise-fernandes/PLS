/*
 * huffman_liste.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "anlyseTexte.h"
#include "Lecture_Ecriture_B.h"
#include "arbre.h"

/*Fonction  nb_element_nul
 * Paramètre :
 *     symb : un tableau d'entier
 * Return
 *     int : le nombre de case du tableau a zeros */
int nb_element_nul(int *symb){
	int i ;
	int cpt = 0 ;
	for ( i = 0 ; i < N ; i++ ){
				if(symb[i]== 0){
					cpt++;
					
				}
	} 
	return cpt;
}
//retourne le nombre d'elm de la liste -1
//0 si la liste a 1 elm
//255 si l liste a 256 elm

/*Fonction  tailleListePL
 * Paramètre :
 *     pointeurListe : un pointeur sur le premier elm d'une liste 
 * Return
 *     taille : nb d'elm de la liste -1    */
int tailleListePL(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	int taille = 0;
	while(pointeur->next!=NULL)
	{
		taille++;
		pointeur = pointeur->next;
	}
	return taille;	
}
	
/*Fonction  huffman
 * Paramètre :
 *     chemin : le chemin du fichier à lire
 * 	   tableau : le tableau du nombre d'occurences des symboles
 * Return
 *     pArbre : un arbre de huffman  */
 
pArbre huffman(char* chemin, int * tableau)
{
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	
	pointeurConstruction = pointeurListe;
	pArbre a,b,c;
	pl pa,pb;
	FILE* fichier = ouvertureFichierLecture(chemin);
	
	//Remplir le tableau
	for (i = 0 ; i < N ; i++ ){
		tableau[i] = 0 ;
	}
	int t = remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	for(i = 0; i < N-1; i++)
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
		
	pointeurConstruction->A = malloc(sizeof(Arbre));
	pointeurConstruction->A->cle = i;
	pointeurConstruction->A->dispo = tableau[i];
	pointeurConstruction->A->ag = NULL;
	pointeurConstruction->A->ad = NULL;
	pointeurConstruction->poids = tableau[i];
	
	pointeurConstruction->next = NULL;
	//Trie et affichage de la liste	
	pl trie = trier_Liste2(pointeurListe);
	
	
	
	
	//on enleve les 0 du debut de la liste
	int taille = tailleListe1(trie);
	int nb_Element = nb_element_nul(tableau)-1;
	if(taille == nb_Element){printf (" le fichier est vide \n");return NULL;}

	if(nb_Element==-1){nb_Element=0;}
	trie=getElmt(trie,nb_Element);

	while(tailleListe1(trie) != 1 )
	{
		pa = (getElmt(trie,0));
		pb = (getElmt(trie,1));
		
		a = pa->A;
		
		b = pb->A;
		
		c = fusion(a,b);
		
		trie = insertElm (trie,c);	
		
		trie = getElmt(trie,2) ; //on recuprer la liste prive de ses deux premier elem
									
	}
	return c;
	
}
