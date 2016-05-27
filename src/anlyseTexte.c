#include <stdio.h>
#include <stdlib.h>
#include "../include/Lecture_Ecriture_B.h"//attention
#define NMAX 256





void initialiser_tableau_poids_symbole(int* symb ){
	//on initialise les 256 cases du tableau du poids des sybole a 0;
	int i = 0 ;
	for ( i = 0 ; i < NMAX ; i++ ){
		symb[i]=0;
	}


}

void afficher_tableau_poids_symbole(int* symb ){
	//on initialise les 256 cases du tableau du poids des sybole a 0;
	int i = 0 ;
	for ( i = 0 ; i < NMAX ; i++ ){
		printf("(%c,%d)\n",i,symb[i]);
	}
}
//(get_bytes renvoi la taill caractere suivant en int )

long remplir_tableau_poids_symbole_et_calcul_taille(int* symb,FILE* fichier_a_compresser){
	long cpt = 0 ;//reflechier a la fonction stat -c %s nom_fichier_a_compresser
	//int c = 0 ;
	char value;//atttention
	while( getByte(fichier_a_compresser, &value ) == 1 ){
/* c = get_bytes(fichier_a_compresser,int* value ) == 8 */   /* fread(&c,1,1,fichier_a_compresser) != 0 */ //tant que l'on est pas a la fin du fichier //bug possible ici a verifier
		//printf ("caractere lu =%d\n ",c);
		//symb[c]++; 
		symb[(int)value]++ ;
		cpt++;
	}
	return cpt;		
}


long int analyse_fichier_a_compresser(int* symb,FILE* fichier_a_compresser ){
	
	//FILE* fichier_a_compresser = NULL;
	//long int taille_fichier_a_compresser;
	//fichier_a_compresser = ouverture_fichier_a_compresser(nom_fichier_a_compresser );
	initialiser_tableau_poids_symbole( symb );
	long int taille = remplir_tableau_poids_symbole_et_calcul_taille(symb,fichier_a_compresser);
	afficher_tableau_poids_symbole(symb);
	return taille;
	
	
	//return remplir_tableau_poids_symbole_et_calcul_taille( symb , fichier_a_compresser);
	
}

//main pour tester 




int main (int argc , char *argv[]){

	FILE* fichier_a_compresser = NULL;	
	int symb[NMAX];
	//int c = 0 ;
	//fichier_a_compresser = ouverture_fichier_a_compresser("test.txt");
	//fichier_a_compresser = fopen("test.txt","r");
	fichier_a_compresser = ouvertureFichierLecture("albatros.txt");
/*
 * 
	c = fgetc(fichier_a_compresser);
	printf ("caractere lu =%c\n ",c);
	c = fgetc(fichier_a_compresser);
	printf ("caractere lu =%c\n ",c);
	c = fgetc(fichier_a_compresser);
	printf ("caractere lu =%c\n ",c);

	*/
/*	
	long cpt = 0 ;//reflechr a la fonction stat -c %s nom_fichier_a_compresser
	//int* value;//atttention
	while( ( c = fgetc(fichier_a_compresser) ) != 10){//utiliser la fonction d'heloise 
		
*/			
/* c = get_bytes(fichier_a_compresser,int* value ) == 8 */   /* fread(&c,1,1,fichier_a_compresser) != 0 */ //tant que l'on est pas a la fin du fichier //bug possible ici a verifier
/*
		printf ("caractere lu = %d\n ",c);
		symb[c]++; 
*/
		/*symb[value]++ */

		//cpt++;
	//return cpt;		
	
	
	
	
	printf (" taille du fichier  = %ld\n",analyse_fichier_a_compresser(symb,fichier_a_compresser));
	//afficher_tableau_poids_symbole(symb );
	

	fclose(fichier_a_compresser);
	return 0;}
	

