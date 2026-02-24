#include <stdio.h>

#define N 5

/* .. .. ..| .. .. ..| .. .. ..
 * ^ X (MSB)     ^ O (LSB)
 */
#define HORIZONTAL_WIN (1+4+16)
#define VERTICAL_WIN   (1+(1<<6)+(1<<12))
#define DOWNRIGHT_WIN  (1+(1<<8)+(1<<16))
#define DOWNLEFT_WIN   ((1<<4)+(1<<8)+(1<<12))

int main() {
    /* tic tac toe */
    int board = 0;
    /* turn 0 == O, turn 1 == X, win 0 == no one won, win 1 == winner */
    int i, j, val, in, turn = 1, win = 0, count;
    
    for (count=0; ; count++) {
        for (i=0; i<9; i++) {
            switch ((board>>(i*2)) & 0x3) {
            case 0: printf("%d ", i); break;
            case 1: printf("O "); break;
            case 2: printf("X "); break;
            default: printf("??");
            }
            if (i%3 == 2) printf("\n");
        }
        printf("\n");
        if (win || count == 9) break;
        scanf("%d", &in);
        if (((board>>(in*2)) & 3) == 0) {
            board += 1<<(in*2+turn);
            turn = !turn;
        }
        for (i=0;i<3;i++) {
            if (!((~board) & (HORIZONTAL_WIN << (i*6))) ||
                !((~board) & (HORIZONTAL_WIN << (i*6+1))) ||
                !((~board) & (VERTICAL_WIN   << (i*2))) ||
                !((~board) & (VERTICAL_WIN   << (i*2+1)))) {
                win = 1;
                break;
            }
        }
        if (!((~board) & (DOWNLEFT_WIN)) ||
            !((~board) & (DOWNLEFT_WIN << 1)) ||
            !((~board) & (DOWNRIGHT_WIN)) ||
            !((~board) & (DOWNRIGHT_WIN << 1)))
            win = 1;
            
    }
    if (win && turn) printf("O wins\n");
    else if (win && !turn) printf("X wins\n");
    else printf("Tie!\n");
        
    
#if 0
    /* print an nxn identity matrix */
    int row, col;
    for (row = 0; row < N; row++) { /* iterate over rows */
        for (col = 0; col < N; col++) {
            if (row == col) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
#endif

#if 0
    /* unscheduled excursion into integer type sizes */
    char x = 256;
    short y;
    int16_t i;
    printf("char %d int %d short %d long %d long long %d i %d\n",
           sizeof(char), sizeof(int), sizeof(short), sizeof(long),
           sizeof(long long), sizeof(i));
    if (x) {
        printf("X is true\n");
    } else {
        printf("x is false\n");
    }
#endif
    return 0;
}
