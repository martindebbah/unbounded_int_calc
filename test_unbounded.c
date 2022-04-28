#include <stdio.h>
#include "unbounded_int.h"

int main(void) {
    // Tests à faire pour chaque fonction !

    unbounded_int a = string2unbounded_int("28");
    unbounded_int b = string2unbounded_int("28");
    unbounded_int sum = diff_pos(a, b);
    printf("%s\n", unbounded_int2string(sum));

    return 0;
}
