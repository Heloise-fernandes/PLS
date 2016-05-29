//huffman_liste
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



pl getElmt(pl pointeur, int indice)
{
	printf("dans getElm\n");
	if(indice == 0){return pointeur;}
	else
	{	indice = indice - 1;
		return getElmt(pointeur->next, indice);}
	return NULL;
}

void afficherListe(pl pointeurListe)
{
	pl pointeur;
	pointeur = pointeurListe;
	printf("dans afficher liste \n");
	while(pointeur->next != NULL)
	{
		printf(" pointeur NULL %p\n",NULL);
		printf(" pointeur %p\n",pointeur);
		printf(" pointeur->next %p\n",pointeur->next);
		printf("Element : %d, nombre : %d\n",(unsigned char)pointeur->A->cle,pointeur->poids);
		pointeur = pointeur-> next;
		if (pointeur==NULL){
			printf("HOHO");
		}
	}
	printf("fin de afficher liste \n");
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
			pl pointeur = pointeurCourant;
			pointeurCourant=parent;
			return pointeur;
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
Arbre  *ajouter_noeud (Arbre *a, Arbre *n){
  if (a == NULL)
    return n ;
  else if (n->dispo < a->dispo)
	a->ag = ajouter_noeud (a->ag, n) ;
  else
	a->ad = ajouter_noeud (a->ad, n) ;
  return a ;  
}  

pArbre ajouter_dispo (pArbre a, int dispo){
  Arbre *n ;
  pArbre b ;
  
  n = (Arbre *) malloc (sizeof(Arbre)) ;
 
  n->dispo = dispo;
   //printf(" dans ajouter dispo  n -> dispo%d",n->dispo);
  n->ag = NULL ;
  n->ad = NULL ;
  
	
	b = ajouter_noeud  (n,(Arbre *)a) ;
  //b = ajouter_noeud ((Arbre *)a, n) ;
  
  // printf(" dans ajouter dispo  b -> dispo%d",b->dispo);
  return b ;
}
pArbre fusion(pArbre a,pArbre b){
	printf("Dans fusion\n");
	pArbre c =  malloc(sizeof(Arbre));
	if (c == NULL) {
		fprintf(stderr,"pb malloc\n");
	}
	printf(" dans fusion a -> dispo%d",a->dispo);
	printf(" dans fusion b -> dispo%d",b->dispo);
	c=ajouter_dispo(c,(a->dispo) + (b->dispo));
	printf(" dans fusion c -> dispo%d",c->dispo);
	c->ag = a;
	c->ad = b;
	return c;

}

void afficher_Arbre2 (pArbre A){//modif pour afficher dispo
	if (A!=NULL){
		if (A->ad==NULL&&A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else if (A->ad==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else if (A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else { // cas d'un noeud
			printf("Noeud (");
			afficher_Arbre2( A->ag);
			printf(",");
			afficher_Arbre2 (A->ad);
			printf(")");
		}
	}
}

pl insertElm(pl pointeurListe, pArbre a){
	
		pl pointeurConstruction,pointeurCourant,pred;	
		pointeurConstruction =  malloc(sizeof(l));
		pointeurCourant = pointeurListe;
		pointeurConstruction->A = a;
		//printf("dans insertion\n");
		//afficher_Arbre2(a);
		//printf(" a -> dispo%d",a->dispo);
		pointeurConstruction->poids = a->dispo;
		//printf(" poids %d",pointeurConstruction->poids);
		
		//pointeurConstruction->next = malloc(sizeof(l));
		pointeurConstruction->next =NULL;
		
		
		//printf("dans insertion\n");
		//afficherListe(pointeurConstruction);
		
		while( (pointeurCourant->next !=NULL) && (pointeurCourant->poids< pointeurConstruction->poids)){
			pred=pointeurCourant;
			pointeurCourant = pointeurCourant->next;
				
		}
		if (pointeurCourant==pointeurListe){
				pointeurConstruction->next =pointeurCourant;
				printf("ajout en tete");
				pointeurListe=pointeurConstruction;
			}
		else{
		//printf("dans insert \n");
		//afficherPointeur(pred);
		//afficherPointeur(pointeurCourant);
		pred->next = pointeurConstruction;
		pointeurConstruction->next =pointeurCourant;
		}
		return pointeurListe;//?
	}








pArbre huffman(char* chemin)
{
	int* tableau = malloc(sizeof(int)*TAILLE_TAB);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	pointeurConstruction = pointeurListe;
	pArbre a,b,c;
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
	//afficherListe(trie);
	trie = getElmt(trie,1);
	//afficherListe(trie);
	
	//on enleve les 0 du debut de la liste
	
	while(trie->poids==0){
		 trie = getElmt(trie,1) ;//marche mais pas super efficace 
	}
	
	
	afficherListe(trie);
	//on recupere les deux arbre des plus petit
	
	while((trie)->next != NULL ){
		printf("debut while\n");
		 a = (getElmt(trie,0)->A);
		afficher_Arbre2(a);
		//printf(" a -> dispo%d",a->dispo);
		 b = (getElmt(trie,1)->A);
		afficher_Arbre2(b);
		//printf(" b -> dispo%d",b->dispo);
		if (b ==NULL){
			return a;
			}
		 c = fusion(a,b);
		afficher_Arbre2(c);
		
		//fprintf(stderr," si NULL la lista na que deux elem ? %p\n",(trie->next)->next);
		if((trie->next)->next == NULL){
			printf("c'est ici la sortie");
		return c;
		}
		
		//printf(" c -> dispo%d",c->dispo);
		trie = getElmt(trie,1) ; //on recuprer la liste prive de ses deux premier elem
		
		trie = getElmt(trie,1) ;
		//printf("avant insertion");
		trie = insertElm (trie,c);	
		printf("liste apres insertiton");
		afficherListe(trie);							
	}
	
	//afficherListe(trie);
	//afficher_Arbre2(trie->A);
//return (pointeurListe);
	printf ("ici?\n");
return NULL;//normalement on ne peux pas venir ici 	
	
}


int main(int argc, char **argv)
{
	//huffman("chemin");
	pArbre res = huffman("chemin");
	return 0;
}

