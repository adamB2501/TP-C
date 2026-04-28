#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tribo_rec(int n) {
    switch (n) {
        case 0: return 0;break;
        case 1: return 1; break;
        case 2:return 1; break;
        default: return tribo_rec(n-1) + tribo_rec(n-2) + tribo_rec(n-3);
    }    
}

int tribo(int n) {
    int a=0, b=1, c=1;
    for (int i)

}