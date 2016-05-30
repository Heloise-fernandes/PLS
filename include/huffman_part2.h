



//fonction auxiliaire pour generation description arbre
void generation_description_arbre_aux (pArbre A, FILE* F, char size, int indice, char * T);

// apartir d'un arbre A ecrit dans un fichier la description de l'arbre
void generation_description_arbre (pArbre A,char* T,FILE *F);

//cree un tableau t avec le code pour chaque symbole
//PB il faudrait mettre la taille du fichier et la description de l'arbre avant !
void generation_code (pArbre A, int *t, int s);

//code un fichier a partir de l'arbre A
void Transcodage (pArbre A, FILE* fLecture,FILE * fEcriture ,char* Longueur);
//indique si il reste des feuille sans cle dans l'arbre
int place (pArbre A);
//affiche un tableau
void afficherT (int T[]);
//calcule la valeur maximum d'un tableau T et retourne l'indice de cette valeur
int max( int  T[]){
int min( int  T[]);






//contruit l'arbre canonique a partir d'un tableau T avec la longueur de chaque symbole dans l'arbre
pArbre construction_arbre_canonique (int T[] );
void decodage_texte (FILE * fLecture,FILE* fEcriture,pArbre A,int taille);
void codage (FILE *fLecture, FILE* fEcriture, pArbre A, int taille);
void decodage (FILE *fLecture, FILE* fEcriture);
