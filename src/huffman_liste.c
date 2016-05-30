/*
 * huffman_liste.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "anlyseTexte.h"
#include "Lecture_Ecriture_B.h"
#include "arbre.h"


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

pArbre huffman(char* chemin)
{
	int* tableau = malloc(sizeof(int)*N);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	
	pointeurConstruction = pointeurListe;
	pArbre a,b,c;
	FILE* fichier = ouvertureFichierLecture(chemin);
	printf("je suis dans huffman et j'ai ouvert le fichier \n");
	//Remplir le tableau
	remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	/*
	//Initialisation d'un tableau
	
	for(i = 0; i <N; i++)
	{
		tableau[i]=0;
	}

	//tableau[2] = 4;
	//tableau[3] = 2;
	//tableau[4] = 18;
	//tableau[5] = 7;
	//tableau[6] = 80;
	//tableau[7] = 17;
	//tableau[8] = 2;
	//tableau[9] = 32;

	tableau['A'] = 50; 
	tableau['B'] = 5;
	tableau['C'] = 25;
	tableau['D'] = 1;
	tableau['E'] = 70;
	tableau['F'] = 200;
	tableau['G'] = 80;
	tableau['H'] = 81;*/
//Création de la liste

	for(i = 0; i < N; i++)
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
	//afficherListe(trie);
	trie = getElmt(trie,1);
	//afficherListe(trie);
	
	//on enleve les 0 du debut de la liste
	
	//while(trie->poids==0 && trie->next !=NULL ){
		// trie = getElmt(trie,1) ;//marche mais pas super efficace 
	//}
	trie=getElmt(trie,nb_element_nul(tableau)-1);
	
	
	//afficherListe(trie);
	//on recupere les deux arbre des plus petit
	
	while((trie)->next != NULL ){
		//printf("debut while\n");
		 a = (getElmt(trie,0)->A);
		//afficher_Arbre2(a);
		//printf(" a -> dispo%d",a->dispo);
		 b = (getElmt(trie,1)->A);
		//afficher_Arbre2(b);
		//printf(" b -> dispo%d",b->dispo);
		if (b ==NULL){
			//printf("sortie");
			return a;
			}
		 c = fusion(a,b);
		//afficher_Arbre2(c);
		
		//fprintf(stderr," si NULL la lista na que deux elem ? %p\n",(trie->next)->next);
	
		
		//printf(" c -> dispo%d",c->dispo);
		//printf("poids cumul = %d\n",c->dispo);
		trie = getElmt(trie,1) ; //on recuprer la liste prive de ses deux premier elem
		
		trie = getElmt(trie,1) ;
		//printf("avant insertion");
		trie = insertElm (trie,c);	
		//printf("liste apres insertiton\n");
		afficherListe(trie);							
	}
	
	//afficherListe(trie);
	//afficher_Arbre2(trie->A);
//return (pointeurListe);
	printf (" le fichier est vide \n");
return NULL;// 	

	
}



	
	





