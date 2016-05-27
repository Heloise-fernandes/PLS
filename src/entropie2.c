#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE_MAX 256
/*

format du fichier 

nom obligatoire : "entropie.txt"

contenu du fichier :

nb d'elements N (int < TAILLE_MAX)
elem1 (double)
elem2 (double)
...
elem N (double)

attention le resultat n'est pas garentie en cas de fichier incorrect
*/

/*
compilation 

gcc entropie.c -lm -o entropie

execution

./entropie


*/

int main (int argc , char *argv[]){
	FILE* fic = NULL;
	int nb_elem;
	int i;
	int tab[TAILLE_MAX];
	float entropie = 0.0;

	fic = fopen("entropie.txt","r");//on ouvre le fichier en lecture
	if (fic != NULL ){
		fscanf(fic,"%d",&nb_elem);//on recupere le nb d'elements indiquer au debut du fichier
		//printf("%d\n",nb_elem);
		for (i = 0 ; i<nb_elem ; i++){
			fscanf(fic,"%f",tab+i);//on recupere chaque element et on le met dans un tableau
			entropie+=tab[i]*(log2((1/tab[i])));//on calcule l'entropie partielle. A la fin de la boucle entropie contiendra la valeur final
			//printf("entropie partielle = %f",entropie);
			//printf("%f\n",tab[i]);

		}

	fclose(fic);//on n'oublie pas de fermer le fichier
	printf("entropie %f :",entropie);//on affiche le resultat 
	}

	

return 0;
}