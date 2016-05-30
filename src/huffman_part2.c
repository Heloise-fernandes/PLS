/*
 * 
 * huffman_part2.h
 * 
 */

#include "stdlib.h"
#include "stdio.h"
#include "limits.h"

#include "Lecture_Ecriture_B.h"
#include "arbre.h"
#include "huffman_liste.h"



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
	//printf("Je suis dans transcodage\n");
	int indice =0;
	
	int t[N];
	char c;
	generation_code(A,t,0);
	 
	while (getByte(fLecture,&c)==1){
		//printf("%c:%i de longueur %i avec un indice : %i\n",c,t[(int)c],Longueur[(int)c],indice);
		putIntV2(fEcriture,t[(int)c],&indice,Longueur[(int)c]);
	
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







//contruit l'arbre canonique a partir d'un tableau T avec la longueur de chaque symbole dans l'arbre
pArbre construction_arbre_canonique (int T[] ){
	pArbre A;
	pl liste;
	int i;
	int nb_symbole=0;
	for (i=0;i<N;i++){  // on compte le nombre de symbole a mettre dans l'arbre
		if (T[i]!=0) {nb_symbole++;}
	}
	
	/*T['A']=3;
	T['B']=7;
	T['C']=5;
	T['D']=8;
	T['E']=3;
	T['F']=1;
	T['G']=3;
	T['H']=6;
	T['I']=8;
	T['J']=4;
*/
	
	printf("nb_symbole:%i\n",nb_symbole);
	//on suppose le nombre de symbole non nul
	liste= malloc(sizeof (l));//element fictif de tete
	pl liste2= liste; 
	while (nb_symbole>0){ // on construit un liste d'arbre -> au debut liste de feuille contenant tout les symboles trie 
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
	//affichage_liste(liste);
	while (liste->next!=NULL){ // tant qu'il y a plus d'un element dans la liste (encore une fois on suppose qu'il y a au moins un elt)
		liste2=liste;  // on utilise le pointeur liste2 pour avancer dans la liste
		affichage_liste(liste2);
		while (liste2!=NULL&&liste2->next!=NULL){ //tant que il reste deux elmt avant la fin de la liste
			affichage_liste(liste2);
			if (liste2->poids==liste2->next->poids){ //si deux element on la meme profondeur dans l'arbre
				A=malloc(sizeof(Arbre)); //on cree un arbre avec c'est deux elmt
				A->ag= liste2->A;
				A->ad=liste2->next->A;
				liste2->A=A; // et on le met a la place de l'arbre de l'element courant de la liste
				liste2->poids--;
				liste2->next=liste2->next->next; // penser a le liberer   // on eleve l'element apres l'element courant
				//liste2=liste2->next;// on avance dans la liste
				liste2=liste; // on retourne au debut de la liste
			}
			else liste2=liste2->next; // si il n'ont pas le meme poid on avance dans la liste
		}
	}
	return liste->A; //on retourne l' arbre du dernier elmt de la liste
}


//mettre une erreur quand il reste des charactere pas decodable ou pas ...
//a partir d'un fichier, decode un texte de longueur taille coder avec l'arbre A ,  
void decodage_texte (FILE * fLecture,FILE* fEcriture,pArbre A,int taille){
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
int T[N];
int i;
for (i=0;i<N;i++){T[i]=0;}
char c;
char taille;
//lire le nombre de symbole
int nb_symbole=8;
for (i=0;i<nb_symbole;i++){
	getByte(fLecture,&c);
	printf("%c:",c);
	getByte(fLecture,&taille);
	printf("%c",taille);
	T[(int)c]=(int)taille;
}
printf("Tableau:\n");
afficherT(T);
//creer l'arbre
pArbre A= construction_arbre_canonique(T);
afficher_Arbre(A);
//lire la taille
int taille_fichier=0;
for(i=0;i<4;i++){
	getByte(fLecture,&taille);
	printf("  %c   ",taille);
	taille_fichier=(taille_fichier<<8)+(int)taille;// A VERIFIER
}
printf("\nTaille du fichier: %i\n",taille_fichier);
taille_fichier=256;
//decoder le fichier	
	decodage_texte(fLecture,fEcriture,A,taille_fichier);
}	

