#include <stdio.h>
#include <stdlib.h>

#include "Lecture_Ecriture_B.c"
#include "RLE.c"
#include "MTF.c"



int main(){
	FILE* test = ouvertureFichierLecture("fichier_src");
	MTF(test);
	fclose(test);
	
	test = ouvertureFichierLecture("apres_MTF");
	RLE(test);
	fclose(test);

	test = ouvertureFichierLecture("apres_RLE");
	unRLE(test);
	fclose(test);

	test = ouvertureFichierLecture("apres_unRLE");
	unMTF(test);
	fclose(test);
	
	return EXIT_SUCCESS;
}
