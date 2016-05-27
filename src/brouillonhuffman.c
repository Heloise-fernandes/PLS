#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 256

/*
compilation
gcc huffman.c -o huffman
execution
./huffman
necessite le fichier entropie.txt au bon format voit entropie.c)
*/
typedef struct n {
  signed char cle;
  struct n *gauche, *droite;
} noeud_t ;

typedef noeud_t *Abr_t; 





noeud_t  *ajouter_noeud (noeud_t *a, noeud_t *n)
{
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->gauche = ajouter_noeud (a->gauche, n) ;
  else
	a->droite = ajouter_noeud (a->droite, n) ;
  return a ;  
}  




Abr_t ajouter_cle (Abr_t a, signed char cle)
{
  noeud_t *n ;
  Abr_t b ;
  
  n = (noeud_t *) malloc (sizeof(noeud_t)) ;
  n->cle = cle;
  n->gauche = NULL ;
  n->droite = NULL ;

  b = ajouter_noeud ((noeud_t *)a, n) ;
  return b ;
}



Abr_t fusion(Abr_t a,Abr_t b){
	Abr_t c = NULL;
	c=ajouter_cle(c,(a->cle) + (b->cle));
	c->gauche = a;
	c->droite = b;
	return c;

}


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

//tri huffman

//renvoi l' indice du min du tableau
int recherchemin (Abr_t *tab,int nb_elem,int i){
		
	int indmin = i;
	int j;
	for (j=i+1; j<nb_elem;j++){
		if ((tab[j]->cle) < tab[indmin]->cle ){
			indmin = j;
			
		}	
	

	}

return indmin;
}
//echange les case d'indice i et j du tableau
void echange(Abr_t *tab,int i,int j ){
	Abr_t temp;	
	temp = tab[i];
	tab[i]=tab[j];
	tab[j]=temp;
	}

void tri(Abr_t *tab,int nb_elem){
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
int recherchemin2 (signed char *tab,int nb_elem,int i){
		
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
void echange2(signed char *tab,int i,int j ){
	float temp;	
	temp = tab[i];
	tab[i]=tab[j];
	tab[j]=temp;
	}

void tri2(signed char *tab,int nb_elem){
	int i;
	int indmin;
	int j;
	
	for(i=0;i<nb_elem;i++){
		indmin = recherchemin2(tab,nb_elem,i);
	
		echange2(tab,i,indmin);
	}



}



//elle "descent" la valeur restante (id est a partir de l'indice l ) la plus faible du tableau de probas dans le tableau d'arbre sous forme d'arbre
int descente(signed char *tab,int nb_elem,Abr_t *huffman, int l,int L){
	 Abr_t temp;
	
	if (l<nb_elem ){
		temp=NULL;
		temp = ajouter_cle(temp,tab[l]);
			
		
		if (L<(TAILLE_MAX)-1){//si le tableau n'est pas plein 
			huffman[L]=temp;
			L++;

		}else{printf("ERROR TABLEAU PLEIN ");}
	}
return L;

}

//affiche le tableau de huffman et sa Longueur utilise pour le debbugage
void debug(Abr_t *huffman,int L){
int i;
for ( i=0;i<L;i++){
		printf("huffman[%d] : ",i);
		afficher_arbre(huffman[i]);
		printf("\n");
		printf("L : %d",L);
		printf("\n");
	}


}


void initialiser_tableau_poids_symbole(signed char* symb ){//attention duplication de code 
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
int main (int argc , char *argv[]){

 
	//FILE* fic = NULL;
	int nb_elem;
	int nb_even;
	int i;
	int j;
	int l = 2 ;// indice repere sur tab 
	int L;//Longueur de huffman  de huffman
	int k = 1; //sert au calcul du nb d element de huffman car la fusion diminue ce nombre
	signed char tab[TAILLE_MAX];
	signed char  copietab[TAILLE_MAX];//pour se souvenir de l'ordre initial copietab[0] est la probabilite de e0
	nb_elem = 4; //a calculer a partir du nombre de case differente de zeros dans le tableau

	Abr_t huffman[TAILLE_MAX];
	Abr_t a;

	/* fic = fopen("entropie.txt","r");//on ouvre le fichier en lecture
	if (fic != NULL ){
		fscanf(fic,"%d",&nb_elem);//on recupere le nb d'elements indiquer au debut du fichier
		//printf("%d\n",nb_elem);
		if (nb_elem<TAILLE_MAX){
			for (i = 0 ; i<nb_elem ; i++){
				fscanf(fic,"%c",tab+i);//on recupere chaque element et on le met dans un tableau
				copietab[i]=tab[i];//on copie le tableau de probas

			}
		}else {printf("ERROR nb d'elements trop important");}
	fclose(fic);//on n'oublie pas de fermer le fichier
*/
//	

//pour le cas de plusieurs evenement consecutif : ne marche pas encore mais plus le temps de voir 
/*

	
	do{

	
	printf("Simple : 1 Double : 2 triple : 3  limite a 3 \n" );
	scanf("%d",&nb_even);	
	
	}while(nb_even >3);
	switch(nb_even){
		case 1 :break;//rien a faire 
		case 2 : for (i = 0 ;i<nb_elem;i++){
				for (j = 0 ;j<nb_elem;j++){
					tab[i*nb_elem+j]=copietab[i]*copietab[j];
				}
			}


			break;
		case 3 :
			for (i = 0 ;i<nb_elem;i++){
				for (j = 0 ;j<nb_elem;j++){
					for (k = 0 ;k<nb_elem;k++){}
						tab[i*nb_elem*nb_elem+j*nb_elem+k]=copietab[i]*copietab[j]*copietab[k];
				}
			}

	}

	
	
*/
	initialiser_tableau_poids_symbole(tab);
	for (i = 0 ; i<nb_elem ; i++){
				copietab[i]=tab[i];
	}//on copie le tableau de probas
	
	tri2(tab,nb_elem);//tableau de probas trie

	//initialisation du tableau d'arbre par les deux plus petit element de tableau de probas sous forme d'arbre	
	for(i=0;i<2;i++){
		a=NULL;
		a = ajouter_cle(a,tab[i]);
		huffman[i]=a;
		

	}
	debug(huffman,2);
	
	
	huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
	L=1;//initialisationde la longueur de huffman 
	
	debug(huffman,L);
	do{
	
	
		do{

			L = descente(tab,nb_elem,huffman,l,L);
			l++;//car on a desendu un element l indqiue donc l'element suivant
			
		}while((huffman[L-1]->cle)<=huffman[L-2]->cle);
		
		debug(huffman,L);
		tri(huffman,L);//on tri 
		
	
		huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
		debug(huffman,L);
	for (j=1;j<L-1;j++){
		huffman[j]=huffman[j+1];
	}

	L--;
	debug(huffman,L);
	}while(l<nb_elem);
	
	
	//tout les element sont descendus on peu donc finir par tout fusionner sans oublier de trier a chaque fois 
	
	while (L!=1){
		tri(huffman,L);//on tri 
		
		huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
		
	for (j=1;j<L-1;j++){
		huffman[j]=huffman[j+1];
	}
	L--;
	
	debug(huffman,L);
	
	}






	//printf("ok285\n");
	
	printf("l'affichage s'effectue en ordre fils gauche noeud fils droit : \n");
	afficher_arbre(huffman[0]);
	

	return 0;

	}



