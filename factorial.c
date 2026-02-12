#include <stdio.h>

int multiply(int a, int b) {
    return a*b;
}

int fact(int a) {
    int i, accum;
    accum = 1;
    for (i=a; i; i--) {
        accum = multiply(accum, i);
    }
    return accum;
}

void swap(int a, int b) {
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
    return;
}

int main() {
    int x = 5;
    int y = 3;
    printf("5! = %d\n", fact(5));
    swap(x,y);
    printf("%d %d\n", x, y);
    return 0;
}
