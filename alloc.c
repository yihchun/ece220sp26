#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_t {
    char *NAME;
    int UIN;
    float GPA;
} student;

int main() {
    student *arr = malloc(200*sizeof(student));
    int i;
    for (i=0; i<200; i++) {
        /* Initialize name to “To be set”, UIN to -1 and
         * GPA to 0.0 for all 200 records */
        arr[i].NAME = malloc(100);
        /* DO NOT: arr[i].NAME = "To be set"; */
        strcpy(arr[i].NAME, "To be set");
        arr[i].UIN = -1;
        arr[i].GPA = 0;
    }
    /* scanf("%s", arr[0].NAME); */
    printf("%s\n", arr[0].NAME);
    for (i=0; i<200; i++) {
        free(arr[i].NAME);
    }
    free(arr);
}
