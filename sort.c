#include <stdio.h>

void print_array(const int *arr, int len) {
    int i;
    for (i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubblesort(int *arr, int len) {
    int i, j, tmp;
    for (i=0; i<len; i++) {
        for (j=0; j<len-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
        print_array(arr, len);
    }
}

void insertsort(int *arr, int len) {
    /* repeat n times in loop index i
     * find the smallest element [i:len] swap it to arr[i]
     */
    int i, j, tmp, sm_idx;
    for (i=0; i<len; i++) {
        sm_idx = i;
        for (j=i+1; j<len; j++) {
            if (arr[j] < arr[sm_idx])
                sm_idx = j;
        }
        tmp = arr[i];
        arr[i] = arr[sm_idx];
        arr[sm_idx] = tmp;
        print_array(arr, len);
    }
}

#define ARR_LEN 20

int main() {
    FILE *fp = fopen("/dev/urandom", "r");
    int arr[ARR_LEN];
    int i;
    for (i=0; i<ARR_LEN; i++)
        arr[i] = fgetc(fp);
    print_array(arr, ARR_LEN);
    insertsort(arr, ARR_LEN);
    print_array(arr, ARR_LEN);
}
