/*
 * 
 * Arbre.c
 * 
 */
#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

/*AfficherT:
 * affiche un tableau T
 */
void afficherT (int T[]){
	int i;
	for (i=0;i<N;i++){
		
		printf("_%i_",T[i]);		
	}
	printf ("\n");
}

void afficherT2 (char T[]){
	int i;
	for (i=0;i<N;i++){
		
		printf("_%d_",T[i]);		
	}
	printf ("\n");
}

/*========================================*
 *         Fonction affichage :
 * =======================================*/

void afficher_Arbre (pArbre A){
	if (A!=NULL){
		if (A->ad==NULL&&A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->cle);
		}
		else if (A->ad==NULL){//cas d'une feuille
			printf("F(%d)",A->cle);
		}
		else if (A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->cle);
		}
		else { // cas d'un noeud
			printf("Noeud (");
			afficher_Arbre( A->ag);
			printf(",");
			afficher_Arbre (A->ad);
			printf(")\n");
		}
	}
}


void affichage_liste (pl liste){
	while (liste!=NULL){
		printf("(%i) ",liste->poids);
		liste=liste->next;
	}
	printf("\n");
}
/*=================================*
 * Fonction sur les listes
 * ================================*/

pl getElmt(pl pointeur, int indice)
{
	//printf("dans getElm\n");
	if(indice == 0){return pointeur;}
	else
	{	indice = indice - 1;
		if(pointeur->next==NULL){return NULL;}
		return getElmt(pointeur->next, indice);}
}


void afficherPointeur(pl pointeurListe)
{
	printf("Element : %d, %c, nombre : %d\n",(unsigned char) pointeurListe->A->cle,(unsigned char) pointeurListe->A->cle,pointeurListe->poids);
}

void afficherListe(pl pointeurListe)
{
	pl pointeur;
	pointeur = pointeurListe;
	//printf("afficher liste \n");
	//while(pointeur!= NULL)
	while(pointeur->next != NULL)
	{
		afficherPointeur(pointeur);

		//printf("Element : %d, nombre : %d\n",(unsigned char)pointeur->A->cle,pointeur->poids);
		pointeur = pointeur-> next;
	}
	//printf("fin de afficher liste \n");
}

pl suprElmt(pl pointeur,int indice)
{
	pl pointeurC,pointeurP;
	pointeurC = getElmt(pointeur,indice);
	if(indice == 0)
	{	
		pointeur = pointeurC->next;//On change la tête de liste
	}
	else//On change les liens
	{	
		pointeurP = getElmt(pointeur,indice-1);
		pointeurP->next = pointeurC->next;
	}
	pointeurC->next = NULL;
	return pointeurC;
}

pl trier_Liste(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	
	pl pointeurSauvegarde;
	pl pointeurJ;
	int i,j;
	for(i = 1; i < N; i++)										//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt(pointeur, i);				//x = T[i]
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

/*==========================================*/


int tailleListe2(pl p){
	int taille = 0;
	while(p->next!=NULL)
	{
		taille++;
		p = p->next;
	}
	return taille;	
}

pl getElmt2(pl pointeurListe, int indice)
{
	pl pointeur = pointeurListe;
	int i;
	int taille = tailleListe2(pointeur);
	for(i = 0; i <taille;i++)
	{
		if(i == indice){break;}
		pointeur = pointeur->next;
	}
	if(i == taille){printf("Erreur d'indice");exit(0);}
	return pointeur;
}

pl suprElmt2(pl pointeur,int indice)
{
	pl pointeurC,pointeurP;
	pointeurC = getElmt2(pointeur,indice);
	if(indice == 0)
	{	
		pointeur = pointeurC->next;//On change la tête de liste
	}
	else//On change les liens
	{	
		pointeurP = getElmt2(pointeur,indice-1);
		pointeurP->next = pointeurC->next;
	}
	pointeurC->next = NULL;
	return pointeurC;
}


pl trier_Liste2(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	
	pl pointeurSauvegarde;
	pl pointeurJ;
	int taille = tailleListe2(pointeurListe);
	int i,j;
	for(i = 1; i < taille; i++)											//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt2(pointeur, i);						//x = T[i]
		j = i;															//j<-i
		pointeurJ = getElmt2(pointeur, j-1);
		while((j>0)&&(pointeurJ->poids > pointeurSauvegarde->poids))	//tantque j>0 et T[j - 1] > x
		{
			j--;
			if(j>0){pointeurJ = getElmt2(pointeur, j-1);}				//T[i]<-T[j-1]; j<-j-1
			
		}
		if(j==0)//Cas tête de liste
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



pl insertElm(pl pointeurListe, pArbre a){
	
		pl pointeurConstruction,pointeurCourant,pred;	
		pointeurConstruction =  malloc(sizeof(l));
		if ( pointeurConstruction == NULL) {
			fprintf(stderr,"pb malloc\n");
			exit(20);
		}
		pointeurCourant = pointeurListe;
		pointeurConstruction->A = a;
		//printf("dans insertion\n");
		//afficher_Arbre2(a);
		//printf(" a -> dispo%d",a->dispo);
		pointeurConstruction->poids = a->dispo;
		//printf(" poids %d",pointeurConstruction->poids);
		
		//pointeurConstruction->next = malloc(sizeof(l));
		pointeurConstruction->next = NULL ;
		
		
		//printf("dans insertion\n");
		//afficherListe(pointeurConstruction);
		
		while( (pointeurCourant->next !=NULL) && (pointeurCourant->poids< pointeurConstruction->poids)){
			pred=pointeurCourant;
			pointeurCourant = pointeurCourant->next;
				
		}
		if (pointeurCourant==pointeurListe){
				pointeurConstruction->next =pointeurCourant;
				//printf("ajout en tete");
				pointeurListe=pointeurConstruction;
			}
		else{
		//printf("dans insert \n");
		//afficherPointeur(pred);
		//afficherPointeur(pointeurCourant);
		pred->next = pointeurConstruction;
		pointeurConstruction->next =pointeurCourant;
		}
		return pointeurListe;
	}




/*=====================================*
 * Fonction sur les arbres 
 * ====================================*/

Arbre  *ajouter_noeud (Arbre *a, Arbre *n){
  if (a == NULL)
    return n ;
  else if (n->dispo < a->dispo)
	a->ag = ajouter_noeud (a->ag, n) ;
  else
	a->ad = ajouter_noeud (a->ad, n) ;
  return a ;  
}  

pArbre ajouter_dispo (pArbre a, int d){
  Arbre *n ;
  pArbre b ;
  
  n = (Arbre *) malloc (sizeof(Arbre)) ;
 
  printf("Dispo : %d\n",d);
  n->dispo = d;
   //printf(" dans ajouter dispo  n -> dispo%d",n->dispo);
  n->ag = NULL ;
  n->ad = NULL ;
  
	
	b = ajouter_noeud  (n,(Arbre *)a) ;
  //b = ajouter_noeud ((Arbre *)a, n) ;
  
  // printf(" dans ajouter dispo  b -> dispo%d",b->dispo);
  return b ;
}
pArbre fusion(pArbre a,pArbre b){
	//printf("Dans fusion\n");
	pArbre c =  malloc(sizeof(Arbre));
	//test test malloc
	//c=NULL;
	if (c == NULL) {
		fprintf(stderr,"pb malloc\n");
		exit(20);
	}
	//printf(" dans fusion a -> dispo%d \n",a->dispo);
	//printf(" dans fusion b -> dispo%d\n",b->dispo);
	c = malloc (sizeof(Arbre)) ;
	c-> cle = 0;
	c-> dispo = (a->dispo) + (b->dispo);
	//printf(" dans fusion c -> dispo%d",c->dispo);
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
	else{printf("NULL !!! ");}
}


void profondeur (pArbre A,int * T, int p){
	if (A==NULL){}
	else if ((A->ag==NULL)||(A->ad==NULL)){ T[(unsigned char) A->cle]=p;}
	else {
		profondeur(A->ad,T,(p+1));
		profondeur(A->ag,T,(p+1));}
}
