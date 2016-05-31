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


/* Generation description arbre aux 
 * Fonction recursive auxiliaire qui a partir d'un arbre A ecrit dans un fichier et stocke dans un tableau T
 * la profondeur de chaque symbole ou feuille de l'arbre.
 * 
 * Parametre:
 * 	A: un pointeur sur un arbre 
 * 	F: Un fichier ouvert en ecriture
 * 	size: La profondeur auquel on est deja
 * 	indice: a quelle possition dans un octet on est en train d'ecrire
 * 	T: Un tableau de taille N initialise avec des zero dans lequel on ecrit la profondeur des symbole 
 */

void generation_description_arbre_aux (pArbre A, FILE* F, char size, int indice, char * T){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// Cas d'une feuille 
			putByte(F,A->cle);
			putByte (F,size);			//	-> on ecrit dans le fichier
			
			T[A->cle]=size;				//	-> et on modifie la valeur dans le tableau; 
			
			  
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_description_arbre_aux(A->ag,F,size+1,indice,T);
			generation_description_arbre_aux(A->ad,F,size+1,indice,T);
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(50);}		
	}
	
}

/* Generation description arbre 
 * A partir d'un arbre A ecrit dans un fichier et stocke dans un tableau T
 * la profondeur de chaque symbole ou feuille de l'arbre.
 * 
 * Parametre:
 * 	A: un pointeur sur un arbre 
 * 	F: Un fichier ouvert en ecriture
 * 	T: Un tableau de taille N initialise avec des zero dans lequel on va ecrire la profondeur des symboles 
 */


void generation_description_arbre (pArbre A,char* T,FILE *F){

	generation_description_arbre_aux(A,F,0,0,T);printf("\n");
}



/* Generation code: 
 * Creer un tableau t avec le code pour chaque symbole
 * 
 * 
 * Parametre:
 * 	A: Un pointeur sur un arbre 
 * 	t: Un tableau de taille N dans lequel on ecrit le code de chaque symbole.
 *  s: Un entier qui contient dans ses bites de point faible le code du chemin parcouru dans l'arbre  
 */

void generation_code (pArbre A, int *t, int s){
	if (A==NULL){}
	else {
		if (A->ag==NULL && A->ad==NULL){// cas d'une feuille 
			t[A->cle]=s;
		}
		else if (A->ag!=NULL && A->ad!=NULL){ // cas d'un noeud -> on va dans les sous arbres  
			generation_code(A->ag,t,(s<<1));  // <- pareil ATTENTION !!!!!!!!!!!!!
			generation_code(A->ad,t,(s<<1)+1);//<- possible erreur c'etait *2 a la place de <<1
		}
		else { printf ("Erreur dans huffman_part2: Arbre mal forme\n");exit(48);}		
	}
	
}


/* Transcodage: 
 * A partir d'un arbre A code le texte du fichier fLecture dans fEcriture
 * (fEcriture contient deja l'entete avec l'arbre, la taille du fichier ect ...)
 * 
 * Parametre:
 * 	A: un pointeur sur un arbre 
 *  fLecture : Un fichier ouvert en lecture
 * 	fEcriture: Un fichier ouvert en ecriture
 * 	Longueur : Un tableau avec la taille du code de chaque caractere
 */
void Transcodage (pArbre A, FILE* fLecture,FILE * fEcriture ,char* Longueur){
	int indice =0;
	int t[N];
	char c;
	int i ;
	for (i=0;i<N;i++){
		t[i]=0;
	}
	generation_code(A,t,0); //<- met dans t le code de chaque symbole present dans le texte 
	//printf("generer le code :\n");
	//afficherT(t); 
	while (getByte(fLecture,&c)==1){
		//printf("%c:%d de longueur %d avec un indice : %i\n",c,t[(unsigned char)c],Longueur[(unsigned char)c],indice);
		putIntV2(fEcriture,t[(unsigned char)c],&indice,Longueur[(unsigned char)c]);
	}
}


/* Place:
 * Indique si il reste de feuille qui ne contienne pas encore de cle dans l'arbre ou le sous-arbre
 * 
 * Parametre:
 * 	A: un pointeur sur un arbre 
 * Renvoie:
 * 0 pour pas de place /1 sinon
 */

int place (pArbre A){
	int b=0;
	if (A==NULL) b=1; //arbre vide
	else if (A->ag==NULL &&A->ad==NULL) b=A->dispo;// cas d'une feuille
	else b= (place(A->ag)||place(A->ad));// cas d'un noeud
	return b;
}



/* Max:
 * calcule la valeur maximum d'un tableau T et retourne l'indice de cette valeur
 */
int max( int  T[]){
	int i;
	int max, imax;
	imax=0;
	max=T[imax];
	for (i=1;i<N;i++){
		if (T[i]>max) {
			max = T[i];
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






/* Construction arbre canonique:
 * Contruit l'arbre canonique a partir d'un tableau T qui la profondeur de chaque symbole dans l'arbre
 * 
 * Parametre:
 * 	T: Un tableau de taille N qui contient la profondeur des symboles dans l'arbre
 * Renvoie:
 * 	Un pointeur sur un arbre 
 */

pArbre construction_arbre_canonique (int T[] ){
	//printf ("je commence a construire l'arbre canonique\n");
	pArbre A;
	pl liste1=NULL;
	int i;
	int nb_symbole=0;
	for (i=0;i<N;i++){  // on compte le nombre de symbole a mettre dans l'arbre
		if (T[i]!=0) {nb_symbole++;}
	}
	
	//afficherT(T);
	//printf("nb_symbole:%i\n",nb_symbole);
	//on suppose le nombre de symbole non nul
	liste1 = malloc(sizeof (l));//element fictif de tete
	
	liste1->poids=42;
	liste1->next=NULL;
	//printf("Liste de debut :\n");
	//affichage_liste(liste1);
	pl liste2 = liste1; 
	//affichage_liste (liste2);
	//afficherT(T);
	
	while (nb_symbole>0){ // on construit un liste d'arbre -> au debut liste de feuille contenant tout les symboles trie 
		liste2-> next=malloc(sizeof (l));
		liste2->next->next=NULL;
		liste2= liste2->next;
		liste2->A= malloc (sizeof(Arbre));
		liste2->A->ad=NULL;
		liste2->A->ag=NULL;
		i=max(T);
		
		liste2->A->cle=i;
		liste2->poids=T[i];
		T[i]=0;
		nb_symbole--;
		
		//printf("\n==============================================\n");
		//afficherT(T);
		//affichage_liste(liste1);
	}
	//printf("liste de debut\n");
	//affichage_liste(liste1);
	liste1=liste1->next;// il faudrait le liberer
	//affichage_liste(liste1);
	int h=0;
	liste2=liste1;
	while (liste1->next!=NULL && h<12)
	{
		h++; // tant qu'il y a plus d'un element dans la liste (encore une fois on suppose qu'il y a au moins un elt)
	 // on utilise le pointeur liste2 pour avancer dans la liste
	//	printf(" je rentre dans le premier while\n");
		//affichage_liste(liste2);
		
		while (liste2!=NULL&&liste2->next!=NULL){ //tant que il reste deux elmt avant la fin de la liste
			
		//	printf(" je suis dans le while \n");
			if (liste2->poids==liste2->next->poids){ //si deux element on la meme profondeur dans l'arbre
			//	printf(" je rentre la \n");
				A=malloc(sizeof(Arbre)); //on cree un arbre avec c'est deux elmt
				A->ag= liste2->A;
				A->ad=liste2->next->A;
				liste2->A=A; // et on le met a la place de l'arbre de l'element courant de la liste
				liste2->poids--;
				liste2->next=liste2->next->next; // penser a le liberer   // on eleve l'element apres l'element courant
				//liste2=liste2->next;// on avance dans la liste
				liste2=liste1; // on retourne au debut de la liste
			}
			else liste2=liste2->next; // si il n'ont pas le meme poid on avance dans la liste
			
		}
	}
	//affichage_liste(liste1);
	//printf("je suis la \n");
	//afficher_Arbre(liste1->A);
	return liste1->A; //on retourne l' arbre du dernier elmt de la liste
}

/* Decodage_Texte:
 * A partir d'un fichier fLecture de texte codé ou l'entete a deja ete lu
 * ecrit dans le fichier fEcriture le texte decoder
 * 
 * Parametre:
 * 	fLecture : Un fichier ouvert en Lecture
 *  fEcriture: Un fichier ouvert en Ecriture
 *  A: Un pointeur sur un arbre
 *  taille: la taille du fichier
 */

void decodage_texte (FILE * fLecture,FILE* fEcriture,pArbre A,int taille){
	char c;
	pArbre B= NULL;
	int i;
	int indice=0;
	B=A;
	for (i=0;i<taille;i++){
		
		if (getBit(fLecture,&indice,&c)==0){printf(" j'ai fini de lire\n");exit(49);}
		
		//printf("%d\n",c);
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
			//printf("Affichage:\n");
			//printf(" \n%d\n ",B->cle); 
			putByte(fEcriture,B->cle); //on met le symbole dans le fichier
			//printf ("cle :%d \n  ",B->cle);
			B=A;// on remonte en haut de l'arbre
		} 
	}
}

/* Codage:
 * Code un fichier fLecture, dans un fichier fEcriture avec un arbre A et un fichier de longeur taille
 * 
 * Parametre:
 * fLecture : Un fichier ouvert en Lecture
 *  fEcriture: Un fichier ouvert en Ecriture
 *  A: Un pointeur sur un arbre
 *  taille: la taille du fichier
 */
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
	//printf("Tableau des profondeur dans transcodage\n");
	//afficherT2(Longueur);
	//printf("\n");
	Transcodage(A,fLecture,fEcriture,Longueur);
}
/* Decodage:
 * Decode un fichier fLecture, dans un fichier fEcriture 
 * 
 * Parametre:
 * 	fLecture : Un fichier ouvert en Lecture
 *  fEcriture: Un fichier ouvert en Ecriture
 */
void decodage (FILE *fLecture, FILE* fEcriture){
//lire la transcription de l'arbre
	printf("\n==================\nje decode\n================\n");
	int T[N];
	int i;
	for (i=0;i<N;i++){T[i]=0;}
	char c;
	char taille;
	//lire le nombre de symbole
	char nb_symbole=0;//=6;
	getByte(fLecture,&nb_symbole);
	printf(" Le nombre de symbole lu est : %d\n",(unsigned char) nb_symbole);
	for (i=0;i<=((unsigned char) nb_symbole);i++){
		getByte(fLecture,&c);
		//printf("%d:",(unsigned char)c);
		getByte(fLecture,&taille);
		//printf("%d_",(unsigned char)taille);
		T[(unsigned char)c]=(unsigned char)taille;
	}
	//printf("Tableau:\n");
	//afficherT(T);
	
//creer l'arbre
	pArbre A= construction_arbre_canonique(T);
	//afficher_Arbre(A);
	//printf("\n Fin de l'affichage de l'arbre.\n");

//lire la taille
	unsigned int taille_fichier=0;
	for(i=0;i<4;i++){
		getByte(fLecture,&taille);
		//printf("  %d   ",(unsigned char)taille);
		taille_fichier=(taille_fichier<<8)+(unsigned char)taille;// A VERIFIER
	}
	//printf("\nTaille : %u\n",taille);
	//printf("\nTaille du fichier: %i\n",taille_fichier);
	//taille_fichier=256; // <- A ENLEVER !!!

//decoder le fichier	
	decodage_texte(fLecture,fEcriture,A,taille_fichier);
}	

