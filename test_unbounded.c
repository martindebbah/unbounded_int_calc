#include "unbounded_int.h"
#include <stdio.h>

int main(void) {
    char *c = unbounded_int2string(string2unbounded_int("12345"));
    printf("%s", c);
    return 0;
}
