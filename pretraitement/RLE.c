#include <stdio.h>
#include <stdlib.h>


void RLE(FILE* fichier_src,FILE* fichier_dest){

	char octet_lu;
	char precedent;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int n=1;

	while (taille_octet == 1){
		
		if(n==1) putByte(fichier_dest,octet_lu);
		precedent=octet_lu;
		taille_octet=getByte(fichier_src,&octet_lu);
		
		if((octet_lu==precedent)&(taille_octet == 1)) {n+=1;}
		else {
			if(n!=1){
				putByte(fichier_dest,precedent);
				putByte(fichier_dest,n-2);
			}
			n=1;
		}
	}
}


void unRLE(FILE* fichier_src,FILE* fichier_dest){
	
	char octet_lu;
	char precedent;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int i;
	
	while (taille_octet == 1){
		
		putByte(fichier_dest,octet_lu);
		if((octet_lu==precedent)&(taille_octet == 1)){
			taille_octet=getByte(fichier_src,&octet_lu);
			for(i=0;i<octet_lu;i++){putByte(fichier_dest,precedent);}
			precedent=-1;
		}

		precedent=octet_lu;
		taille_octet=getByte(fichier_src,&octet_lu);
	}
}
