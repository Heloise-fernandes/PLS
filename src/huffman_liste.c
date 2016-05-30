/*
 * huffman_liste.c
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "anlyseTexte.h"
#include "Lecture_Ecriture_B.h"
#include "arbre.h"
//~ 
//~ void afficher_tableau_poids_symbole(int* symb ){
	//~ //on affiche les 256 cases du tableau du poids des symbole ;
	//~ int i = 0 ;
	//~ for ( i = 0 ; i < NMAX  /* nom de cst a changer ? */ ; i++ ){
		//~ if ( (i>=65 && i<=90) || (i>=97 && i<=122) || (i>=48 && i<=57) ){
			//~ printf("(%c,%d)\n",i,symb[i]);
		//~ }else{
			//~ printf("(%d,%d)\n",i,symb[i]);
		//~ }	
	//~ }
//~ }

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
 * Return
 *     pArbre : un arbre de huffman  */
 
pArbre huffman(char* chemin)
{
	int* tableau = malloc(sizeof(int)*N);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	
	pointeurConstruction = pointeurListe;
	pArbre a,b,c;
	pl pa,pb;
	FILE* fichier = ouvertureFichierLecture(chemin);
	printf("je suis dans huffman et j'ai ouvert le fichier \n");
	//Remplir le tableau
	remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	//afficher_tableau_poids_symbole(tableau);
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
	//fprintf(stderr," apres construction\n");
	//Trie et affichage de la liste

	
	//Trie et affichage de la liste
	printf("Taille de la liste avant trie : %d\n", tailleListePL(pointeurListe));
	
	pl trie = trier_Liste(pointeurListe);
	//afficherListe(trie);
	
	afficherListe(trie);
	
	//on enleve les 0 du debut de la liste
	
	//while(trie->poids==0 && trie->next !=NULL ){
		// trie = getElmt(trie,1) ;//marche mais pas super efficace 
	//}
	//trie = getElmt(trie,1);


	int taille = tailleListePL(pointeurListe);
	int nb_Element = nb_element_nul(tableau);
	if(taille == nb_Element){printf (" le fichier est vide \n");return NULL;}
	
	trie=getElmt(trie,nb_Element);
	printf("Taille de la liste après réduction : %d, taille 0 : %d\n", tailleListePL(trie),nb_Element);

	
	//afficherListe(trie);
	//on recupere les deux arbre des plus petit
	fprintf(stderr," apres tri \n");
	
	while(tailleListePL(trie) != 1 )
	{
		//printf("============================>\n");
		//printf("debut while\n");
		 pa = (getElmt(trie,0));
		//afficher_Arbre2(a);
		//printf(" a -> dispo%d",a->dispo);
		 pb = (getElmt(trie,1));
		
		 a = pa->A;
		//afficher_Arbre2(b);
		//printf(" b -> dispo%d",b->dispo);
		/*if (pb == NULL)
		{
			//printf("sortie");

			printf("Sortie a = %d\n", (a==NULL));
			return a;
		}*/
		//printf("Après sortie\n");
		b = pb->A;
		//printf(" a -> dispo%d,  b -> dispo%d\n",a->dispo,b->dispo);
		c = fusion(a,b);
		//printf("Après fusion\n");

		//afficher_Arbre2(c);
		
		//fprintf(stderr," si NULL la lista na que deux elem ? %p\n",(trie->next)->next);
	
		
		//printf(" c -> dispo%d",c->dispo);
		//printf("poids cumul = %d\n",c->dispo);

		
		
		//printf("avant insertion");
		trie = insertElm (trie,c);	
		
		trie = getElmt(trie,2) ; //on recuprer la liste prive de ses deux premier elem
		//printf("liste apres insertiton\n");
		//printf("Taille de la liste après réduction : %d, nex null? : %d\n", tailleListePL(trie),(trie->next==NULL));
		//afficherListe(trie);
		//printf("============================>\n");

	}
	return c;
	//afficherListe(trie);
	//afficher_Arbre2(trie->A);
//return (pointeurListe);
	
	
}
/*
int main(int argc, char **argv)
{
	//int N=256;
	//huffman("chemin");
	pArbre res = huffman("../fichier_test/albatros.txt");
	afficher_Arbre2(res); printf("je suis la \n");
	//profondeur(res,?,0);
	 
	int T[N];
	int i; 
	for (i =  0 ; i < N ; i++){
		T[i]=0;
	}
	profondeur(res,T,0);printf(" je suis la bis\n");
	afficherT(T);
	
	pArbre res2 = construction_arbre_canonique(T);printf ("je suis sortie \n");
	afficher_Arbre(res2);
	
	return 0;
}
*/

	
	





