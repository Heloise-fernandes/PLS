#include <stdio.h>
#include <stdlib.h>

void initialiser_tab(char* tab){
	int i;
	for(i=0;i<256;i++){
		tab[i]=i-128;
	}
}

void MTF(FILE* fichier_src,FILE* fichier_dest){
	
	char tab[255];
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
		putByte(fichier_dest,(char)(i-128));
		taille_octet = getByte(fichier_src,&octet_lu);
	}
}


void unMTF(FILE* fichier_src,FILE* fichier_dest){

	char tab[255];
	initialiser_tab(tab);
	char octet_lu,v;
	int taille_octet=getByte(fichier_src,&octet_lu);
	int i,j,n;
	
	while(taille_octet == 1){

		n=octet_lu+128;//indice de l'element a MTF
		v=tab[n];//element a MTF
		
		i=0;
		while(tab[i]!=v){i+=1;}
		for(j=0;j<i;j++){
			tab[i-j]=tab[i-j-1];
		}
		
		tab[0]=(char)(v);
		putByte(fichier_dest,(char)(v));
		taille_octet = getByte(fichier_src,&octet_lu);
	}
}
