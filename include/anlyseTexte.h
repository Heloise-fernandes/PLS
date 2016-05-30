//anlyseTexte.h

//initialise par la valeur 0 les cases du tableau 
void initialiser_tableau_poids_symbole(int* symb );

//affiche pour chaque symbole  le couple (symbole , nombre d'occurences )
//les lettres et les chiffres sont affiches sous formes de char 
//les autres caracteres ont affichs sous forme d'entier
void afficher_tableau_poids_symbole(int* symb );

//renvoi la taille en octet max 4Milliard .
//lit le fichier a compresser et incrementes le nombre d'occurence du symbole lu
int remplir_tableau_poids_symbole_et_calcul_taille(int* symb,FILE* fichier_a_compresser);

//fonction principal qui appelle les autres 
int analyse_fichier_a_compresser(int* symb,FILE* fichier_a_compresser );
