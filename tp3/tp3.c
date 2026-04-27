#include <stdio.h>
#include <stdlib.h>

typedef struct node {
int info;
struct node *left, *right;
} node;
typedef struct {
int info;
int left, right;
} static_node;

node* create_node(int v) {
    node* n = malloc(sizeof(node));
    n -> left = NULL;
    n -> right = NULL;
    n -> info = v;
    return n;
}

void insert_bst(node** T, int v) {
    node* new_node = create_node(v);
    node* pointer = *T;
    if (!(*T)) {
        *T = new_node;
    }
    else {
        while (1) {
            if (v < (pointer) -> info) {
                if ((pointer) -> left) {
                    (pointer) = (pointer) -> left;
                }
                else {pointer -> left = new_node; break;}
            }
            else {
                if (pointer -> right) {
                    pointer = pointer -> right;
                }
                else {
                    pointer -> right = new_node; 
                    break;
                }
            }
        }
    }
}

int count_nodes(node* T) {
    return (T) ? 1 + count_nodes(T -> right) + count_nodes(T -> left) : 0;
}

int count_leafs(node* T) {
    if (T == NULL) {return 0;}
    return (!(T -> right) && !(T -> left)) ? 1 : count_leafs(T -> left) + count_leafs(T -> right); 
}
void p_spaces(int l) {
    for (int i=0; i<l;i++) {
        printf("     ");
    }
    
}
void show_nodes(node* T,int level) {
    if (T) {
        show_nodes(T -> right,level+1);
        p_spaces(level);
        printf("%d",T -> info);
        printf("\n");
        show_nodes(T -> left,level+1);
    }
}

void find_node(node* T,node** parent,node** found,int v) {
    if (T) {
        if (T->info == v) {
            *found = T;
        }
        else {
            if (*found == NULL) {
                *parent = T;
            }
            if (T->info < v) {
            find_node(T->right, parent,found,v);
            }
            else {
            find_node(T->left, parent,found,v);
            }
        }
    }
}

void del_node(node** T,int v) {
    node* parent;
    node* found;
    parent = NULL;
    found = NULL;
    find_node(*T,&parent, &found,v);
    if (!(*T) || (found == NULL)) {
        printf("nothing to do here!");
    }
    else {//the element is found
        if (!(found->right) && !(found->left)) { //1st case no children
            if (parent == NULL) {
                *T = NULL;
            }
            else {
                if (parent->left == found) {parent ->left = NULL;}
                else {parent->right = NULL;}
            }
            free(found);
        }
        else if (found->right && found->left) { //2nd case two children 
            node* parentSucc = found;
            node* succ = found->right;
            while (succ->left) {
                parentSucc = succ;
                succ = succ->left;
            }
            found->info = succ->info;
            if (parentSucc->left == succ) {parentSucc->left = succ->right;}
            else {parentSucc->right = succ->right;}
            free(succ);
        }
        else if (found->right) { //3rd case only right child
            if (parent == NULL) {
                *T = found->right;
            }
            else {
                if (parent->left == found) {
                    parent->left = found->right;
                }
                else {parent->right=found->right;}
            }
            free(found);
        }
        else {//4th case only left child
            if (parent == NULL) {
                *T = found->left;
            }
            else {
                if (parent->left == found) {
                    parent->left = found->left;
                }
                else {parent->right=found->left;}
            }
            free(found);
        }
    }
}

void copy_tree (node *t, static_node *st, int *N) {
    if (t) {
        int parentIndex = *N;
        st[*N].info = t->info;
        st[*N].left = -1;
        st[*N].right = -1;
        if (t->right) {
            st[parentIndex].right = *N;
            (*N) ++;
            copy_tree(t->right,st,N);
        }
        if (t->left) {
            st[parentIndex].left = *N;
            (*N) ++;
            copy_tree(t->left,st,N);
        }
    }
    else {
        return;
    }
}

void delete_bst(node* t) {
    if (t) {
        delete_bst(t->left);
        delete_bst(t->right);
        free(t);
        printf("1");
    }
}

void main() {
    node* t = create_node(50);
    int num[9] = {30, 70, 20, 40, 60, 80, 10, 35, 65};
    for (int i = 0; i < 9; i++){
        insert_bst(&t,num[i]);
    }
    show_nodes(t,0);
    printf("number of nodes is %d\n",count_nodes(t));
    printf("number of leafs is %d\n",count_leafs(t));
    del_node(&t,10);
    printf("10 deleted\n");
    show_nodes(t,0);
    printf("---------------------->\n");
    del_node(&t,40);
    printf("40 deleted\n");
    show_nodes(t,0);
    del_node(&t,30);
    printf("---------------------->\n");
    printf("30 deleted\n");
    show_nodes(t,0);
    delete_bst(t);
}