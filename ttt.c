#include <stdio.h>

#define INDEX(i,j) ((i)*3+(j))
#define X 1
#define O -1

/* returns who won, 0 if no one won */
int did_win(const int *board) {
    int i, j, accumh, accumv, accumur, accumdr;
    accumur = accumdr = 0;
    for (i=0; i<3; i++) {
        accumh = 0;
        accumv = 0;
        for (j=0; j<3; j++) {
            accumh += board[INDEX(i,j)];
            accumv += board[INDEX(j,i)];
        }
        if (accumh == (3*X) || accumv == (3*X)) return X;
        if (accumh == (3*O) || accumv == (3*O)) return O;
        accumdr += board[INDEX(i,i)];
        accumur += board[INDEX(2-i,i)];
    }
    if (accumur == (3*X) || accumdr == (3*X)) return X;
    if (accumur == (3*O) || accumdr == (3*O)) return O;
    return 0;
}

void print_board(const int *board) {
    int i,j ;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            printf("%c", "O-X"[board[INDEX(i,j)]+1]);
        }
        printf("\n");
    }
}

int main() {
    int board[3][3] = {0};
    int i,j,turn;
    turn = X;
    while (!did_win(board)) {
        scanf("%d %d", &i, &j);
        if (!board[i][j]) {
            board[i][j] = turn;
            turn = -turn;
        }
        print_board(board);
    }

}
