#include <stdio.h>

void stringcopy(char *dst, const char *src) {
    /* while (*dst++ = *src++) ; */
    while (*src) {
        *dst = *src;
        dst++; src++;
    }
}

int main() {
    char arr[16] = "Hi";
    printf("%s\n", arr);
    stringcopy(arr, "Hello worldhlafdshiouadfwiuhaewrqihuaefwhiulafewihludfsahiluawef");
    printf("%s\n", arr);
    
    return 0;
}
