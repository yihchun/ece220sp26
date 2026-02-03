#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

int main() {
    int x = -1;
    unsigned int u = -1;
    int a = 3;
#ifdef DEBUG
    printf("x >> 1 is %x\n", x>>1);
    printf("%x >> 1 is %x\n", u, u>>1);
    printf("-7%%2 = %d\n", -7%2);
#endif
    printf("%d\n", a++);
    if (x = 3) {
        printf("x is %d\n", x);
    }
    printf("max of 5,7 is %d\n", MAX(2+3,4+3));
    return 0;
}
