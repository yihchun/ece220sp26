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
#ifdef DEBUG
    printf("Partition Done: [%d] ", partition);
    print_array(arr, len);
#endif
    if (left == len-1 && arr[left] < partition) {
        /* partition is the largest value in the array */
#ifdef DEBUG
        printf(">>> Largest Value\n");
#endif
        arr[0] = arr[len-1];
        arr[len-1] = partition;
        quicksort(arr, len-1);
    } else {
#ifdef DEBUG
        printf(">>> Something Else left=%d\n", left);
        assert(left == right);
        assert(arr[left] >= partition);
#endif
        arr[0] = arr[left-1];
        arr[left-1] = partition;
#ifdef DEBUG
        for (i=0; i<left-1; i++) assert(arr[i] <= partition);
        for (i=left; i<len; i++) assert(arr[i] >= partition);
#endif
        quicksort(arr, left-1);
        quicksort(arr+left, len-left);
    }
#ifdef DEBUG
    printf("Sort done: ");
    print_array(arr, len);
    for (i=1; i<len; i++) assert(arr[i-1] <= arr[i]);
#endif
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
        //print_array(arr, len);
    }
}

int median_of_medians(int *arr, int len) {
    /* len/5 medians will wind up in arr[0...ceil(len/5)] */
    int i, j, k, tmp;
    int stride = 1+((len+4)/5);
    int vals[5];
    if (len <= 5) {
        insertsort(arr, len);
        return arr[len/2];
    }
    for (i=0; i<stride; i++) {
        k=0;
        for (j=i; j<len; j+=stride) {
            vals[k++] = arr[j];
        }
        insertsort(vals,k);
        for (j=i; j<len; j+=stride) {
            if (vals[k/2] == arr[j]) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return quickselect(arr, stride/2, stride);
}


#define ARR_LEN 200000

int main() {
    FILE *fp = fopen("/dev/urandom", "r");
    int arr[ARR_LEN];
    int i;
    for (i=0; i<ARR_LEN; i++)
        arr[i] = fgetc(fp);
    //print_array(arr, ARR_LEN);
    quicksort(arr, ARR_LEN);
    //print_array(arr, ARR_LEN);
}

/*
int main() {
    int x;
    scanf("%d", &x);
    printf("%d! = %d\n", x, factorial(x));
    return 0;
}
*/
