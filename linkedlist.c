#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node_t ll_node;
struct ll_node_t {
    int x;
    ll_node *next;
};

typedef struct dll_node_t dll_node;
struct dll_node_t {
    int x;
    dll_node *next, *prev;
};

typedef struct dll_list {
    dll_node *head;
    dll_node *tail;
} dll_list;

void dll_init(dll_list *list) {
    list->head = list->tail = NULL;
}

void dll_insert_head(dll_list *list, int val) {
    dll_node *tmp = malloc(sizeof(dll_node));
    tmp->next = list->head;
    tmp->x = val;
    tmp->prev = NULL;
    if (list->head) {
        tmp->next->prev = tmp;
    } else {
        list->tail = tmp;
    }
    list->head = tmp;
}

void dll_delete(dll_list *list, int victim) {
    dll_node *tmp;
    for (tmp = list->head; tmp && tmp->x != victim; tmp = tmp->next)
        ;
    if (tmp->prev) {
        tmp->prev->next = tmp->next;
    } else {
        list->head = tmp->next;
    }
    if (tmp->next) {
        tmp->next->prev = tmp->prev;
    } else {
        list->tail = tmp->prev;
    }
    free(tmp);
}

void dll_print(const dll_list list) {
    dll_node *head = list.head;
    while (head) {
        printf("(%p)%d(%p) ", head->prev, head->x, head->next);
        head = head->next;
    }
    printf("%p %p\n", list.head, list.tail);
}

void ll_print(const ll_node *head) {
    while (head) {
        printf("%d ", head->x);
        head = head->next;
    }
    printf("\n");
}

void ll_insert_head(ll_node **head, int data) {
    ll_node *new_node = malloc(sizeof(ll_node));
    new_node->next = *head;
    new_node->x = data;
    *head = new_node;
}

void ll_insert_tail(ll_node **head, int data) {
    if (*head == NULL) {
        ll_insert_head(head, data);
        return;
    }
    while ((*head)->next) {
        head = &((*head)->next);
    }
    (*head)->next = malloc(sizeof(ll_node));
    (*head)->next->next = NULL;
    (*head)->next->x = data;
}

void ll_insert_inorder_asc(ll_node **head, int data) {
    ll_node *tmp;
    while ((*head) && (*head)->x <= data) {
        head = &((*head)->next);
    }
    tmp = malloc(sizeof(ll_node));
    tmp->next = (*head);
    tmp->x = data;
    (*head) = tmp;
}

int ll_delete(ll_node **head, int victim) {
    ll_node *tmp;
    while ((*head) && (*head)->x != victim) {
        head = &((*head)->next);
    }
    if (!*head)
        return 0;
    tmp = (*head)->next;
    free(*head);
    *head = tmp;
    return 1;
}
    
int main() {
    dll_list list;
    dll_init(&list);
    dll_print(list);
    dll_insert_head(&list, 5);
    dll_insert_head(&list, 6);
    dll_insert_head(&list, 7);
    dll_print(list);
    dll_delete(&list, 6);
    dll_print(list);
        dll_delete(&list, 5);
    dll_print(list);
        dll_delete(&list, 7);
    dll_print(list);
    /*
    ll_node *head = NULL;
    ll_insert_head(&head, 14);
    ll_insert_head(&head, 12);
    ll_insert_head(&head, 10);
    ll_insert_tail(&head, 16);
    ll_insert_inorder_asc(&head, 9);
    ll_print(head);
    ll_insert_inorder_asc(&head, 17);
    ll_print(head);
    ll_delete(&head, 9);
    ll_delete(&head, 17);
    ll_delete(&head, 12);
    ll_print(head);
    */
}
