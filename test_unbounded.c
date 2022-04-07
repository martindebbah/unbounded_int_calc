#include <stdio.h>
#include "unbounded_int.h"

int main(void) {
    unbounded_int a = string2unbounded_int("3");
    unbounded_int b = string2unbounded_int("-12");
    printf("%d\n", unbounded_int_cmp_unbounded_int(a, b));
    return 0;
}
