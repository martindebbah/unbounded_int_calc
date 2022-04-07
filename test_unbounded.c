#include <stdio.h>
#include "unbounded_int.h"

int main(void) {
    // Tests à faire pour chaque fonction !

    unbounded_int a = string2unbounded_int("999");
    unbounded_int b = string2unbounded_int("9");
    unbounded_int sum = somme_pos(a, b);
    printf("%s\n", unbounded_int2string(sum));

    return 0;
}
