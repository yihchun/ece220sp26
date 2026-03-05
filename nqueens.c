#include <stdio.h>
#include <strings.h>

#define N 12

int arr[N][N];
int ban[N][N];
int is_safe_square(int r, int c) {
    int i;
    for (i=0; i<N; i++) {
        if (arr[r][i]) return 0;
        if (arr[i][c]) return 0;
        if ((r-c+i >= 0) && (r-c+i < N) && arr[r-c+i][i]) return 0;
        if ((c+r-i >= 0) && (c+r-i < N) && arr[c+r-i][i]) return 0;
    }
    return 1;
}

/* Place a queen on each row starting from next_row through N-1.
 * Returns 1 if possible, leaving arr solved,
 * or 0 if impossible, leaving arr undisturbed from the original call.
 */
int can_solve(int next_row) {
    int i, j, k;
    if (next_row == N) {
        for (i=0; i<N; i++) {
            for (j=0; !arr[i][j]; j++) ;
            for (k=0; !ban[i][k] && k<N; k++) ;
            if (k == N) return 1;
            if (j > k) return 1;
            if (j < k) return 0;
        }
        return 0;
    }
    /* see if we can place a queen in row next_row */
    for (i=0; i<N; i++) {
        if (!is_safe_square(next_row, i)) continue;
        arr[next_row][i] = 1;
        if (can_solve(next_row+1)) return 1;
        arr[next_row][i] = 0;
    }
    return 0;
}
    
int main() {
    int i,j,soln = 0;
    while (can_solve(0)) {
        printf("Solution %d\n", soln++);
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                printf("%c", "-Q"[arr[i][j]]);
            }
            printf("\n");
        }
        bcopy(arr, ban, sizeof(arr));
        bzero(arr, sizeof(arr));
    }
}
