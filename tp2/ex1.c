#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
int data;
struct node* next;
} node;

void swap(node* n1, node* n2) {
    int temp = n1->data;
    n1->data = n2->data;
    n2->data = temp;
}

void bubble_sort(node* n) {
    int repeat = 0;
    node* temp = n;
    while (temp->next) {
        if (temp->data > (temp->next)->data) {
            swap(temp, temp->next);
            repeat = 1;
        }
        temp = temp->next;
    }
    if (repeat) {
        triBulles(n);
    }
}

void min(node* n,node** min) {
    *min = n;
    while (n->next) {
        if (n->data < (*min)->data) {
            min = n;
        }
        n->next;
    }
}

void selection_sort(node* n) {
    while (n->next) {
        node* m;
        min(n,&m); 
        swap(n,m);
        n=n->next;
    }
}

node* get_tail(node* n) {
    while (n && n->next) {
        n = n->next;
    }
    return n;
}
node* quick_sort(node* n) {
    if (n) {
        node* pivot = n;
        node* half1 = NULL;
        node* half2 = NULL;
        node* tail1 = NULL;
        node* tail2 = NULL;
        while (n->next) {
            if ((n->next)->data < pivot->data) {
                if (!half1) {
                    half1 = n->next;
                    tail1 = half1;
                }
                else {
                    tail1->next = n->next;
                    tail1 = tail1->next;
                }
            }
            else {
                if (!half2) {
                    half2 = n->next;
                    tail2 = half2;
                }
                else {
                    tail2->next = n->next;
                    tail2 = tail2->next;
                }
            }
            n = n->next;
        }
        if (tail1) {tail1->next = NULL;}
        if (tail2) {tail2->next = NULL;}
        half1 = quick_sort(half1);
        half2 = quick_sort(half2);
        if (!half1 && !half2) {
            return pivot;
        }
        else if (!half1) {
            pivot->next = half2;
            return pivot;
        }
        else if (!half2) {
            tail1 = get_tail(half1);
            tail1->next = pivot;
            return half1;
        }
        else {
            tail1 = get_tail(half1);
            tail1->next = pivot;
            pivot->next = half2;
            return half1;
        }

    }
    else {
        return NULL;
    }
}