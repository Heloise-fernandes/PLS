#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../include/Package_Merge.h"//attntion
//se mettre daccord sur les om des constantes
//est se que l'on mettraait toutes es fonction arbre et liste dans un .h 
//srtucture.h ou liste.h et arbre.h ?
#define TAILLE_MAX 256
#define TAILLE_TAB 256
/*
compilation
gcc huffman.c -o huffman
execution
./huffman
necessite le fichier entropie.txt au bon format voit entropie.c)
*/
/*
typedef struct n {
  signed char cle;
  int dispo;
  struct n *gauche, *droite;
} noeud_t ;

typedef noeud_t *Abr_t; 
*/

typedef struct _Arbre{
	signed char cle;
	int dispo;
	struct _Arbre *ag;
	struct _Arbre *ad;
} Arbre, *pArbre;




//a supprimer plus tard provient de Package_merge

typedef struct _l{
	pArbre A;
	int poids;
	struct _l *next;
} l,*pl;


pl getElmt(pl pointeur, int indice)
{
	if(indice == 0){return pointeur;}
	else{ return getElmt(pointeur->next, indice--);}
	
}

void afficherListe(pl pointeurListe)
{
	pl pointeur,affiche;
	int i;
	pointeur = pointeurListe;
	for( i = 0; i <TAILLE_TAB; i++)
	{
		affiche = getElmt(pointeur, i);
		printf("Element : %d, nombre : %d\n",i,affiche->poids);
	}
}






pl suprElmt(pl pointeurCourant,pl parent, int indice)
{
	if(indice == 0)
	{	if(parent!=NULL)
		{
			parent->next = pointeurCourant->next;
			pointeurCourant->next = NULL; 
		}
		else
		{
			parent = pointeurCourant->next;
			pointeurCourant->next = NULL;
		}
		return pointeurCourant;
	}
	else
	{	indice = indice - 1;
		return suprElmt(pointeurCourant->next,pointeurCourant, indice);
	}
	return NULL;
}
pl trier_Liste(pl pointeurListe)
{
	pl pointeur = pointeurListe;
	
	pl pointeurSauvegarde;
	pl pointeurJ;
	int i,j;
	for(i = 1; i < TAILLE_TAB; i++)										//pour i de 1 n-1
	{
		pointeurSauvegarde = suprElmt(pointeur,NULL, i);				//x = T[i]
		j = i;															//j<-i
		pointeurJ = getElmt(pointeur, j-1);
		while((j>0)&&(pointeurJ->poids > pointeurSauvegarde->poids))	//tantque j>0 et T[j - 1] > x
		{
			j--;
			if(j>0){pointeurJ = getElmt(pointeur, j-1);}					//T[i]<-T[j-1]; j<-j-1
			
		}
		if(j==0)
		{
			pointeurSauvegarde->next = pointeur;
			pointeur = pointeurSauvegarde;
		}
		else
		{
			pointeurSauvegarde->next = pointeurJ->next;
			pointeurJ->next = pointeurSauvegarde;						//T[j] ← x
		}
											
	}
	return pointeur;
}

//rajout dans Package merge ?


void insertElm(pl pointeurListe, pArbre a){
	
		pl pointeurConstruction;	
		pointeurConstruction =  malloc(sizeof(l));
		pointeurConstruction->A = a;
		pointeurConstruction->poids = a->dispo;
		
	}

































Arbre  *ajouter_noeud (Arbre *a, Arbre *n)
{
  if (a == NULL)
    return n ;
  else if (n->dispo < a->dispo)
	a->ag = ajouter_noeud (a->ag, n) ;
  else
	a->ad = ajouter_noeud (a->ad, n) ;
  return a ;  
}  
pArbre ajouter_dispo (pArbre a, int dispo)
{
  Arbre *n ;
  pArbre b ;
  
  n = (Arbre *) malloc (sizeof(Arbre)) ;
  n->dispo = dispo;
  n->ag = NULL ;
  n->ad = NULL ;

  b = ajouter_noeud ((Arbre *)a, n) ;
  return b ;
}
pArbre fusion(pArbre a,pArbre b){
	pArbre c =  malloc(sizeof(Arbre));
	c=ajouter_dispo(c,(a->dispo) + (b->dispo));
	c->ag = a;
	c->ad = b;
	return c;

}
void afficher_Arbre2 (pArbre A){//modif pour afficher dispo
	if (A!=NULL){
		if (A->ad==NULL&&A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else if (A->ad==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else if (A->ag==NULL){//cas d'une feuille
			printf("F(%d)",A->dispo);
		}
		else { // cas d'un noeud
			printf("Noeud (");
			afficher_Arbre2( A->ag);
			printf(",");
			afficher_Arbre2 (A->ad);
			printf(")");
		}
	}
}
/*
void afficher_arbre (Abr_t a)
{
  if (a != NULL)
      {
	//printf("g");
	afficher_arbre (a->gauche) ;
	//printf("cle")
	printf (" %d ", a->cle) ;
	//printf (" %s ", a->nom) ;
	//printf("d");
	afficher_arbre (a->droite) ;
      }
  return ;
}
*/
//tri huffman
//renvoi l' indice du min du tableau
int recherchemin (pArbre*tab,int nb_elem,int i){
		
	int indmin = i;
	int j;
	for (j=i+1; j<nb_elem;j++){
		if ((tab[j]->dispo) < tab[indmin]->dispo ){
			indmin = j;
			
		}	
	

	}

return indmin;
}
//echange les case d'indice i et j du tableau
void echange(pArbre *tab,int i,int j ){
	pArbre temp;	
	temp = tab[i];
	tab[i]=tab[j];
	tab[j]=temp;
	}
void tri(pArbre *tab,int nb_elem){
	int i;
	int indmin;
	//int j;
	
	for(i=0;i<nb_elem;i++){
		indmin = recherchemin(tab,nb_elem,i);
	
		echange(tab,i,indmin);
	}



}
//tri probas
//renvoi l' indice du min du tableau
int recherchemin2 (int *tab,int nb_elem,int i){
		
	int indmin = i;
	int j;
	for (j=i+1; j<nb_elem;j++){
		if ((tab[j]) < tab[indmin] ){
			indmin = j;
			
		}	
	

	}

return indmin;
}
//echange les case d'indice i et j du tableau
void echange2(int *tab,int i,int j ){
	float temp;	
	temp = tab[i];
	tab[i]=tab[j];
	tab[j]=temp;
	}

void tri2(int *tab,int nb_elem){
	int i;
	int indmin;
	//int j;
	
	for(i=0;i<nb_elem;i++){
		indmin = recherchemin2(tab,nb_elem,i);
	
		echange2(tab,i,indmin);
	}



}
//elle "descent" la valeur restante (id est a partir de l'indice l ) la plus faible du tableau de probas dans le tableau d'arbre sous forme d'arbre
int descente(int *copie_symb,int nb_elem,pArbre *huffman, int l,int L){
	 pArbre temp;
	
	if (l<nb_elem ){
		temp=NULL;
		temp = ajouter_dispo(temp,copie_symb[l]);//attenstion
			
		
		if (L<(nb_elem)-1){//si le tableau n'est pas plein 
			huffman[L]=temp;
			L++;

		}else{printf("ERROR TABLEAU PLEIN ");}
	}
return L;

}
//affiche le tableau de huffman et sa Longueur utilise pour le debbugage
void debug(pArbre *huffman,int L){
int i;
for ( i=0;i<L;i++){
		printf("huffman[%d] : ",i);
		afficher_Arbre2(huffman[i]);
		printf("\n");
		printf("L : %d",L);
		printf("\n");
	}


}

void initialiser_tableau_poids_symbole(int* symb ){//attention duplication de code 
	//on initialise les 256 cases du tableau du poids des sybole a 0;
	int i = 0 ;
	for ( i = 0 ; i < TAILLE_MAX ; i++ ){//attention 
		symb[i]=0;//attention
	}
	symb[0] = 1;
	symb[1] = 1;
	symb[2] = 1;
	symb[3] = 1;


}

void initialiser_tableau(int* symb){//attention
	//on initialise les 256 cases du tableau du poids des sybole a 0;
	int i = 0 ;
	for ( i = 0 ; i < TAILLE_MAX ; i++ ){//attention 
		symb[i]=0;//attention
	}



}
//remplir une copie du tableau contenant le poids des symboles
 void copie_symbole_non_nul(int* symb,int* copie_symb ){
		int i = 0 ;
		int j = 0 ;
		for ( i = 0 ; i < TAILLE_MAX ; i++ ){
				if(symb[i]!= 0){
					copie_symb[j] = symb[i];
					j++;
					}
			} 
	}
	
int nb_element_non_nul(int *symb){
	int i ;
	int cpt = 0 ;
	for ( i = 0 ; i < TAILLE_MAX ; i++ ){
				if(symb[i]!= 0){
					cpt++;
					
				}
	} 
	return cpt;
}	

void init_tableau_huffman(int* copie_symb,pArbre* huffman){
	int i ;
	//initialisation du tableau d'arbre par les deux plus petit element de tableau de poids sous forme d'arbre	
	pArbre a;
	for(i=0;i<2;i++){
		a=NULL;
		a = ajouter_dispo(a,copie_symb[i]);//attention nb d elem >=2 
		huffman[i]=a;
	}
}

pArbre generation_huffman(int* symb){
/*	
 * 
	
	
	int nb_elem = nb_element_non_nul(symb);
		printf("nb-elem = %d\n",nb_elem);
	int copie_symb[nb_elem];
	int l = 2; //indice repre copie_symb
	int L;//indice case dispo dans Huffman
	int i = 0 ;
	//pArbre a;
	pArbre huffman[3];//atention
	for (i = 0 ; i < 3 ;i++){
		huffman[i]=NULL;
		}
		debug(huffman,3);//debug
	copie_symbole_non_nul(symb,copie_symb);
	for (i = 0 ; i < 5 ; i++){//debug
			printf(" i = %d et copie_symb[%d] = %d\n ",i,i,copie_symb[i]);
		}
	tri2(copie_symb,nb_elem);//tableau de poids trie
	for (i = 0 ; i < 5 ; i++){//debug
			printf(" i = %d et copie_symb[%d] = %d\n ",i,i,copie_symb[i]);
		}
	
	init_tableau_huffman(copie_symb,huffman);
	huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
	L=1;//initialisationde la longueur de huffman 
	//hypothese au moins 3 elem ?
	debug(huffman,2);
	//printf(" avant le do while  (l,L) = ( %d , %d )\n",l,L);
	do {
		
		
			while (l < nb_elem && L !=3){//tans qu'il reste des elem et que huffman non remplis 3 cases on les descend sous forme d'arbre 
				//printf(" dans le do while avant la descente  l = %d L = %d",l,L);
				L = descente(copie_symb,nb_elem,huffman,l,L);//on descend le plus petit
				//printf(" dans le do while l = %d L = %d",l,L);
				l++;//car on a desendu un element l indqiue donc l'element suivant
				//debug(huffman,L);
			}	
			tri(huffman,nb_elem);	
			//debug(huffman,L);
			huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie	
			//debug(huffman,L);
			//on tri puis on fusionnne puis on decale a gauche 	
			huffman[1]=huffman[2];
			//liberer la memoire ?
			huffman[2]=NULL;
			L--;//le decalage libere une case 
			printf("ici\n");
			debug(huffman,L);
			printf("dernier L = %d ",L);
			printf("l %d ",l);
	}while(L!=1 || !(L==2 && l==nb_elem -1 ));
	printf("sortie ? \n ");
	return huffman[0];
	//liberation de memoire ? quand ? 
*/	
return NULL;
}




//void generation_huffman_liste(int* symb){
void generation_huffman_liste(){
	
	int* tableau = malloc(sizeof(int)*TAILLE_TAB);
	int i;
	pl pointeurListe, pointeurConstruction;	
	pointeurListe = malloc(sizeof(l));
	pointeurConstruction = pointeurListe;
	//FILE* fichier = ouvertureFichierLecture(chemin);
	
	//Remplir le tableau
	//remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	//Initialisation d'un tableau
	for(i = 0; i <TAILLE_TAB; i++)
	{
		tableau[i]=0;
	}
	
	tableau[0] = 50; 
	tableau[1] = 5;
	tableau[2] = 25;
	tableau[3] = 1;
	tableau[4] = 70;
	tableau[5] = 200;
	tableau[6] = 80;
	tableau[7] = 17;
	tableau[8] = 2;
	tableau[9] = 32;
	
	//Création de la liste
	for(i = 0; i < TAILLE_TAB; i++)
	{
		pointeurConstruction->A = malloc(sizeof(Arbre));
		pointeurConstruction->A->cle = i;
		pointeurConstruction->A->dispo = tableau[i];
		pointeurConstruction->A->ag = NULL;
		pointeurConstruction->A->ad = NULL;
		pointeurConstruction->poids = tableau[i];
		pointeurConstruction->next = malloc(sizeof(l));
		pointeurConstruction = pointeurConstruction->next;
	}
	
	//Trie et affichage de la liste
	pl trie = trier_Liste(pointeurListe);
	afficherListe(trie);
	
	
	
	
	
	
	
	
	
	
	
	/*
	
	
	//int nb_elem = nb_element_non_nul(symb);
	//int copie_symb[nb_elem];
	//copie_symbole_non_nul(symb,copie_symb);
	
	
	//tri2(copie_symb,TAILLE_MAX);//tableau de poids trie
	//tri de la liste plus efficace 
	pl pointeurListe,pointeurConstruction;;	
	int i = 0;
	pointeurListe = malloc(sizeof(l));
	pointeurConstruction = pointeurListe;
	
	//Remplir le tableau 
	//remplir_tableau_poids_symbole_et_calcul_taille(tableau,fichier);
	
	//for(i = 0; i <nb_elem; i++)
	for(i = 0; i <TAILLE_TAB; i++)
	{
		
		
		//Création de la liste
		pointeurConstruction->A = malloc(sizeof(Arbre));
		pointeurConstruction->A->cle = i;
		pointeurConstruction->A->dispo = symb[i];
		pointeurConstruction->A->ag = NULL;
		pointeurConstruction->A->ad = NULL;
		pointeurConstruction->poids = symb[i];
		pointeurConstruction->next = malloc(sizeof(l));
		pointeurConstruction = pointeurConstruction->next;
		afficherListe(pointeurListe);
	}
	
	
	afficherListe(pointeurListe);
	trier_Liste( pointeurListe);
	afficherListe(pointeurListe);
	
	//on enleve les 0 du debut de la liste
	while(pointeurListe->poids==0){
		 pointeurListe = suprElmt(pointeurListe,NULL,0) ;
		 
		 
		 //pointeurListe = pointeurListe->next;
		 //attention fuite memoire utiliser supprimer elm des que disponible
		}
	//on recupere les deux arbre des plus petit
	/*
	 * 
	while((pointeurListe)->next !=NULL ){
		pArbre a = (getElmt(pointeurListe,0)->A);
		pArbre b = (getElmt(pointeurListe,1)->A);
		pArbre c = fusion(a,b);
		pointeurListe = suprElmt(pointeurListe,NULL,0) ; 
		pointeurListe = suprElmt(pointeurListe,NULL,0) ; 
		insertElm (pointeurListe,c);								
	}
	afficherListe(pointeurListe);
	* */
//return (pointeurListe);



}




int main(int argc , char *argv[]){
	
	//int i = 0 ;
	//int symb[256];//256 TAILLE_MAX N_MAX
	
	//pArbre resultat = NULL;
	
	//initialiser_tableau(symb);
	/*
	for (i = 0 ; i < TAILLE_MAX ;i++){
			//printf("( %d , %d )\n",i,symb[i]);
			;
		}
		symb[65]=25000;
		symb[66]=20000;
		symb[67]=15000;
		symb[68]=10000;
		symb[69]=50000;
		
		for (i = 0 ; i < TAILLE_MAX ;i++){
		//printf("( %d , %d )\n",i,symb[i]);
			;
		}
	*/
	//resultat = generation_huffman_liste(symb);
	 generation_huffman_liste();
	
	
	
	
	
	
	
	
	
	
	//afficher_Arbre2(resultat);
	 
	return 0;
	
	
}





	

	



