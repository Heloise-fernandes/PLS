#include <stdio.h>
#include <stdlib.h>

void initialiser_tab(unsigned char* tab){
	int i;
	for(i=0;i<256;i++){
		tab[i]=i;
	}
}

void MTF(FILE* fichier_src){
	FILE* fichier_dest = ouvertureFichierEcriture("apres_MTF");
	
	unsigned char tab[256];
	initialiser_tab(tab);
	char octet_lu,v;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int i,j;


	while(taille_octet == 1){
		
		i=0;
		while((tab[i]!=octet_lu) & (i<256)){
			i+=1;
		}
		v=tab[i];
		
		
		for(j=0;j<i;j++){
			tab[i-j]=tab[i-j-1];
		}
		tab[0]=v;
		putByte(fichier_dest,(unsigned char)(i));
		taille_octet = getByte(fichier_src,&octet_lu);
	}
	fermetureFichier(fichier_dest);
}


void unMTF(FILE* fichier_src){
	FILE* fichier_dest = ouvertureFichierEcriture("apres_unMTF");

	unsigned char tab[256];
	initialiser_tab(tab);
	char octet_lu,v;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int i,n;
	printf("%d ",taille_octet);
	while(taille_octet == 1){
		

		n=octet_lu;//indice de l'element a MTF
		v=tab[n];//element a MTV
		
		for(i=0;i<n;i++){
			tab[n-i]=tab[n-i-1];
		}
		tab[0]=(unsigned char)(v);
		putByte(fichier_dest,(unsigned char)(v));
		taille_octet = getByte(fichier_src,&octet_lu);
	}
	fermetureFichier(fichier_dest);
}
