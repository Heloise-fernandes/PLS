#include "stdlib.h"
#include "stdio.h"
#define N 256
typedef struct _Arbre{
	signed char cle;
	int dispo;
	struct _Arbre *ag;
	struct _Arbre *ad;
} Arbre, *pArbre;


void generation_description_arbre_aux (pArbre A, FILE* F, int size){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// cas d'une feuille -> on ecrit dans le fichier
			putByte(F,A->cle);
			putInt (F,size);
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_description_arbre_aux(A->ag,F,size+1);
			generation_description_arbre_aux(A->ad,F,size+1);
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(0);}		
	}
	
}


void generation_description_arbre (pArbre A){
	FILE * F= OuvertureFichierEcriture ("Je sais pas ou le mettre"); //<-A CHANGER !!!
	generation_description_arbre_aux(A,F,0);
}
//PB il faudrait mettre la taille du fichier et la description de l'arbre avant !
void generation_code (pArbre A, int *t, int s){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// cas d'une feuille 
			t[A->cle]=s;
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_code(A->ag,t,(s*2));
			generation_code(A->ad,t,(s*2)+1);
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(0);}		
	}
	
}


void Transcodage (pArbre A, FILE* fLecture){
	
	 FILE * fEcriture = OuvertureFichierEcriture ("Je sais pas ou le mettre"); //<-A CHANGER !!!
	 int t[N];
	 char c;
	 generation_code(A,t,0);
	 while (getByte(fLecture,&c)==8){
		 PutInt (fEcriture, t[c]);
	 }
}


int place (pArbre A){
	int b=0;
	if (A==NULL) b=1; //arbre vide
	else if (A->ag==NULL &&A->ad==NULL) b=A->dispo;// cas d'une feuille
	else b= (place(A->ag)||place(A->ad));// cas d'un noeud
	return b;
}

int min( int  T[]){
	int i;
	int min, imin;
	imin=0;min=T[0];
	for (i=1;i<N;i++){
		if (T[i]<min&&T[i]>0) {
			min =T[i];
			imin=i;
		}
	}
	return imin;
} 


// a partir d'un tableau qui contient la longueur du code de chaque symbole on construit un arbre
pArbre construction_arbre_canonique (int * T){
	pArbre A;
	pArbre B;
	signed char i;
	int j;
	int nb_symbole=0;
	for (i=0;i<N;i++){
		if (T[i]!=0) nb_symbole++;
	}
	while (nb_symbole>0){
		i=min(T);
		B=A;
		for(j=0;j<T[j];j++){
			if (B==NULL) {
				B=malloc(sizeof (Arbre));
				B->dispo=1;
				B->ad=malloc(sizeof(Arbre));
				B->ad->dispo=1;
				B->ag=malloc(sizeof(Arbre));
				B->ag->dispo=1;
				B=B->ad;
			}
			
			else {
				if (place(B->ad)==1){
					if (B->ad==NULL){
						B->ad=malloc(sizeof(Arbre));
						B->ad->dispo=1;
					}
					B=B->ad;
				}
				else if (place (B->ag)==1){
					if (B->ad==NULL){
						B->ag=malloc(sizeof(Arbre));
						B->ag->dispo=1;
					}	
					B=B->ag;
				}
				else {
					printf(" Arbre canonique imposible a construire\n"); 
					exit(0);
				}

			}
		}
		B->cle=i;
		B->dispo=0;
		T[i]=0;
		nb_symbole--;
	}	
	return A;
}
//dit s'il reste de la place dans un arbre ou si toute les feuilles corresponde deja a un symbole

void afficher_Arbre (pArbre A){
	if (A!=NULL){
		if (A->ad==NULL&&A->ag==NULL){//cas d'une feuille
			printf("F(%c)",A->cle);
		}
		else { // cas d'un noeud
			printf("Noeud (");
			afficher_Arbre( A->ad);
			printf(", ");
			afficher_Arbre (A->ag);
			printf(") ");
		}
	}
}


int main (){
	int T[N];
	int i;
	for (i=0;i<N;i++){T[i]=0;}
	T['a']=1;
	T['b']=2;
	T['c']=3;
	T['d']=4;
	T['e']=5;
	T['f']=5;
	pArbre A=construction_arbre_canonique(T);
	afficher_Arbre(A);
	return 0;
}
