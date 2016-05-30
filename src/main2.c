/*
 * Main
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>

#include "Lecture_Ecriture_B.h"
#include "package_merge.h"
#include "anlyseTexte.h"
#include "huffman_liste.h"
#include "huffman_part2.h"

int main(int argc, char **argv)
{
	
	string modeDEmploie = "Le programme s'utilise comme suit : \n ./compresser nomFichier (Compression sans prétaitement avec Huffman)\n Posibilité d'ajouter les fonctions -p : \n ./compresser nomFichier : compression package merge sans prétraitement\n Posibilité d'ajouter les fonctions -r, -m, -mr : \n -r : prétraitement rle \n -m prétaitement mtf \n - mr : prétraitement rle et mtf\nExemple : ./compresser (-p) (-r/-m/-mr) nomFichier\n");
	if(argc < 2)
	{
		printf("%s", modeDEmploie);
	}
	else if (argc == 2)
	{
		printf("Compression sans pretraitement avec huffman");
	}
	else if (argc < 5)
	{
		if(argc==3)
		{
			string chemin = argv[2];
			if((strcmp("-p",argv[1]))||(strcmp("-m",argv[1]))||(strcmp("-r",argv[1]))||(strcmp("-mr",argv[1]))){printf("Lancement");}
			else{printf("%s",modeDEmploie);}
		}
		else
		{
			if((strcmp("-p",argv[1]))||(strcmp("-m",argv[2]))||(strcmp("-r",argv[2]))||(strcmp("-mr",argv[2]))){printf("Lancement");}
			else{printf("%s",modeDEmploie);}
		}
	}
	else
	{
		printf("%s",modeDEmploie);
	}
	
	return 0;
}
