#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "unbounded_int.h"

// Fonction auxiliaire pour la somme (a >= 0 et b >= 0)
static unbounded_int somme_pos(unbounded_int a, unbounded_int b);

// Fonction auxiliaire pour la différence (0 < b < a)
static unbounded_int diff_pos(unbounded_int a, unbounded_int b);

unbounded_int string2unbounded_int(const char *e) {
    unbounded_int *entier = malloc(sizeof(unbounded_int));
    int len = 0;
    int i = 0;
    if (e[i] < '0' || e[i] > '9') {
        if (e[i] == '-') {
            entier -> signe = '-';
            i++;
        }else {
            entier -> signe = '*';
        }
    }else {
        entier -> signe = '+';
    }
    entier -> premier = malloc(sizeof(chiffre));
    chiffre *current = entier -> premier;
    entier -> dernier = NULL;
    while (e[i] != '\0') {
        current -> c = e[i];
        current -> precedent = entier -> dernier;
        current -> suivant = malloc(sizeof(chiffre));
        entier -> dernier = current;
        len++;
        current = current -> suivant;
        i++;
    }
    free(current -> suivant);
    current -> suivant = NULL;
    entier -> len = len;
    return *entier;
}

unbounded_int ll2unbounded_int(long long i) {
    unbounded_int *entier = malloc(sizeof(unbounded_int));
    int len = 1;
    if (i < 0) {
        entier -> signe = '-';
    }else {
        entier -> signe = '+';
    }
    int n = i % 10;
    i /= 10;
    entier -> dernier = malloc(sizeof(chiffre));
    entier -> premier = entier -> dernier;
    chiffre *current = entier -> dernier;
    current -> c = (char) (n + '0');
    while (i != 0) {
        n = i % 10;
        i /= 10;
        len++;
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;
        current -> c = (char) (n + '0');
        entier -> premier = current;
    }
    entier -> len = len;
    return *entier;
}

char *unbounded_int2string(unbounded_int i) {
    char *str;
    int index = 0;
    int len = i.len;
    if (i.signe == '-') {
        str = malloc(sizeof(char) * len + 1);
        str[index] = '-';
        index++;
        len++;
    }else {
        str = malloc(sizeof(char) * len);
    }
    chiffre *current = i.premier;
    for (; index < len; index++) {
        str[index] = current -> c;
        current = current -> suivant;
    }
    return str;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    if (a.signe == '-') { // Si a est négatif
        if (b.signe == '+') { // Si b est positif : a < b (-1 < 1)
            return -1;
        } // Sinon b est positif
        if (a.len > b.len) { // Si a est plus long que b : a < b (-10 < -1)
            return -1;
        }
        if (a.len < b.len) { // Si a est plus court que b : a > b (-1 > -10)
            return 1;
        }
        // a et b font la même taille on compare chaque chiffre en partant de la gauche
        chiffre *pta = a.premier;
        chiffre *ptb = b.premier;
        while (pta -> suivant != NULL) {
            if (pta -> c < ptb -> c) { // Si pta < ptb : a > b (-2 > -5)
                return 1;
            }
            if (pta -> c > ptb -> c) { // Si pta > ptb : a < b (-5 > -2)
                return -1;
            }
            pta = pta -> suivant;
            ptb = ptb -> suivant;
        }
        return 0; // a == b
    } // Sinon a est positif
    if (b.signe == '-') { // Si b est négatif : a > b (1 > -1)
        return 1;
    } // Sinon b est positif
    if (a.len > b.len) { // Si a est plus long que b : a > b (10 > 1)
        return 1;
    }
    if (a.len < b.len) { // Si a est plus court que b : a < b (1 < 10)
        return -1;
    }
    // Sinon a et b font la même taille on compare chaque chiffre en partant de la gauche
    chiffre *pta = a.premier;
    chiffre *ptb = b.premier;
    while (pta -> suivant != NULL) {
        if (pta -> c < ptb -> c) { // Si pta < ptb : a < b (2 < 5)
            return -1;
        }
        if (pta -> c > ptb -> c) { // Si pta > ptb : a > b (5 > 2)
            return 1;
        }
        pta = pta -> suivant;
        ptb = ptb -> suivant;
    }
    return 0; // a == b
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    return unbounded_int_cmp_unbounded_int(a, ll2unbounded_int(b));
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    int cmpa = unbounded_int_cmp_ll(a, 0);
    int cmpb = unbounded_int_cmp_ll(b, 0);
    if (cmpa >= 0 && cmpb >= 0) { // a, b >= 0 -> a + b
        return somme_pos(a, b);
    }else if (cmpa <= 0 && cmpb <= 0) { // a, b <= 0 -> -(|a| + |b|)
        unbounded_int sum = somme_pos(a, b);
        sum.signe = '-';
        return sum;
    }else if (cmpa >= 0 && cmpb < 0) { // a >= 0 et b < 0 -> a - |b|
        b.signe = '+';
        return unbounded_int_difference(a, b);
    }else { // a < 0 et b >= 0 -> b - |a|
        a.signe = '+';
        return unbounded_int_difference(b, a);
    }
}

unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b) {
    int cmpa = unbounded_int_cmp_ll(a, 0);
    int cmpb = unbounded_int_cmp_ll(b, 0);
    int cmp = unbounded_int_cmp_unbounded_int(a,b);
    if (cmpa >= 0 && cmpb >= 0) { // a, b >= 0 -> a - b
        if (cmp >= 0) {
            return diff_pos(a, b);
        }else {
            unbounded_int diff = diff_pos(b, a);
            diff.signe = '-';
            return diff;
        }
    }else if (cmpa <= 0 && cmpb <= 0) { // a, b <= 0 -> |b| - |a|
        if (cmp >= 0) {
            return diff_pos(b, a);
        }else {
            unbounded_int diff = diff_pos(a, b);
            diff.signe = '-';
            return diff;
        }
    }else if (cmpa >= 0 && cmpb < 0) { // a >= 0 et b < 0 -> a + |b|
        b.signe = '+';
        return unbounded_int_somme(a, b);
    }else { // a < 0 et b >= 0 -> -(b + |a|)
        a.signe = '+';
        unbounded_int diff = unbounded_int_somme(b, a);
        diff.signe = '-';
        return diff;
    }
}

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b) {
    chiffre *pta = a.dernier;
    chiffre *ptb = b.dernier;
    unbounded_int *produit = malloc(sizeof(unbounded_int));
    produit -> premier = malloc(sizeof(chiffre));
    produit -> dernier = produit -> premier;
    int len = a.len + b.len;
    int r;
    int v;
    chiffre *current = produit -> premier;
    current -> precedent = NULL;
    for (int i = 0; i < len; i++) { // Initialisation du unbounded_int
        current -> c = '0';
        current -> suivant = malloc(sizeof(chiffre));
        current -> suivant -> precedent = current;
        current = current -> suivant;
    }
    current = current -> precedent;
    current -> suivant = NULL;
    produit -> dernier = current;
    chiffre *tmp = current;
    while (ptb != NULL) {
        r = 0;
        if (ptb -> c == '0') {
            ptb = ptb -> precedent;
            tmp = tmp -> precedent;
            current = tmp;
            continue;
        }
        pta = a.dernier;
        while (pta != NULL) {
            v = (current -> c - '0') + (pta -> c - '0') * (ptb -> c - '0') + r;
            current -> c = (char)((v % 10) + '0');
            r = v / 10;
            current = current -> precedent;
            pta = pta -> precedent;
        }
        current -> c = (char)(r + '0');
        ptb = ptb -> precedent;
        tmp = tmp -> precedent;
        current = tmp;
    }
    produit -> len = len;
    if (a.signe == b.signe) {
        produit -> signe = '+';
    }else {
        produit -> signe = '-';
    }
    // On enlève les 0 du début
    while (produit -> premier -> c == '0') {
        if (produit -> len == 1) {
            break;
        }
        produit -> premier = produit -> premier -> suivant;
        produit -> premier -> precedent = NULL;
        produit -> len--;
    }
    return *produit;
}

static unbounded_int somme_pos(unbounded_int a, unbounded_int b) {
    chiffre *pta = a.dernier;
    chiffre *ptb = b.dernier;
    unbounded_int *sum = malloc(sizeof(unbounded_int));
    int len = 0;
    int r = 0;
    int n;
    sum -> premier = malloc(sizeof(chiffre));
    sum -> dernier = sum -> premier;
    chiffre *current = sum -> dernier;
    while (pta != NULL && ptb != NULL) {
        n = (pta -> c - '0') + (ptb -> c - '0') + r;
        current -> c = (char) ((n % 10) + '0');
        r = n / 10;
        pta = pta -> precedent;
        ptb = ptb -> precedent;
        len++;
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;
        sum -> premier = current;
    }
    while (pta != NULL) {
        n = pta -> c - '0' + r;
        current -> c = (char) ((n % 10) + '0');
        r = n / 10;
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;
        sum -> premier = current;
        pta = pta -> precedent;
        len++;
    }
    while (ptb != NULL) {
        n = ptb -> c - '0' + r;
        current -> c = (char) ((n % 10) + '0');
        r = n / 10;
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;
        sum -> premier = current;
        ptb = ptb -> precedent;
        len++;
    }
    if (r == 0) {
        sum -> premier = sum -> premier -> suivant;
        sum -> premier -> precedent = NULL;
        free(current);
    }else {
        current -> c = (char) (r + '0');
        len++;
    }
    sum -> len = len;
    sum -> signe = '+';
    return *sum;
}


static unbounded_int diff_pos(unbounded_int a, unbounded_int b) {
    chiffre *pta = a.dernier;
    chiffre *ptb = b.dernier;
    unbounded_int diff;
    chiffre *current = malloc(sizeof(chiffre));
    current -> suivant = NULL;
    diff.dernier = current;
    diff.premier = malloc(sizeof(chiffre));
    int len = 0;
    int r = 0;
    int n = 0;
    int c;
    while (ptb != NULL) {
        n = (pta -> c - '0') - (ptb -> c - '0') + r;
        if (n >= 0) {
            c = n;
            r = 0;
        }else {
            c =n +10 ;
            r = -1;  
        }
        current -> c = (char) c +'0';
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;

        pta = pta -> precedent;
        ptb = ptb -> precedent;
        len++;
    }
    while(pta != NULL) {
        n = (pta -> c - '0' +r);

        if (n >= 0) {
            c = n;
            r = 0;
        }else {
            c = n+ 10;
            r = -1;  
            }
        pta = pta -> precedent;
        len++;
        current -> c = (char) c +'0' ;
        current -> precedent = malloc(sizeof(chiffre));
        current -> precedent -> suivant = current;
        current = current -> precedent;
    }

    diff.premier = current -> suivant;
    diff.premier -> precedent = NULL;
    diff.len = len;
    diff.signe = '+';
    // On enlève les 0 du début
    while (diff.premier -> c == '0') {
        if (diff.len == 1) {
            break;
        }
        diff.premier = diff.premier -> suivant;
        diff.premier -> precedent = NULL;
        diff.len--;
    }
    return diff;
}
