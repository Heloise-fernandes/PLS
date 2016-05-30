/*
 * Main
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>

/*#include "Lecture_Ecriture_B.h"
#include "package_merge.h"
#include "anlyseTexte.h"
#include "huffman_liste.h"
#include "huffman_part2.h"
*/
int main(int argc, char **argv)
{
	
	char* modeDEmploie = "\nNAME : Compression\n\nSYNOPSIS : \n	./compresser [OPTIONS] nomFichier \n\nDESCRIPTION : 	\n	-p\n		compression package merge sans prétraitement\n\n	-r,-m,-rm\n		compression avec prétraitement rle(r) ou mtf(m) ou rle et mtf (mr)\n\nExemple : ./compresser -p nomFichier, ./compresser -r nomFichier, ./compresser -p -m nomFichier\n\n";
	if(argc < 2)
	{
		printf("%s", modeDEmploie);
	}
	else if (argc == 2)
	{
		printf("Compression sans pretraitement avec huffman\n");
	}
	else if (argc < 5)
	{
		if(argc==3)
		{
			char* chemin = argv[2];
			if(strcmp("-p",argv[1])==0)
			{
				printf("Lancement  avec package merge\n");		
			}
			else if (strcmp("-m",argv[1])==0)
			{printf("Lancement avec prétraitement mtf \n");}
			else if (strcmp("-r",argv[1])==0)
			{printf("Lancement  avec prétraitement rle\n");}
			else if (strcmp("-mr",argv[1])==0)
			{printf("Lancement  prétraitement avec mtf et rel \n");}
			else{printf("%s",modeDEmploie);}
		}
		else
		{
			if (strcmp("-p",argv[1])==0)
			{
				if (strcmp("-m",argv[2])==0)
				{printf("Lancement codage package merge avec prétraitement mtf\n");}
				else if (strcmp("-r",argv[2])==0)
				{printf("Lancement  codage package merge avec prétraitement rle\n");}
				else if (strcmp("-mr",argv[2])==0)
				{printf("Lancement  codage package merge avec prétraitement mtf et rel\n");}
				else{printf("%s",modeDEmploie);}
			}
			else{printf("%s",modeDEmploie);}
		}
	}
	else
	{
		printf("%s",modeDEmploie);
	}
	
	return 0;
}
