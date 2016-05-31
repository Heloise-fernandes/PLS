#ifndef MTF_H
#define MTF_H

#include <stdio.h>
#include <stdlib.h>
#include "Lecture_Ecriture_B.h"


void initialiser_tab(char* tab);

void MTF(FILE* fichier_src,FILE* fichier_dest);

void unMTF(FILE* fichier_src,FILE* fichier_dest);

#endif
