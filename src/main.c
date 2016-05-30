/*
 * Main
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#include "Lecture_Ecriture_B.h"
#include "package_merge.h"
#include "anlyseTexte.h"
#include "huffman_liste.h"
#include "huffman_part2.h"

int main(int argc, char **argv)
{
	int T[N];
	
	int i;
	pArbre res = huffman("../fichier_test/test3.txt");
	printf("\nJ'ai construit l'arbre de Huffman\n");
	afficher_Arbre(res);
	for (i=0;i<N;i++){
		T[i]=0;
	}
	profondeur(res,T,0);
	printf(" j'ai reussi a calculer les profondeurs\n");
	//recuperation du nombre de symbole 
	
	char nb_symbole=0;
	for (i=0;i<N;i++){ if (T[i]!=0) nb_symbole++;}
	
	pArbre A=construction_arbre_canonique(T);
	afficher_Arbre(A);
	
	//generation_description_arbre(A,T2);
	FILE *F1= ouvertureFichierLecture("../fichier_test/test3.txt");
	FILE *F2 = ouvertureFichierEcriture ("../fichier_test/code.txt");
	
	//ecriture du nombre de symbole 
	putByte(F2,nb_symbole);
	printf("\nle nombre de symbole est : %d\n",nb_symbole);
	
	codage(F1,F2,A,256);
	
	fermetureFichier(F1);
	fermetureFichier(F2);
	
	//decodage
	FILE *F3= ouvertureFichierLecture("../fichier_test/code.txt");
	FILE *F4 = ouvertureFichierEcriture ("../fichier_test/decodage.txt");
	printf("\n\n Decodage:\n");
	decodage(F3,F4);
	printf("Fin du decodage\n");
	fermetureFichier(F3);
	fermetureFichier(F4);
	
	return 0;
}
/* huffman_liste
int main(int argc, char **argv)
{int N=256;
	//huffman("chemin");
	pArbre res = huffman("chemin");
	afficher_Arbre(res); printf("je suis la \n");
	int T[256];
	int i; 
	for (i=0;i<N;i++){
		T[i]=0;
	}
	profondeur(res,T,0);printf(" je suis la bis\n");
	afficherT(T);
	
	pArbre res2 = construction_arbre_canonique(T);printf ("je suis sortie \n");
	afficher_Arbre(res2);
	
	return 0;
}
*/
