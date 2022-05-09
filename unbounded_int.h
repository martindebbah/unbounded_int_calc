#ifndef UNBOUNDED_INT_H
#define UNBOUNDED_INT_H

// Structure d'un chiffre (contient un char et pointe vers le suivant et le précédent)
typedef struct chiffre {
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
}chiffre;

// Liste doublement chaînée pointant vers le début et la fin
typedef struct {
    char signe;
    size_t len;
    chiffre *premier;
    chiffre *dernier;
}unbounded_int;


// Renvoie un unbounde_int qui représente la chaîne de caractères passée en argument
unbounded_int string2unbounded_int(const char *e);

// Renvoie un unbounded_int qui représente le long long passé en argument
unbounded_int ll2unbounded_int(long long i);

// Renvoie une chaîne de caractères qui représente l'unbounded_int passé en argument
char *unbounded_int2string(unbounded_int i);

// Renvoie -1 si a < b, 0 si a == b ou 1 si a > b (a et b les deux unbounded_int passés en arguments)
int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);

// Renvoie -1 si a < b, 0 si a == b ou 1 si a > b (a et b respectivement l'unbounded_int et le long long passés en arguments)
int unbounded_int_cmp_ll(unbounded_int a, long long b);

// Renvoie un unbounded_int qui représente la somme des deux unbounded_int passés en arguments
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);

// Renvoie un unbounded_int qui représente la différence des deux unbouded_int passés en arguments
unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b);

// Renvoie un unbounded_int qui représente le produit des deux unbounded_int passés en arguments
unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);

#endif
