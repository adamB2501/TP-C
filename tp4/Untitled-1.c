#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { OPERATOR, OPERAND } nodeType;

typedef union { char operator; int operand; } Content;

typedef struct node {
nodeType type;
Content content;
struct node* left;
struct node* right;
} TreeNode;

typedef struct elem {
nodeType type;
Content content;
struct elem* next;
} listNode;

typedef struct Stack{
    int value;
    struct Stack* next;
}Stack;

int pull(Stack** s) {
    if (*s) {
        Stack* del = (*s);
        int ret = (*s)->value;
        (*s) = (*s)->next;
        free(del);
        return ret;
    }
}

void push(Stack** s, int value) {
    Stack* newHead = malloc(sizeof(Stack));
    newHead->next = *s;
    newHead->value = value;
    (*s) = newHead;
}

TreeNode* createOperandNode(int val) {
    TreeNode* T = malloc(sizeof(TreeNode));
    T->type = OPERAND;
    T->content.operand = val;
    T->left = NULL;
    T->right = NULL;
    return T;
}

TreeNode* createOperatorNode(char op, TreeNode* exp1, TreeNode* exp2) {
    TreeNode* T = malloc(sizeof(TreeNode));
    T->type = OPERATOR;
    T->content.operator = op;
    T->left = exp1;
    T->right = exp2;
    return T;
}

void postOrderList(TreeNode* root, listNode** l) {
    if (root == NULL) {return;}
    postOrderList(root->left, l);
    postOrderList(root->right, l);
    listNode* newNode = malloc(sizeof(listNode));
    newNode->type = root->type;
    newNode->content = root->content;
    newNode->next = NULL;
    if (!(*l)) {
        *l = newNode;
        return;
    }
    else {
        listNode* temp = *l;
        while(temp -> next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int evalExpr(listNode* top) {
    listNode* temp = top;
    Stack* s = NULL;
    while (temp) {
        if (temp->type == OPERATOR) {
            int nd = pull(&s);
            int st = pull(&s);
            switch (temp->content.operator) {
                case '+':push(&s, st + nd);break;
                case '*':push(&s, st * nd);break;
                case '-':push(&s, st - nd);break;
                case '/':push(&s, st / nd);break;
                case '%':push(&s, st % nd);break;
            }
            temp = temp->next;
        }
        else {
            push(&s,temp->content.operand);
            temp = temp->next;
        }
    }
    return pull(&s);
}

int main() {
    TreeNode* root = createOperatorNode('*',
                        createOperatorNode('-',
                            createOperandNode(85),
                            createOperandNode(9)),
                        createOperatorNode('/',
                            createOperatorNode('+',
                                createOperandNode(78),
                                createOperandNode(45)),
                            createOperatorNode('-',
                                createOperandNode(6),
                                createOperandNode(2))));
    listNode* l = NULL;
    postOrderList(root, &l);
    listNode* temp = l;
    while (temp) {
        if (temp->type == OPERAND)
            printf("%d", temp->content.operand);
        else
            printf("%c", temp->content.operator);
        temp = temp->next;
    }
    printf("\n");
    printf("%d\n", evalExpr(l));
    printf("%d",  (85 - 9) * ((78 + 45) / (6 - 2)));
    return 0;
}