#include <stdio.h>

int find_index_sorted(const int *arr, int needle, int len) {
    int left, right, mid;
    left = 0; right = len-1;
    while (left <= right) {
        mid = (left+right)/2;
        if (arr[mid] < needle) {
            left = mid+1;
        } else if (arr[mid] > needle) {
            right = mid-1;
        } else {
            return mid;
        }
    }
    return -1;
}

void print_array(const int *arr, int len) {
    int i;
    for (i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
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
    while (scanf("%d", &i))
        printf("%d\n", find_index_sorted(arr, i, ARR_LEN));
    return 0;
}
