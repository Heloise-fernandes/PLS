/*
 * package_merge.c
 * 
 */

#include "../include/package_merge.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Lecture_Ecriture_B.h"


//============================================>FONCTIONS MANIPULATION DE LISTE

/*Fonction  maximum
 * Paramètre :
 *     a,b : les entier à comparer
 * Return
 *     int : element maximum*/
int max(int a, int b){ return ((a>=b)?a:b);}


/* Fonction qui calcul la taille d'une liste
 * Paramètre
 *     pointeurListe : la liste à traiter
 * Return 
 *     int : taille de la liste*/
int tailleListe(pliste pointeurListe)
{
	pliste pointeur = pointeurListe;
	int taille = 0;
	while(pointeur!=NULL)
	{
		taille++;
		pointeur = pointeur->next;
	}
	return taille;	
}


/* Fonction qui recupère un elément d'un liste selon l'indice
 * Paramètre :
 *     pointeurListe : la liste à traiter
 *     indice : l'indice de l'élément souhaité
 * Return
 *     pliste : pointeur sur l'élément de la liste*/
pliste getElmt(pliste pointeurListe, int indice)
{
	pliste pointeur = pointeurListe;
	int i;
	int taille = tailleListe(pointeur);
	for(i = 0; i <taille;i++)
	{
		if(i == indice){break;}
		pointeur = pointeur->next;
	}
	if(i == taille){printf("Erreur d'indice");exit(0);}
	return pointeur;
}


/* Fonction qui elève un élément d'une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter
 *     indice : l'indice de l'élément souhaité
 * Return
 *     pliste : pointeur sur l'élément de la liste*/
pliste suprElmt(pliste pointeur,int indice)
{
	pliste pointeurC,pointeurP;
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


/* Fonction qui libere une liste
 * Paramètre :
 *     listeLiberer : la liste à traiter*/
void libererListe(pliste listeLiberer)
{
	int taille = tailleListe(listeLiberer);
	pliste element;
	int i;
	for(i = taille-1; i >=0; i--)
	{
		element = getElmt(listeLiberer,i);
		free(element);
	}
}


//============================================>AFFICHAGE

/* Fonction d'affichage d'un élément d'une liste
 * Paramètre :
 *     pointeur : la liste à traiter*/
void afficherPointeur(pliste pointeur)
{
	int i;
	printf("Nombre éléments : %d, ",pointeur->nbElmt);
	for(i = 0; i < pointeur->nbElmt; i++)
	{
		printf("Elmt %d : %d /",i,pointeur->elmt[i]);
	}
	printf("suivant Null?  : %d ",(pointeur->next==NULL));
	printf("poids : %d\n",pointeur->poids);
}

/* Fonction d'affichage d'une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter*/
void afficherListe(pliste pointeurListe)
{
	pliste pointeur,affiche;
	int i;
	int taille = tailleListe(pointeurListe);
	pointeur = pointeurListe;
	for( i = 0; i <taille; i++)
	{
		affiche = getElmt(pointeur, i);
		afficherPointeur(affiche);
	}
}


//============================================>TRIE

/* Fonction qui tri par insertion une liste
 * Paramètre :
 *     pointeurListe : la liste à traiter
 * Return
 *     pliste : pointeur sur la liste trié*/
pliste trier_Liste(pliste pointeurListe)
{
	pliste pointeur = pointeurListe;
	
	pliste pointeurSauvegarde;
	pliste pointeurJ;
	int taille = tailleListe(pointeurListe);
	int i,j;
	for(i = 1; i < taille; i++)											//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt(pointeur, i);						//x = T[i]
		j = i;															//j<-i
		pointeurJ = getElmt(pointeur, j-1);
		while((j>0)&&(pointeurJ->poids > pointeurSauvegarde->poids))	//tantque j>0 et T[j - 1] > x
		{
			j--;
			if(j>0){pointeurJ = getElmt(pointeur, j-1);}				//T[i]<-T[j-1]; j<-j-1
			
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


//============================================>CONSTRUCTION LISTE

/* Fonction qui construit une liste de 256 éléments
 * Paramètre :
 *     pointeurListe : la liste à creer
 *     tableau : les valeurs à ajouter dans la liste*/
void construireListe(pliste pointeurListe, int *tableau)
{
	int i;
	pliste pointeurConstruction = pointeurListe;
	for(i = 0; i < TAILLE_TAB-1; i++)
	{
		pointeurConstruction->nbElmt = 1;								//Nombre d'élément dans la structure
		//Ajout des éléments dans la structures
		pointeurConstruction->elmt = (unsigned char*) malloc(sizeof(unsigned char)*pointeurConstruction->nbElmt);
		pointeurConstruction->elmt[0] = (unsigned char) i;
		pointeurConstruction->poids = tableau[i];						//Ajout du poids de l'élément
		pointeurConstruction->next = malloc(sizeof(liste));
		pointeurConstruction = pointeurConstruction->next;				//incrementer pointeur liste
	}
	//Construction du dernière élément
	pointeurConstruction->nbElmt = 1;
	pointeurConstruction->elmt = (unsigned char*) malloc(sizeof(unsigned char)*pointeurConstruction->nbElmt);
	pointeurConstruction->elmt[0] = (unsigned char) i;
	pointeurConstruction->poids = tableau[i];
	pointeurConstruction->next = NULL;
}


/* Fonction qui construit la liste de package de l'algorithme package merge
 * Paramètre :
 *     listeSymbole : la liste à traiter
 *     tailleListeDouble : taille Maximale de la liste de package
 * Return
 *     pliste : pointeur sur la liste creer*/
pliste constructionListeDouble(pliste listeSymbole,int tailleListeDouble)
{
	pliste indice,listeDouble,elmt1,elmt2;
	int i,j,k;
	int taille = tailleListe(listeSymbole);
	
	//Choix de la taille
	if(taille%2==1){taille--;}											//choix d'un taille pair car les éléments sont appairés
	if(taille/2>tailleListeDouble){taille = 2*tailleListeDouble;}		//choix de la plus petite taille
	
	indice = malloc(sizeof(liste));
	listeDouble = indice;
	for(i = 0; i <taille; i+=2)
	{
		elmt1 = getElmt(listeSymbole,i);								//Element 1
		elmt2 = getElmt(listeSymbole,i+1);								//Element 2
		
		indice->nbElmt = elmt1->nbElmt + elmt2->nbElmt;					//Nombre d'element
		
		//Ajout des éléments de Element1 et Element2 
		indice->elmt = (unsigned char*) malloc(sizeof(unsigned char)*indice->nbElmt);		
		for(j=0;j<elmt1->nbElmt;j++)
		{
			indice->elmt[j] = elmt1->elmt[j];
		}
		for(k=0;k<elmt2->nbElmt;k++)
		{
			indice->elmt[j+k] = elmt2->elmt[k];
		}
		
		indice->poids = elmt1->poids + elmt2->poids;					//poids
		
		if(i+2 == taille){indice->next = NULL;}							//Si dernière élément à ajouter dans la liste
		else{indice->next = malloc(sizeof(liste));}						//sinon
		
		indice = indice->next;											//incrementer pointeur liste
	}
	indice = NULL;
	return listeDouble;
}


/* Fonction qui créer la liste qui correspond à l'union entre la liste d'origine et la liste de package
 * Paramètre :
 *     listeSymbole,listeDouble : les deux listes utilisé pour creer la troisième
 * Return
 *     pliste : pointeur sur la liste creer*/
pliste constructionListeFinale(pliste listeSymbole,pliste listeDouble)
{
	int tailleListeSymbole = tailleListe(listeSymbole);
	int tailleListeDouble = tailleListe(listeDouble);
	int i,j;
	pliste indice,listefinal, elmt;
	
	listefinal = malloc(sizeof(liste));
	indice = listefinal;
	
	
	for(i = 0; i < tailleListeSymbole; i++)								//Ajout de la première liste
	{
		elmt = getElmt(listeSymbole,i);
		
		indice->nbElmt = elmt->nbElmt;
		
		indice->elmt = (unsigned char*) malloc(sizeof(unsigned char)*indice->nbElmt);
		indice->elmt = elmt->elmt;
		
		indice->poids = elmt->poids;
		
		indice->next = malloc(sizeof(liste));
		indice = indice->next;											//incrementer pointeur liste
	}
	for(j = 0; j < tailleListeDouble; j++)								//Ajout de la deuxième liste
	{
		elmt = getElmt(listeDouble,j);
		
		indice->nbElmt = elmt->nbElmt;
		
		indice->elmt = (unsigned char*) malloc(sizeof(unsigned char)*indice->nbElmt);
		indice->elmt = elmt->elmt;
		
		indice->poids = elmt->poids;
		
		if(j+1 == tailleListeDouble){indice->next = NULL;}				//Si dernière élément à ajouter
		else{indice->next = malloc(sizeof(liste));}						//Sinon
		
		indice = indice->next;											//incrementer pointeur liste
	}
	indice = NULL;
	
	return trier_Liste(listefinal);
}


/* Fonction qui retire les éléments de poids 0
 * Paramètre :
 *     trie : la liste à traiter
 * Return
 *     pliste : pointeur sur la liste reduite*/
pliste reduireListe(pliste trie)
{
	pliste nouveauPointeur = trie;
	if(nouveauPointeur-> poids ==0)
	{
		while((nouveauPointeur->next!=NULL)&&(nouveauPointeur->poids==0))//Tantque la poids vaut 0 et qu'il y a un élément qui suit
		{
			nouveauPointeur = nouveauPointeur->next;					//incrementer pointeur liste
		}
		if((nouveauPointeur-> poids ==0)&&(nouveauPointeur->next==NULL)){printf("Il n'y a pas de symbole dans ce fichier");exit(0);}
	}
	return nouveauPointeur;
}


//============================================>CALCUL ITERATION ET OCCURENCE

/* Fonction qui calcul le nombre d'occurence d'un élément dans une liste
 * Paramètre :
 *     listeOc : la liste à traiter
 *     e : element cherché
 *     t : taille de la liste
 * Return
 *     int : nombre d'occurence*/
int nombreOccurence(pliste listeOc, unsigned char e, int t)
{
	int occurence = 0;
	pliste element;
	int i,j;
	for(i=0; i < t; i++)
	{
		element = getElmt(listeOc,i);
		for(j=0; j < element->nbElmt; j++)
		{
			if(element->elmt[j]==e){occurence++;}
		}
	}
	return occurence;
}

/* Fonction qui calcul le nombre d'occurence de tout les éléments 
 * Paramètre :
 * 	   tableauOccurence : tableaux ou stocker les nombres d'occurence
 *     listeCreationArbre : la liste à traiter*/
void calculOccurence(int *tableauOccurence,pliste listeCreationArbre)
{
	int i;
	unsigned char element;
	int taille = tailleListe(listeCreationArbre);
	for(i = 0; i < TAILLE_TAB; i++)
	{
		element = (unsigned char) i;
		tableauOccurence[i] = nombreOccurence(listeCreationArbre, element, taille);
	}
}

/* Fonction qui calcul Lmax
 * Paramètre :
 *     taille : nombre de symbole
 * Return
 *     int : Lmax*/
int claculIteration(int taille)
{
	int nbSymbolePosible = 0;
	int Lmax = 0;
	while(nbSymbolePosible<taille)
	{
		nbSymbolePosible = (int) pow(2,Lmax);
		Lmax++;
	}
	return Lmax;
}


//============================================>PACKAGE-MERGE

/* Fonction package-merge
 * Paramètre :
 *     chemin : le chemin du fichier à lire*/
void package_merge(char* chemin)
{
	int* tableau = malloc(sizeof(int)*TAILLE_TAB);
	int i;
	//FILE* fichier = ouvertureFichierLecture(chemin);
	
	//Remplir le tableau
	//remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	//Initialisation d'un tableau
	for(i = 0; i <TAILLE_TAB; i++)
	{
		tableau[i]=0;
	}
	
	tableau[0] = 1; 
	tableau[1] = 2;
	tableau[2] = 3;
	tableau[3] = 7;
	tableau[4] = 10;
	tableau[5] = 11;
	tableau[6] = 22;
	
	int nbIteration;
	pliste listeTableau = malloc(sizeof(liste));
	//Construire la liste
	construireListe(listeTableau, tableau);
	
	//Trier la liste
	printf("================================================> LISTE TRIEE\n");
	pliste trie = trier_Liste(listeTableau);
	//afficherListe(trie);
	
	//Creer liste origine
	printf("================================================>LISTE REDUITE\n");
	pliste listeOrigine = reduireListe(trie);
	int nombreSymbole = tailleListe(listeOrigine);
	int tailleListeDouble = nombreSymbole-2;
	nbIteration = claculIteration(nombreSymbole)-1;
	//afficherListe(listeOrigine);
	
	//Creer liste association
	printf("================================================>LISTE DOUBLE - 0\n");
	pliste listeDouble = constructionListeDouble(listeOrigine,tailleListeDouble);
	//afficherListe(listeDouble);
	
	//Creation nvListe
	printf("================================================>LISTE ORIGINE + DOUBLE\n");
	pliste listeCreationArbre = constructionListeFinale(listeOrigine,listeDouble);
	//afficherListe(listeCreationArbre);
	for(i=1;i<nbIteration;i++)
	{
		printf("================================================>LISTE DOUBLE - %d\n",i);
		libererListe(listeDouble);
		listeDouble = constructionListeDouble(listeCreationArbre,tailleListeDouble);
		//afficherListe(listeDouble);
		libererListe(listeCreationArbre);
		listeCreationArbre = constructionListeFinale(listeOrigine,listeDouble);
		//afficherListe(listeCreationArbre);
	}
	libererListe(listeDouble);
	printf("================================================>OCCURENCE\n");
	//afficherListe(listeCreationArbre);
	int *tableauOccurence = malloc(sizeof(int)*TAILLE_TAB);
	calculOccurence(tableauOccurence,listeCreationArbre);
	printf("================================================>AFFICHER TABLEAUX\n");
	for(i=0; i<TAILLE_TAB; i++)
	{
		printf("Element : %d, occurence : %d\n",i,tableauOccurence[i]);
	}
	libererListe(listeCreationArbre);
}


int main(int argc, char **argv)
{
	package_merge("chemin");
	
	return 0;
}

