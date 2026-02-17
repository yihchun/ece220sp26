#include <stdio.h>

int average(int *array, int len) {
    int accum = 0;
    int i;
    for (i=0; i<len; i++) {
        accum += array[i];
    }
    return accum/len;
}

int main() {
    int i = 0;
    int arr[10000];
    while (scanf("%d", arr+i))  /* &arr[i] */
        i++;
    printf("average of %d values is is %d\n", i, average(arr, i));

    /*
    float pi = 3.1415926535;
    float *p = &pi;
    char x,y,z,w;
    int *ptr = (int *)&y;
    x = 'x';
    y = 'y';
    z = 'z';
    printf("x=%c y=%c z=%c\n", x, y, z);
    *ptr = -1;

    printf("x=%c y=%c z=%c\n", x, y, z);
    return 0;
    */
}
