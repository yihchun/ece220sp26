#include <stdio.h>

/* take farenheight -> celcius */

int main() {
    float f, c;
    char x;
    printf("Enter a temperature in 19th century measurements> ");
    while (!scanf("%f", &f)) {
        scanf("%c", &x);
        printf("I needed a number dawg, not this %c business\n", x);
    }
        c = (f-32)*(5.0/9.0);
        printf("%.1f F is what the rest of the world calls %.1f C\n", f, c);
    return 0;
}
