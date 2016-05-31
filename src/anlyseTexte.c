/*
 * 
 * anlyseTexte.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Ecriture_B.h"
#include "anlyseTexte.h"

#define NMAX 256

void initialiser_tableau_poids_symbole(int* symb ){
	//on initialise les 256 cases du tableau du poids des symboles a 0;
	int i = 0 ;
	for ( i = 0 ; i < NMAX ; i++ ){
		symb[i]=0;
	}
}

void afficher_tableau_poids_symbole(int* symb ){
	int i = 0 ;
	for ( i = 0 ; i < NMAX; i++ ){
		if ( (i>=65 && i<=90) || (i>=97 && i<=122) || (i>=48 && i<=57) ){
			printf("(%c,%d)\n",i,symb[i]);
		}else{
			printf("(%d,%d)\n",i,symb[i]);
		}	
	}
}

int remplir_tableau_poids_symbole_et_calcul_taille(int* symb,FILE* fichier_a_compresser){
	int cpt = 0 ;//reflechier a la fonction stat -c %s nom_fichier_a_compresser
	char value =' ';
	
	while( getByte(fichier_a_compresser, &value ) == 1 ){
		symb[(unsigned char)value]++ ;
		cpt++;
	}
	
	return cpt;		
}

 int analyse_fichier_a_compresser(int* symb,FILE* fichier_a_compresser ){
	initialiser_tableau_poids_symbole( symb );
    int taille = remplir_tableau_poids_symbole_et_calcul_taille(symb,fichier_a_compresser);
    return taille;
}
