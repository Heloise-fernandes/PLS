#include "stdlib.h"
#include "stdio.h"
typedef struct Arbre{
	signed char cle;
	struct  Arbre *ag;
	struct  Arbre *ad;
} Arbre, *pArbre;


void generation_description_arbre (pArbre A, FILE* F, int size){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// cas d'une feuille -> on ecrit dans le fichier
			putByte(F,A->cle);
			putInt (F,size);
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_description_arbre(A->ag,F,size+1);
			generation_description_arbre(A->ad,F,size+1);
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(0);}		
	}
	
}

