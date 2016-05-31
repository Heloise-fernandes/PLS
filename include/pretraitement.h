
#ifndef PRETRAITEMENT_H
#define PRETRAITEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "Lecture_Ecriture_B.h"
#include "RLE.h"
#include "MTF.h"


//Fonctions de compression/decompression avec MTF puis RLE

void comp_MTF_RLE(FILE* fichier_src,FILE* fichier_dest);
void decomp_MTF_RLE(FILE* fichier_src,FILE* fichier_dest);

//Fonctions de compression/decompression avec RLE puis MTF

void comp_RLE_MTF(FILE* fichier_src,FILE* fichier_dest);
void decomp_RLE_MTF(FILE* fichier_src,FILE* fichier_dest);
#endif

