#include <stdio.h>
#include <assert.h>

/* return factorial of n */
int factorial(unsigned int n) {
    int tmp;
    if (n <= 1) return 1;
    tmp = factorial(n-1);
    return tmp*n;
}

void print_array(const int *arr, int len) {
    int i;
    for (i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* sorts arr, quickly if possible, which is of length len */
void quicksort(int *arr, int len) {
    int partition, left, right, tmp, i;
    if (len < 2) return;
    if (len == 2) {
        if (arr[0] > arr[1]) {
            tmp = arr[0];
            arr[0] = arr[1];
            arr[1] = tmp;
        }
        return;
    }
    partition = arr[0];
    left = 1; right = len-1;
    while (1) {
        while (left < right && arr[left] <= partition) { left++; }
        while (left < right && arr[right] >= partition) { right--; }
        if (left >= right) break;
        tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
    }
    printf("Partition Done: [%d] ", partition);
    print_array(arr, len);
    if (left == len-1 && arr[left] < partition) {
        /* partition is the largest value in the array */
        printf(">>> Largest Value\n");
        arr[0] = arr[len-1];
        arr[len-1] = partition;
        quicksort(arr, len-1);
    } else if (right == 1) {
        printf(">>> Smallest Value\n");
        /* partition is the smallest value in the array */
        quicksort(arr+1, len-1);
    } else {
        printf(">>> Something Else left=%d\n", left);
        assert(left == right);
        assert(arr[left] >= partition);
        arr[0] = arr[left-1];
        arr[left-1] = partition;
        for (i=0; i<left-1; i++) assert(arr[i] <= partition);
        for (i=left; i<len; i++) assert(arr[i] >= partition);
        quicksort(arr, left-1);
        quicksort(arr+left, len-left);
    }
    printf("Sort done: ");
    print_array(arr, len);
    for (i=1; i<len; i++) assert(arr[i-1] <= arr[i]);
}

#define ARR_LEN 20

int main() {
    FILE *fp = fopen("/dev/urandom", "r");
    int arr[ARR_LEN];
    int i;
    for (i=0; i<ARR_LEN; i++)
        arr[i] = fgetc(fp);
    print_array(arr, ARR_LEN);
    quicksort(arr, ARR_LEN);
    print_array(arr, ARR_LEN);
}

/*
int main() {
    int x;
    scanf("%d", &x);
    printf("%d! = %d\n", x, factorial(x));
    return 0;
}
*/
