#include <stdio.h>
#include <stdlib.h>
#include "Lecuture_Ecriture_B.c"
#include <limits.h>
//pour pouvoir utiliser nos propres fonctions : getByte et ouvertureFichierLecture
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
//(get_bytes renvoi la taille caractere suivant en int )

long int remplir_tableau_poids_symbole_et_calcul_taille(int* symb,FILE* fichier_a_compresser){
	long cpt = 0 ;//reflechr a la fonction stat -c %s nom_fichier_a_compresser
	int c = 0 ;
	char value = ' ';//atttention
	//printf("%d",getByte(fichier_a_compresser,&value ));
	while( c = getByte(fichier_a_compresser,&value ) == 1 /*( c = fgetc(fichier_a_compresser) ) != 10 */ ){//utiliser la fonction d'heloise 
		
		if ( symb[ (int) value]++ == INT_MAX){
				return -1;
		}
		cpt++;
		//printf ("caractere lu remplir tab  = %d\n ",(int)value); DEBUG
		//printf ("caractere taille mremplir tab  = %d\n ",c);     DEBUG
	}
	return cpt;		
}

//analyse
long int analyse_fichier_a_compresser(int* symb,FILE* fichier_a_compresser ){
	long int taille=0;
	initialiser_tableau_poids_symbole( symb );
	taille = remplir_tableau_poids_symbole_et_calcul_taille(symb,fichier_a_compresser );
	afficher_tableau_poids_symbole(symb );
	return taille;
}



//main pour tester 

int main (int argc , char *argv[]){

	FILE* fichier_a_compresser = NULL;	
	int symb[NMAX];
	//int c = 0 ;
	fichier_a_compresser = ouvertureFichierLecture("albatros.txt");
	printf (" taille du fichier  = %ld\n",analyse_fichier_a_compresser(symb,fichier_a_compresser));
	//reflechr a la fonction stat -c %s nom_fichier_a_compresser
	
	
	
	
	
	//printf (" taille du fichier  = %ld\n",analyse_fichier_a_compresser(symb,fichier_a_compresser));
	//afficher_tableau_poids_symbole(symb );
	

	fclose(fichier_a_compresser);
	return 0;
	}
	

