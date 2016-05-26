#include <stdlib.h>
#include "binio.h"

// Exemple d'utilisation des fonctions d'accès au contenu à copier 
// pour lire la suite d'entiers à tranférer
// Principe similaire pour écrire la suite d'entiers à tranférer

#ifdef FROM_FILE

// Le contenu à traiter est dans un fichier 

FILE *fichier_a_lire;

void initialiser (void)
{
  fichier_a_lire = fopen ("fichier_de_contenu","r");
  if (fichier_a_lire == NULL)
    { 
    fprintf (stderr,
             "Echec de l'ouverture de fichier_de_contenu en lecture\n"
            );
    exit (EXIT_FAILURE);
    } 
}

int my_eof (binio_file_func_param_t f)
{
  int lu;
  
  lu = getc (f);
  if (lu != EOF) 
    {
    ungetc (lu,f);
    return 0;
    }
  else
    return 1;
}

#define my_get (binio_fgetc_t *) fgetc
#define my_param (binio_file_func_param_t) fichier_a_lire

#define MESSAGE "d'un fichier : fichier_de_contenu"

#else

// Le contenu à traiter est dans un tableau

char tableau_a_lire[] = "une chaîne terminee par 0";
int indice;

void initialiser (void)
{
  indice = 0;
}

bool fin_tableau (char t[])
{
  return  (indice >=0) && (t[indice] == 0);
}

int lire_tableau (char t[])
{
  int lu;
  indice++;
  lu = t[indice];
  return lu;
}

#define my_get (binio_fgetc_t *) lire_tableau
#define my_eof (binio_eof_t *) fin_tableau
#define my_param (binio_file_func_param_t) tableau_a_lire

#define MESSAGE "d'une chaine dans un tableau"

#endif

binio_t in;

void ouvrir (bool msb_first)
{
  initialiser ();
  printf ("my_param = %p, feof = %d\n", my_param, feof(my_param));
  in =  binio_read_open (my_get,
                         my_eof,
                         my_param,
                         1);
  if (in == NULL) 
    {
    fprintf (stderr, "Erreur binio_read_open\n");
    exit (EXIT_FAILURE);
    }
} 


// Pour simplifier, la fermeture du fichier de flux n'est pas geree

int main (void)
{
  binio_error_t errcode;
  unsigned long v;

  fprintf (stderr, "Lecture sur 4 bits du contenu %s\n",MESSAGE);

  ouvrir (1);
  while (1) {
    errcode = binio_unsigned_read (in,&v,4,0);
    switch (errcode) {

      case BINIO_OK : printf ("Lu sur 4 bits : %lx\n",v); break;

      case BINIO_EOF : printf ("Fin du contenu\n"); 
                       exit (EXIT_SUCCESS);

      default : fprintf (stderr,"Erreur lors de la lecture du flux binaire\n");
                exit (EXIT_FAILURE);
                
      }
  }
  return 0;
}
