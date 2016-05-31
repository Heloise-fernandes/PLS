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
	//int* tableau = malloc(sizeof(int)*N);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	
	pointeurConstruction = pointeurListe;
	pArbre a,b,c;
	pl pa,pb;
	FILE* fichier = ouvertureFichierLecture(chemin);
	printf("je suis dans huffman et j'ai ouvert le fichier \n");
	//Remplir le tableau
	for (i = 0 ; i < N ; i++ ){
		tableau[i] = 0 ;
	}
	int t = remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	printf("La taille d'origine est de %d bits :\n",t*8);
	
	afficherT(tableau);
	printf("j'ai calculer l'occurence de chaque symbole\n");

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
	printf("Taille de la liste avant trie : %d\n", tailleListe1(pointeurListe));
	
	pl trie = trier_Liste2(pointeurListe);
	//afficherListe(trie);
	
	
	
	//on enleve les 0 du debut de la liste
	
	//while(trie->poids==0 && trie->next !=NULL ){
		// trie = getElmt(trie,1) ;//marche mais pas super efficace 
	//}
	//trie = getElmt(trie,1);


	int taille = tailleListe1(trie);
	int nb_Element = nb_element_nul(tableau)-1;
	if(taille == nb_Element){printf (" le fichier est vide \n");return NULL;}

	if(nb_Element==-1){nb_Element=0;}
	trie=getElmt(trie,nb_Element);
	//printf("Taille de la liste après réduction : %d, taille 0 : %d\n", tailleListePL(trie),nb_Element);


	
	//afficherListe(trie);
	//on recupere les deux arbre des plus petit
	fprintf(stderr," apres tri \n");

	
	while(tailleListe1(trie) != 1 )

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

	
	





