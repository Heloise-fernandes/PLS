#include <stdio.h>
#include <stdlib.h>

#include "Lecture_Ecriture_B.c"

void RLE(FILE* fichier_src){
	FILE* fichier_dest = fopen("pretraitement","wb");

	char octet_lu;
	char precedent=NULL;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int n=1;
	
	while (taille_octet == 1){
		
		if (precedent!=octet_lu) putByte(fichier_dest,octet_lu);
		else n+=1;
		precedent=octet_lu;
		taille_octet = getByte(fichier_src,&octet_lu);
		if((n!=1)  &  ((precedent!=octet_lu)|(taille_octet!=1)|(n==257))){
			putByte(fichier_dest,precedent);
			putByte(fichier_dest,(char)(n-2));
			if (n==257) {putByte(fichier_dest,octet_lu);n=0;}
			else{n=1;}
		}
	}
	fclose(fichier_dest);
}


int main(){
	FILE* test = fopen("fichier_src","rb");
	RLE(test);
	printf("fin\n");
	fclose(test);
	return EXIT_SUCCESS;
}
