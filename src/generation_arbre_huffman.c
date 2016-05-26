#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1000

/*
compilation
gcc huffman.c -o huffman
execution
./huffman
necessite le fichier entropie.txt au bon format voit entropie.c)
*/
/*
 * 
typedef struct n {
  signed char cle; 
  struct n *gauche, *droite;
} noeud_t ;
*/



typedef struct Arbre{
	signed char cle;
	struct  Arbre *ag;
	struct  Arbre *ad;
} Arbre, *pArbre;

typedef Arbre *pArbre; 


Arbre  *ajouter_noeud (Arbre *a, Arbre *n)
{
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->ag = ajouter_noeud (a->ag, n) ;
  else
	a->ad = ajouter_noeud (a->ad, n) ;
  return a ;  
}  




Arbre ajouter_cle (Arbre a, signed char cle)
{
  Arbre *n ;
  Arbre *b ;
  
  n = (Arbre *) malloc (sizeof(Arbre)) ;
  n->cle = cle;
  n->ag = NULL ;
  n->ad = NULL ;

  b = ajouter_noeud ((Arbre *)a, n) ;
  return b ;
}



Abr_t fusion(Arbre a,Arbre b){
	Abr_t c = NULL;
	c=ajouter_cle(c,(a->cle) + (b->cle));
	c->ag = a;
	c->ad = b;
	return c;

}


void afficher_arbre (Arbre a)
{
  if (a != NULL)
      {
	//printf("g");
	afficher_arbre (a->ag) ;
	//printf("cle")
	printf (" %c ", a->cle) ;
	//printf (" %s ", a->nom) ;
	//printf("d");
	afficher_arbre (a->ad) ;
      }
  return ;
}

/*
 * 
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
	int j;
	
	for(i=0;i<nb_elem;i++){
		indmin = recherchemin(tab,nb_elem,i);
	
		echange(tab,i,indmin);
	}



}




//tri probas

//renvoi l' indice du min du tableau
int recherchemin2 (float *tab,int nb_elem,int i){
		
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
void echange2(float *tab,int i,int j ){
	float temp;	
	temp = tab[i];
	tab[i]=tab[j];
	tab[j]=temp;
	}

void tri2(float *tab,int nb_elem){
	int i;
	int indmin;
	int j;
	
	for(i=0;i<nb_elem;i++){
		indmin = recherchemin2(tab,nb_elem,i);
	
		echange2(tab,i,indmin);
	}



}



//elle "descent" la valeur restante (id est a partir de l'indice l ) la plus faible du tableau de probas dans le tableau d'arbre sous forme d'arbre
int descente(float *tab,int nb_elem,Abr_t *huffman, int l,int L){
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
* 
* */

int main (int argc , char *argv[]){
/*
	FILE* fic = NULL;
	int nb_elem;
	int nb_even;
	int i;
	int j;
	int l = 2 ;// indice repere sur tab 
	int L;//Longueur de huffman  de huffman
	int k = 1; //sert au calcul du nb d element de huffman car la fusion diminue ce nombre
	signed char tab[TAILLE_MAX];
	signed char copietab[TAILLE_MAX];//pour se souvenir de l'ordre initial copietab[0] est la probabilite de e0


	Arbre huffman[TAILLE_MAX];
	Arbre a;

	fic = fopen("entropie.txt","r");//on ouvre le fichier en lecture
	if (fic != NULL ){
		fscanf(fic,"%d",&nb_elem);//on recupere le nb d'elements indiquer au debut du fichier
		//printf("%d\n",nb_elem);
		if (nb_elem<TAILLE_MAX){
			for (i = 0 ; i<nb_elem ; i++){
				fscanf(fic,"%f",tab+i);//on recupere chaque element et on le met dans un tableau
				copietab[i]=tab[i];//on copie le tableau de probas

			}
		}else {printf("ERROR nb d'elements trop important");}
	fclose(fic);//on n'oublie pas de fermer le fichier

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
/*
	tri2(tab,nb_elem);//tableau de probas trie

	//initialisation du tableau d'arbre par les deux plus petit element de tableau de probas sous forme d'arbre	
	for(i=0;i<2;i++){
		a=NULL;
		a = ajouter_cle(a,tab[i]);
		huffman[i]=a;
		

	}
	//debug(huffman,2);
	
	
	huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
	L=1;//initialisationde la longueur de huffman 
	
	//debug(huffman,L);
	do{
	
	
		do{

			L = descente(tab,nb_elem,huffman,l,L);
			l++;//car on a desendu un element l indqiue donc l'element suivant
			
		}while((huffman[L-1]->cle)<=huffman[L-2]->cle);
		
		//debug(huffman,L);
		tri(huffman,L);//on tri 
		
	
		huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
		//debug(huffman,L);
	for (j=1;j<L-1;j++){
		huffman[j]=huffman[j+1];
	}

	L--;
	//debug(huffman,L);
	}while(l<nb_elem);
	
	
	//tout les element sont descendus on peu donc finir par tout fusionner sans oublier de trier a chaque fois 
	
	while (L!=1){
		tri(huffman,L);//on tri 
		
		huffman[0]=fusion(huffman[0],huffman[1]);//on fusionne les deux plus petit car tab est trie
		
	for (j=1;j<L-1;j++){
		huffman[j]=huffman[j+1];
	}
	L--;
	
	//debug(huffman,L);
	
	}






	//printf("ok285\n");
	
	printf("l'affichage s'effectue en ordre fils gauche noeud fils droit : \n");
	afficher_arbre(huffman[0]);
	



	}

*/
return 0;
}
