#include <stdio.h>
#include "unbounded_int.h"

int main(void) {

    // Tests pour chaque fonction :

    // string2unbounded
    printf("Fonction unbounded_int string2unbounded_int(const char *s)\n");
    unbounded_int a = string2unbounded_int("223");
    printf("-> unbounded_int a = string2unbounded_int(\"223\")\n");
    unbounded_int b = string2unbounded_int("0000");
    printf("-> unbounded_int b = string2unbounded_int(\"0000\")\n");
    printf("\n");

    // ll2unbounded
    printf("Fonction unbounded_int ll2unbounded_int(long long i)\n");
    unbounded_int c = ll2unbounded_int(528);
    printf("-> unbounded_int c = ll2unbounded_int(528)\n");
    unbounded_int d = ll2unbounded_int(-48);
    printf("-> unbounded_int d = ll2unbounded_int(-48)\n");
    printf("\n");

    // unbounded2string
    printf("Fonction char *unbounded_int2string(unbounded_int a)\n");
    printf("print unbounded_int2string(a) : %s\n", unbounded_int2string(a));
    printf("print unbounded_int2string(b) : %s\n", unbounded_int2string(b));
    printf("print unbounded_int2string(c) : %s\n", unbounded_int2string(c));
    printf("print unbounded_int2string(d) : %s\n", unbounded_int2string(d));
    printf("\n");

    // cmp
    printf("Fonction int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b)\n");
    printf("(= int unbounded_int_cmp_ll(unbounded_int a, long long b))\n");
    printf("print cmp(a, b) : %d\n", unbounded_int_cmp_unbounded_int(a, b));
    printf("print cmp(b, a) : %d\n", unbounded_int_cmp_unbounded_int(b, a));
    printf("print cmp(a, 223) : %d\n", unbounded_int_cmp_ll(a, 223));
    printf("\n");

    // Somme
    printf("Fonction unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b)\n");
    printf("a + b = %s\n", unbounded_int2string(unbounded_int_somme(a, b))); 
    printf("valeur attendue : %d\n",223 + 0);
    printf("a + c = %s\n", unbounded_int2string(unbounded_int_somme(a, c)));
    printf("valeur attendue : %d\n",223 + 528);
    printf("a + d = %s\n", unbounded_int2string(unbounded_int_somme(a, d)));
    printf("valeur attendue : %d\n",223 + (-48));
    printf("\n");

    // Différence
    printf("Fonction unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b)\n");
    printf("a - b = %s\n", unbounded_int2string(unbounded_int_difference(a, b)));
    printf("valeur attendue : %d\n",223 - 0);
    printf("a - c = %s\n", unbounded_int2string(unbounded_int_difference(a, c)));
    printf("valeur attendue : %d\n",223 - 528);
    printf("a - d = %s\n", unbounded_int2string(unbounded_int_difference(a, d)));
    printf("valeur attendue : %d\n",223 - (-48));
    printf("\n");

    // Produit
    printf("Fonction unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b)\n");
    printf("a * b = %s\n", unbounded_int2string(unbounded_int_produit(a, b)));
    printf("valeur attendue : %d\n",223 * 0);
    printf("a * c = %s\n", unbounded_int2string(unbounded_int_produit(a, c)));
    printf("valeur attendue : %d\n",223 * 528);
    printf("a * d = %s\n", unbounded_int2string(unbounded_int_produit(a, d)));
    printf("valeur attendue : %d\n",223 * (-48));
    printf("\n");

    return 0;
}
