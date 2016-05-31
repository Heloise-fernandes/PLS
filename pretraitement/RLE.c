#include <stdio.h>
#include <stdlib.h>


void RLE(FILE* fichier_src,FILE* fichier_dest){

	char octet_lu;
	//char precedent=NULL;
	char precedent=' ';
	int taille_octet=getByte(fichier_src,&octet_lu);
	int n=1;
	
	int s=0;
	int i,j,k;
	int tab[127];
	for(i=0;i<128;i++) {tab[i]=1337;}
	i=0;
	
	while (taille_octet == 1){
		
		if (precedent!=octet_lu) {putByte(fichier_dest,octet_lu);}
		else {n+=1;}
		precedent=octet_lu;
		taille_octet = getByte(fichier_src,&octet_lu);
		if((n!=1)  &  ((precedent!=octet_lu)|(taille_octet!=1)|(n==129))){
			putByte(fichier_dest,precedent);
			if ((n==2)  &  (taille_octet==1)){
				if (s==0){
					j=1337;//valeur par defaut
					k=i;
					while((j==1337)&(k!=i+1)){
						if(tab[k]==octet_lu) {j=k-i-1;}
						k-=1;
						if(k==-1) {k=127;}
					}
					if (j>i) {j=1337;}
					if (j==1337){putByte(fichier_dest,(char)(0));}
					else{putByte(fichier_dest,(char)(j));
						precedent=octet_lu;
						taille_octet = getByte(fichier_src,&octet_lu);
					}s=1;
				}
				else {s=0;}
			}
			else{
				putByte(fichier_dest,(char)(n-2));
			}
			if (n==129) {putByte(fichier_dest,octet_lu);n=0;}
			else{n=1;}
		}
		tab[i]=precedent;
		i+=1;
		if(i==128){i=0;}
	}
}


void unRLE(FILE* fichier_src,FILE* fichier_dest){
	
	char octet_lu;
	char precedent=-1;
	int taille_octet=getByte(fichier_src,&octet_lu);
	
	int i,j;
	int tab[127];
	for(i=0;i<128;i++) {tab[i]=1337;}
	i=0;
	
	while(taille_octet == 1){
		
		if (octet_lu==precedent){
			taille_octet=getByte(fichier_src,&octet_lu);
			if (octet_lu<0) {
				putByte(fichier_dest,precedent);
				tab[i]=precedent;
				i+=1;
				if(i==128){i=0;}
				
				j=i+octet_lu;
				if(j<0) {j+=128;}
				
				putByte(fichier_dest,tab[j]);
				tab[i]=tab[j];
				i+=1;
				if(i==128){i=0;}
			}
			else{
				for(j=0;j<=octet_lu;j++){
					
					putByte(fichier_dest,precedent);
					tab[i]=precedent;
					i+=1;
					if(i==128){i=0;}
					
				}
			}
			precedent=-1;
		}
		else{
			
			putByte(fichier_dest,octet_lu);
			tab[i]=octet_lu;
			i+=1;
			if(i==128){i=0;}
			
			precedent=octet_lu;
		}
		taille_octet = getByte(fichier_src,&octet_lu);
	}	
}
