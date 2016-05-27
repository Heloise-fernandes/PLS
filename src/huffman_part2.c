#include "stdlib.h"
#include "stdio.h"
#include "limits.h"
#define N 256
#include "Lecuture_Ecriture_B.c"
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
	FILE * F= ouvertureFichierEcriture ("../fichier_test/description_arbre.txt"); //<-A CHANGER !!!
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
	
	 FILE * fEcriture = ouvertureFichierEcriture ("../fichier_test/code.txt"); //<-A CHANGER !!!
	 int t[N];
	 char c;
	 generation_code(A,t,0);
	 while (getByte(fLecture,&c)==8){
		 putInt (fEcriture, t[c]);
	 }
}


int place (pArbre A){
	int b=0;
	if (A==NULL) b=1; //arbre vide
	else if (A->ag==NULL &&A->ad==NULL) b=A->dispo;// cas d'une feuille
	else b= (place(A->ag)||place(A->ad));// cas d'un noeud
	return b;
}

void afficherT (int T[]){
	int i;
	for (i=0;i<N;i++){
		
		printf("%i",T[i]);		
	}
	printf ("\n");
}


int max( int  T[]){
	int i;
	int max, imax;
	imax=0;
	max=0;
	afficherT(T);
	for (i=1;i<N;i++){
		if (T[i]>max) {
			max =T[i];
			imax=i;
		}
	}
	return imax;
	
} 



int min( int  T[]){
	int i;
	int min, imin;
	imin=0;
	min=INT_MAX;
	afficherT(T);
	for (i=1;i<N;i++){
		if (T[i]<min&&T[i]>0) {
			min =T[i];
			imin=i;
		}
	}
	return imin;
	
} 


void afficher_Arbre (pArbre A){
	if (A!=NULL){
		if (A->ad==NULL&&A->ag==NULL){//cas d'une feuille
			printf("F(%c)",A->cle);
		}
		else if (A->ad==NULL){//cas d'une feuille
			printf("F(%c)",A->cle);
		}
		else if (A->ag==NULL){//cas d'une feuille
			printf("F(%c)",A->cle);
		}
		else { // cas d'un noeud
			printf("Noeud (");
			afficher_Arbre( A->ag);
			printf(",");
			afficher_Arbre (A->ad);
			printf(")");
		}
	}
}


// a partir d'un tableau qui contient la longueur du code de chaque symbole on construit un arbre

/*
pArbre construction_arbre_canonique (int * T){
	pArbre A=malloc(sizeof(Arbre));A->dispo=1;
	pArbre B;
	int i;
	int j;
	int nb_symbole=0;
	for (i=0;i<N;i++){
		if (T[i]!=0) {nb_symbole++;}
	}
	printf("nb_symbole:%i\n",nb_symbole);
	while (nb_symbole>0){
		i=min(T);
		printf("nb_symbole:%i min[T]: %i \n",nb_symbole,i);
		B=A;
		for(j=0;j<T[i];j++){
			printf("je suis dans le for \n");
			if (B==NULL) {
				B=malloc(sizeof (Arbre));
				B->dispo=1;
				B->ad=malloc(sizeof(Arbre));
				B->ad->dispo=1;
				B->ad->ad=NULL;
				B->ad->ag=NULL;
				B->ag=malloc(sizeof(Arbre));
				B->ag->dispo=1;
				B->ag->ad=NULL;
				B->ag->ag=NULL;
				B=B->ad;
			}
			
			else {
				if (place(B->ad)==1){
					if (B->ad==NULL){
						B->ad=malloc(sizeof(Arbre));
						B->ad->dispo=1;
						B->ad->ad=NULL;
						B->ad->ag=NULL;
					}
					
					B->ad->cle=i;
					B->ad->dispo=0;
					T[i]=0;
					nb_symbole--;
					afficher_Arbre(B);B=B->ad;
				}
				else if (place (B->ag)==1){
					if (B->ad==NULL){
						B->ag=malloc(sizeof(Arbre));
						B->ag->dispo=1;
						B->ag->ad=NULL;
						B->ag->ag=NULL;
					}	
					B->ag->cle=i;
					B->ag->dispo=0;
					T[i]=0;
					nb_symbole--;
					afficher_Arbre(B);
					B=B->ag;
				}
				else {
					printf(" Arbre canonique imposible a construire\n"); 
					exit(0);
				}

			}
		}
	}	
	return A;
}
*/

void affichage_liste (pl liste){
	while (liste!=NULL){
		printf("(%i) ",liste->poids);
		liste=liste->next;
	}
	printf("\n");
}


pArbre construction_arbre_canonique (int T[] ){
	pArbre A;
	pl liste;
	int i;
	int nb_symbole=0;
	for (i=0;i<N;i++){
		if (T[i]!=0) {nb_symbole++;}
	}
	printf("nb_symbole:%i\n",nb_symbole);
	//on suppose le nombre de symbole non nul
	liste= malloc(sizeof (l));//element fictif de tete
	pl liste2= liste; 
	while (nb_symbole>0){
		liste2-> next=malloc(sizeof (l));
		liste2= liste2->next;
		liste2->A= malloc (sizeof(Arbre));
		i=max(T);
		liste2->A->cle=i;
		liste2->poids=T[i];
		T[i]=0;
		nb_symbole--;
	}
	affichage_liste(liste);
	liste=liste->next;// il faudrait le liberer
	affichage_liste(liste);
	while (liste->next!=NULL){
		liste2=liste;
		affichage_liste(liste2);
		while (liste2!=NULL&&liste2->next!=NULL){
			if (liste2->poids==liste2->next->poids){
				A=malloc(sizeof(Arbre));
				A->ag= liste2->A;
				A->ad=liste2->next->A;
				liste2->A=A;
				liste2->poids--;
				liste2->next=liste2->next->next;
				liste2=liste2->next;
			}
			else liste2=liste2->next;
		}
	}
	return liste->A;
}

void decodage (FILE * fLecture,pArbre A,int taille){
	FILE *fEcriture=ouvertureFichierEcriture("../fichier_test/decodage.txt");
	char c;
	pArbre B= NULL;
	int i;
	int indice=0;
	for (i=0;i<taille;i++){
		B=A;
		if (getBit(fLecture,&indice,&c)==0){exit(0);}
		if (c==0){
			B=B->ag;
			printf("%i",0);
		}
		else {
			B=B->ad;
			printf("%i",1);
		}
		
		if (B==NULL) {printf( "erreur de  decodage\n");}
		else if (B->ag==NULL||B->ad==NULL){ //si on est sur une feuille 
			putByte(fEcriture,B->cle); //on met le symbole dans le fichier
			B=A;// on remonte en haut de l'arbre
		} 
	}
}



int main (){
	int T[N];
	int i;
	for (i=0;i<N;i++){T[i]=0;}
	T['A']=4;
	T['B']=4;
	T['C']=4;
	T['D']=4;
	T['E']=3;
	T['F']=3;
	T['G']=1;
	afficherT(T);
	pArbre A=construction_arbre_canonique(T);
	afficher_Arbre(A);
	
	generation_description_arbre(A);
	printf("\n");
	FILE * F=ouvertureFichierLecture("../fichier_test/code_huffman.txt");
	decodage(F,A,32);
	return 0;
}
