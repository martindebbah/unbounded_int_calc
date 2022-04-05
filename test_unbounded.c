#include <stdio.h>
#include "unbounded_int.h"

int main(void) {
    char *c = unbounded_int2string(string2unbounded_int("12345"));
    //printf("%s", c);
    int x = 52;
    x /= 10;
    printf("%d\n", x);
    return 0;
}
