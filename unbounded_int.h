#include <stddef.h>


//Structure d'un chiffre (char pointe vers suivant et precedent)
typedef struct chiffre {
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
}chiffre;
//Liste doublement chainee pointant vers debut et fin
typedef struct {
    char signe;
    size_t len;
    chiffre *premier;
    chiffre *dernier;
}unbounded_int;


/*renvoi la structure int qui represnete la chaine de charactere en argument*/
unbounded_int string2unbounded_int(const char *e);


/*renvoi la structure int qui represnete le long donné en argument*/
unbounded_int ll2unbounded_int(long long i)


/*renvoi la chaine de carctere representant l'entier en argumet*/
char *unbounded_int2string(unbounded_int i);


/*Compare deux entier (renvoi -1,0,1 si a <,==,> à b,respectivement)*/
int unbounded_int_cmp_unbounded_int(unbounded_it a, unbounded_int b);


/*meme chose que la precedente mais compare avec un long ? */
int unbounded_int_cmp_ll(unbounded_int a, long long b);


/*renvoi la representation de la somme des deux entiers*/
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);

/*renvoi la representation de la difference*/
unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b);


/*renvoi la representation du produit des deux entiers en parametres*/
unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);
