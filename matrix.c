#include <stdio.h>


/*
 * Matrix transpose
 * Binary search
 */

void matrix_transpose(const int *a, int *b, int n, int m) {
    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            b[j*n+i] = a[i*m+j];
        }
    }
}

void show_matrix(const int *a, int n, int m) {
    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", a[i*m+j]);
        }
        printf("\n");
    }
}

int main() {
    int a[3][4] = {1,2,3,4, 5,6,7,8, 9,10,11,12};
    int b[4][3];
    matrix_transpose(a[0], b[0], 3, 4);
    show_matrix(a[0], 3,4);
    show_matrix(b[0], 4,3);
    return 0;
}
