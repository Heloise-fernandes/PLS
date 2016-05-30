/*
 * 
 * huffman_liste.h
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "anlyseTexte.h"
#include "arbre.h"
#include "Lecture_Ecriture_B.h"

#ifndef HUFFMAN_LISTE_H
#define HUFFMAN_LISTE_H

/*Fonction  nb_element_nul
 * Paramètre :
 *     symb : un tableau d'entier
 * Return
 *     int : le nombre de case du tableau a zeros */
 int nb_element_nul(int *symb);


/*Fonction  huffman
 * Paramètre :
 *     chemin : le chemin du fichier à lire
 * Return
 *     pArbre : un arbre de huffman  */
pArbre huffman(char* chemin);

#endif

