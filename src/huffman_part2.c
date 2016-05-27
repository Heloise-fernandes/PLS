#include "stdlib.h"
#include "stdio.h"
#include "limits.h"
#define N 256
#include "../include/Lecture_Ecriture_B.h"
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


//fonction auxiliaire pour generation description arbre
void generation_description_arbre_aux (pArbre A, FILE* F, char size, int indice, char * T){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// cas d'une feuille -> on ecrit dans le fichier
			putByte(F,A->cle);
			T[A->cle]=size;
			
			putByte (F,size);  
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_description_arbre_aux(A->ag,F,size+1,indice,T);
			generation_description_arbre_aux(A->ad,F,size+1,indice,T);
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(50);}		
	}
	
}

// apartir d'un arbre A ecrit dans un fichier la description de l'arbre
void generation_description_arbre (pArbre A,char* T,FILE *F){
	
	
	generation_description_arbre_aux(A,F,0,0,T);printf("\n");
	
}

//cree un tableau t avec le code pour chaque symbole
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
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(48);}		
	}
	
}



//code un fichier a partir de l'arbre A
void Transcodage (pArbre A, FILE* fLecture,FILE * fEcriture ,char* Longueur){
	printf("Je suis dans transcodage\n");
	int indice =0;
	
	int t[N];
	char c;
	generation_code(A,t,0);
	 
	while (getByte(fLecture,&c)==1){
		printf("%c:%i de longueur %i avec un indice : %i\n",c,t[c],Longueur[c],indice);
		putIntV2(fEcriture,t[c],&indice,Longueur[c]);
	
	}
}

//indique si il reste des feuille sans cle dans l'arbre
int place (pArbre A){
	int b=0;
	if (A==NULL) b=1; //arbre vide
	else if (A->ag==NULL &&A->ad==NULL) b=A->dispo;// cas d'une feuille
	else b= (place(A->ag)||place(A->ad));// cas d'un noeud
	return b;
}

//affiche un tableau
void afficherT (int T[]){
	int i;
	for (i=0;i<N;i++){
		
		printf("%i",T[i]);		
	}
	printf ("\n");
}

//calcule la valeur maximum d'un tableau T et retourne l'indice de cette valeur
int max( int  T[]){
	int i;
	int max, imax;
	imax=0;
	max=0;
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



void affichage_liste (pl liste){
	while (liste!=NULL){
		printf("(%i) ",liste->poids);
		liste=liste->next;
	}
	printf("\n");
}

//contruit l'arbre cononique a partir d'un tableau T avec la longueur de chaque symbole dans l'arbre
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
	//affichage_liste(liste);
	liste=liste->next;// il faudrait le liberer
	//affichage_liste(liste);
	while (liste->next!=NULL){
		liste2=liste;
		//affichage_liste(liste2);
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


//mettre une erreur quand il reste des charactere pas decodable ou pas ...
//a partir d'un fichier, decode un texte de longueur taille coder avec l'arbre A ,  
void decodage_texte (FILE * fLecture,pArbre A,int taille){
	FILE *fEcriture=ouvertureFichierEcriture("../fichier_test/decodage.txt");// ane pas ouvrir ici
	char c;
	pArbre B= NULL;
	int i;
	int indice=0;
	B=A;
	for (i=0;i<taille;i++){
		
		if (getBit(fLecture,&indice,&c)==0){printf(" j'ai fini de lire\n");exit(49);}
		
		//printf("%d",c);
		if (c==0){
			B=B->ag;
			//printf("%i\n",0);
		}
		else {
			B=B->ad;
			//printf("%i\n",1);
		}
		
		if (B==NULL) {printf( "erreur de  decodage\n");}
		else if (B->ag==NULL||B->ad==NULL){ //si on est sur une feuille 
			putByte(fEcriture,B->cle); //on met le symbole dans le fichier
			//printf ("cle :%d \n  ",B->cle);
			B=A;// on remonte en haut de l'arbre
		} 
	}
	fermetureFichier(fEcriture);
}

void codage (FILE *fLecture, FILE* fEcriture, pArbre A, int taille){
	char Longueur[N];
	int i;
	for (i=0;i<N;i++){
		Longueur[i]=0;
	}
	//mettre le code en debut de fichier et recuperation de la longueur de chaque code 
	generation_description_arbre(A,Longueur,fEcriture);// rejouter l'ecriture du nombre de symbole
	// ecrire la taille du fichier sur 32bit
	putTaille(fEcriture,taille);

	//transcrire le fichier //
	Transcodage(A,fLecture,fEcriture,Longueur);
}

void decodage (FILE *fLecture, FILE* fEcriture){
//lire la transcription de l'arbre
//creer l'arbre
pArbre A;
//lire la taille
//deocder le fichier	
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
	
	pArbre A=construction_arbre_canonique(T);
	afficher_Arbre(A);
	printf("\n");
	
	//generation_description_arbre(A,T2);
	FILE *F1= ouvertureFichierLecture("../fichier_test/test_texte.txt");
	FILE *F2 = ouvertureFichierEcriture ("../fichier_test/code.txt");
	codage(F1,F2,A,256);
	//printf("J'essaie de coder le texte\n");
	//Transcodage(A,F1,fEcriture,T2);
	//printf("J'ai fini de coder le texte\n");
	//FILE * F2=ouvertureFichierLecture("../fichier_test/code_huffman.txt");
	
	
	//decodage(F2,A,16);
	fermetureFichier(F1);
	fermetureFichier(F2);
	return 0;
}
