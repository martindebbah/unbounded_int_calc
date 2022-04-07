#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "unbounded_int.h"

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
    char *str = malloc(sizeof(char) * i.len);
    chiffre *current = i.premier;
    for (int j = 0; j < i.len; j++) {
        str[j] = current -> c;
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

unbounded_int somme_pos(unbounded_int a, unbounded_int b) {
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
