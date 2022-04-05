#include <stdlib.h>
#include <stddef.h>
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

char *unbounded_int2string(unbounded_int i) {
    char *str = malloc(sizeof(char) * i.len);
    chiffre *current = i.premier;
    for (int j = 0; j < i.len; j++) {
        str[j] = current -> c;
        current = current -> suivant;
    }
    return str;
}
