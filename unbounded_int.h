#ifndef UNBOUNDED_H
#define UNBOUNDED_H

typedef struct chiffre {
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
}chiffre;

typedef struct {
    char signe;
    size_t len;
    chiffre *premier;
    chiffre *dernier;
}unbounded_int;

unbounded_int string2unbounded_int(const char *e);

char *unbounded_int2string(unbounded_int i);

#endif
