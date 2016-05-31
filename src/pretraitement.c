#include <stdio.h>
#include <stdlib.h>

#include "Lecture_Ecriture_B.h"
#include "RLE.h"
#include "MTF.h"


//Fonctions de compression/decompression avec MTF puis RLE

void comp_MTF_RLE(FILE* fichier_src,FILE* fichier_dest){
	FILE* tmp=ouvertureFichierEcriture("tmp");
	MTF(fichier_src,tmp);
	fclose(tmp);
	tmp=ouvertureFichierLecture("tmp");
	RLE(tmp,fichier_dest);
	fclose(tmp);
	remove("tmp");
}
void decomp_MTF_RLE(FILE* fichier_src,FILE* fichier_dest){
	FILE* tmp=ouvertureFichierEcriture("tmp2");
	unRLE(fichier_src,tmp);
	fclose(tmp);
	tmp=ouvertureFichierLecture("tmp2");
	unMTF(tmp,fichier_dest);
	fclose(tmp);
	remove("tmp2");
}


//Fonctions de compression/decompression avec RLE puis MTF

void comp_RLE_MTF(FILE* fichier_src,FILE* fichier_dest){
	FILE* tmp=ouvertureFichierEcriture("tmp");
	RLE(fichier_src,tmp);
	fclose(tmp);
	tmp=ouvertureFichierLecture("tmp");
	MTF(tmp,fichier_dest);
	fclose(tmp);
	remove("tmp");
}
void decomp_RLE_MTF(FILE* fichier_src,FILE* fichier_dest){
	FILE* tmp=ouvertureFichierEcriture("tmp2");
	unMTF(fichier_src,tmp);
	fclose(tmp);
	tmp=ouvertureFichierLecture("tmp2");
	unRLE(tmp,fichier_dest);
	fclose(tmp);
	remove("tmp2");
}


//~ int main(){
	//~ FILE* src=ouvertureFichierLecture("fichier_src");
	//~ FILE* resultat=ouvertureFichierEcriture("resultat");
	//~ comp_MTF_RLE(src,resultat);
	//~ fclose(src);
	//~ fclose(resultat);
	//~ 
	//~ src=ouvertureFichierLecture("resultat");
	//~ resultat=ouvertureFichierEcriture("resultat2");
	//~ decomp_MTF_RLE(src,resultat);
	//~ return EXIT_SUCCESS;
//~ }
