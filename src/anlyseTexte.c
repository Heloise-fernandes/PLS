/*
 * 
 * anlyseTexte.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Ecriture_B.h"

#define NMAX 256
//faire un seul fichier .h avecc les structures et constantes ? 

void initialiser_tableau_poids_symbole(int* symb ){
	//on initialise les 256 cases du tableau du poids des symboles a 0;
	int i = 0 ;
	for ( i = 0 ; i < NMAX /* nom de cst a changer ? */ ; i++ ){
		symb[i]=0;
	}
}

void afficher_tableau_poids_symbole(int* symb ){
	//on affiche les 256 cases du tableau du poids des symbole ;
	int i = 0 ;
	for ( i = 0 ; i < NMAX  /* nom de cst a changer ? */ ; i++ ){
		if ( (i>=65 && i<=90) || (i>=97 && i<=122) || (i>=48 && i<=57) ){
			printf("(%c,%d)\n",i,symb[i]);
		}else{
			printf("(%d,%d)\n",i,symb[i]);
		}	
	}
}

int remplir_tableau_poids_symbole_et_calcul_taille(int* symb,FILE* fichier_a_compresser){
	int cpt = 0 ;//reflechier a la fonction stat -c %s nom_fichier_a_compresser
	char value =' ';//atttention
	fprintf(stderr," avant getbyte \n");
	while( getByte(fichier_a_compresser, &value ) == 1 ){
		//fprintf(stderr," dans remplir tableau dans while avant incrementation du nombre d'occurence \n");
		fprintf(stderr," ( unsigned int )value = %ud\n",(unsigned char) value);
		symb[(unsigned char)value]++ ;
		//fprintf(stderr," dans remplir tableau dans while apres incrementation du nombre d'occurence \n");
		cpt++;
		//fprintf(stderr," dans remplir tableau dans while apres incrementation du compteur : cpt = %d \n",cpt);
		
	}
	
	return cpt;		
}

 int analyse_fichier_a_compresser(int* symb,FILE* fichier_a_compresser ){
	initialiser_tableau_poids_symbole( symb );
	//fprintf(stderr," apres initialiser_tableau_poids_symbole \n");
    int taille = remplir_tableau_poids_symbole_et_calcul_taille(symb,fichier_a_compresser);
    //fprintf(stderr," apres remplir_tableau_poids_symbole_et_calcul_taille \n");
	afficher_tableau_poids_symbole(symb);
	//fprintf(stderr," apres afficher_tableau_poids_symbole(symb)\n");
	return taille;
}

//main pour tester 
/*int main (int argc , char *argv[]){

	FILE* fichier_a_compresser = NULL;	
	int symb[NMAX];
	//fichier_a_compresser = ouvertureFichierLecture("../fichier_test/test@.txt");
	fichier_a_compresser = ouvertureFichierLecture("anlyseTexte");
	//fprintf(stderr," apres ouverture \n");
	printf (" taille du fichier  = %d\n",analyse_fichier_a_compresser(symb,fichier_a_compresser));
	fermetureFichier(fichier_a_compresser);
	return 0;}
	
*/
