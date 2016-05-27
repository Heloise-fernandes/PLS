#include <stdio.h>
#include <stdlib.h>

#include "Lecture_Ecriture_B.c"


void RLE(FILE* fichier_src){
	FILE* fichier_dest = ouvertureFichierEcriture("apres_RLE");

	char octet_lu;
	char precedent=NULL;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int n=1;
	
	while (taille_octet == 1){
		
		if (precedent!=octet_lu) {putByte(fichier_dest,octet_lu);}
		else {n+=1;}
		precedent=octet_lu;
		taille_octet = getByte(fichier_src,&octet_lu);
		if((n!=1)  &  ((precedent!=octet_lu)|(taille_octet!=1)|(n==257))){
			putByte(fichier_dest,precedent);
			putByte(fichier_dest,(unsigned char)(n-2));
			if (n==257) {putByte(fichier_dest,octet_lu);n=0;}
			else{n=1;}
		}
	}
	fclose(fichier_dest);
}


void unRLE(FILE* fichier_src){
	FILE* fichier_dest = ouvertureFichierEcriture("apres_unRLE");
	
	char octet_lu;
	char precedent=NULL;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int i,n;
	
	while(taille_octet == 1){
		if (octet_lu==precedent){
			taille_octet=getByte(fichier_src,&octet_lu);
			n=octet_lu;
			if (n<0) n+=256;
			for(i=0;i<=n;i++){
				putByte(fichier_dest,precedent);
			}
		}
		else{
			putByte(fichier_dest,octet_lu);
		}
		precedent=octet_lu;
		taille_octet = getByte(fichier_src,&octet_lu);
	}
}



int main(){
	FILE* test = ouvertureFichierLecture("fichier_src");
	RLE(test);
	fclose(test);
	test = ouvertureFichierLecture("apres_RLE");
	unRLE(test);
	fclose(test);
	return EXIT_SUCCESS;
}
