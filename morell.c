#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_t {
    int data;
    struct llnode_t *next;
} llnode;

int list_len(const llnode *head) {
    int ret;
    for (ret = 0; head; ret++)
        head = head->next;
    return ret;
}

/* sorts the list head in ascending order */
void my_mergesort(llnode **head) {
    int len = list_len(*head); /* find out list length so we can cut in half */
    /* skip this many elements before we set tmp->next to NULL to make our
     * half-length array
     */
    int halflen = len/2-1;
    /* Base case: lists of length 0 and 1 are already sorted */
    if (len < 2) return;

    /* tmp: starts out being used to traverse our linked list
     *      later is the head of one of the two lists that are merged together
     * tmp2: second list that we recursively call on
     * tail: tail of the merged list
     * next: pointer to either tmp or tmp2, depending on which is smaller,
     *       for merging purposes
     */
    llnode *tmp, *tmp2, *tail;
    llnode **next;
    /* walk through the first halflen elements of the list, so that
     * tmp has halflen elements behind it
     */
    for (tmp=*head; halflen--; tmp = tmp->next)
        ;
    /* now tmp2 will have halflen+1 (or len/2) elements behind it */
    tmp2 = tmp->next;
    /* chop up the list into len/2 and len-(len/2) */
    tmp->next = NULL;
    /* call the front of the list tmp, since the back of the list is tmp2 */
    tmp = *head;
    /* use the force, now magically tmp and tmp2 are sorted */
    my_mergesort(&tmp);
    my_mergesort(&tmp2);
    /* tail points to the last element of the partially assembled list.
     * when it is NULL, that's because we haven't started putting things
     * into that list yet. We will test for tail == NULL to decide whether
     * or not to set *head.
     */
    tail = NULL;
    /* loop while any remaining linked list nodes have not been added
     * to the new, sorted, reconstructed linked list
     */
    while (tmp || tmp2) {
        /* decide which of the two linked lists (tmp or tmp2) the next
         * element will come from. 
         */
        if (!tmp) {
            next = &tmp2; /* tmp is empty, so use tmp2 */
        } else if (!tmp2) {
            next = &tmp;  /* tmp2 is empty, so use tmp */
        } else if (tmp->data > tmp2->data) {
            next = &tmp2; /* tmp2 is smaller, so use tmp2 */
        } else {
            next = &tmp; /* tmp2 is not smaller, so use tmp */
        }

        /* Has the first element been added to this list yet? */
        if (tail == NULL) {
            *head = *next; /* no, so populate the head pointer */
        } else {
            tail->next = *next; /* yes, so chain onto the end */
        }
        /* set the tail pointer so the next node knows where to go */
        tail = *next; 
        /* advance the linked list from which the node was taken */
        *next = (*next)->next;
    }
}

typedef llnode *stack;

typedef struct queue_t {
    llnode *head;
    llnode *tail;
} queue;

void queue_init(queue *q) {
    q->head = q->tail = NULL;
}

void queue_enqueue(queue *q, int val) {
    llnode *tmp = malloc(sizeof(llnode));
    tmp->data = val;
    tmp->next = NULL;
    if (q->head == NULL) {
        q->head = tmp;
    } else {
        q->tail->next = tmp;
    }
    q->tail = tmp;
}

int queue_dequeue(queue *q) {
    if (!q->head) return -1;
    int val = q->head->data;
    llnode *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(tmp);
    return val;
}

void print_queue(queue q) {
    llnode *tmp;
    printf("Here's your queue. ");
    for (tmp = q.head; tmp; tmp = tmp->next)
        printf("%d ", tmp->data);
    printf("\n");
}

void stack_init(stack *s) {
    *s = NULL;
}

void stack_push(stack *s, int val) {
    llnode *tmp = malloc(sizeof(llnode));
    tmp->data = val;
    tmp->next = *s;
    *s = tmp;
}

int stack_pop(stack *s) {
    if (*s == NULL) return -1;
    int val = (*s)->data;
    llnode *tmp = *s;
    *s = (*s)->next;
    free(tmp);
    return val;
}
    
int main() {
    //stack s;
    queue q;
    int x;
    //stack_init(&s);
    queue_init(&q);
    while (1) {
        scanf("%d", &x);
        if (x >= 0) queue_enqueue(&q, x);
        else if (x == -2) print_queue(q);
        else if (x == -3) my_mergesort(&q.head); /* screws everything up */
        else printf("%d\n", queue_dequeue(&q));
        /*
        if (x >= 0) stack_push(&s, x);
        else printf("%d\n", stack_pop(&s));
        */
    }
    return 0;
}
