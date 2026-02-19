#include <stdio.h>

void stringcopy(char *dst, const char *src) {
    /* while (*dst++ = *src++) ; */
    while (*src) {
        *dst = *src;
        dst++; src++;
    }
}

char *stringfind(const char *haystack, char needle) {
    while (*haystack) {
        if (*haystack == needle)
            return (char *)haystack;
        haystack++;
    }
    return NULL;
}

int main() {
    char arr[16] = "Hi";
    char *oops = stringfind("Hello World", 'W');
    printf("%s %s\n", "Hello World", oops);
    *oops = '\0';
    printf("Hello World");
    
    /*    printf("%s\n", arr);
    stringcopy(arr, "Hello worldhlafdshiouadfwiuhaewrqihuaefwhiulafewihludfsahiluawef");
    printf("%s\n", arr);
    */
    
    return 0;
}
