#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List {
int data;
struct List* next;
} List;
void show(List* l) {
    while (l) {
        printf("%d ", l->data);
        l = l -> next;
    }
}

List* divide(List* L){
    List* slow = L;
    List* fast = L;
    while (slow ->next && fast -> next && fast -> next -> next) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    List* slow_1 = slow->next;
    slow -> next = NULL;
    return slow_1; 
}

List* merge(List* h1,List* h2) {

    List* organised_list;
    if (h1 -> data < h2 -> data) {
        organised_list = h1;
        h1 = h1 -> next;
    }
    else {
        organised_list = h2;
        h2 = h2 -> next;
    }
    List* organised_list_tail = organised_list;
    while (h1 && h2) {
        if (h1 -> data < h2 -> data) {
            organised_list_tail -> next = h1;
            h1 = h1 -> next;
            organised_list_tail = organised_list_tail -> next;
        }
        else{
            organised_list_tail -> next = h2;
            h2 = h2 -> next;
            organised_list_tail = organised_list_tail -> next;
        }
    }
    organised_list_tail -> next = (h1) ? h1 : h2;
    return organised_list;
}

List* merge_sort(List* L) {
    if (!L || !(L -> next)) {
        return L;
    }
    else {
        List* h1 = L;
        List* h2 = divide(L);
        h1 = merge_sort(h1);
        h2 = merge_sort(h2);
        if (h1 == NULL) 
        {return h2;}
        else if (h2 == NULL) 
        {return h1;}
        return merge(h1,h2);
    }
}

bool VerifDoublons(List *L)
{
List *i = merge_sort(L);
while (i && i -> next) {
if (i == i -> next) {
    return true;
} 
}
return false;
}

void main() {
    List* a = malloc(sizeof(List));
    List* b = malloc(sizeof(List));
    List* c = malloc(sizeof(List));
    List* d = malloc(sizeof(List));
    a -> next = b;
    b -> next = d;
    d -> next = NULL;
    a -> data = 10;
    b -> data = 7;
    d -> data = 2;
    show(a);
    a = merge_sort(a);
    show(a);
}