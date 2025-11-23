#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int n;      
    int k;     
    int *arr;   
    int *top;  
    int *next;  
    int freeTop;
} KStacks;


KStacks *createKStacks(int k, int n) {
    if (k <= 0 || n <= 0) return NULL;
    KStacks *st = malloc(sizeof(KStacks));
    if (!st) return NULL;
    st->k = k; st->n = n;
    st->arr = malloc(n * sizeof(int));
    st->top = malloc(k * sizeof(int));
    st->next = malloc(n * sizeof(int));
    if (!st->arr || !st->top || !st->next) { free(st->arr); free(st->top); free(st->next); free(st); return NULL; }

    for (int i = 0; i < k; ++i) st->top[i] = -1; 
    for (int i = 0; i < n - 1; ++i) st->next[i] = i + 1; 
    st->next[n - 1] = -1;
    st->freeTop = 0;
    return st;
}

int isFull(KStacks *st) {
    return (st->freeTop == -1);
}

int isEmpty(KStacks *st, int sn) {
    if (sn < 0 || sn >= st->k) return 1;
    return (st->top[sn] == -1);
}

int push(KStacks *st, int sn, int value) {
    if (sn < 0 || sn >= st->k) return -1; 
    if (isFull(st)) return -2; 
    int i = st->freeTop;          
    st->freeTop = st->next[i];    
    st->arr[i] = value;           
    st->next[i] = st->top[sn];   
    st->top[sn] = i;              
    return 0;
}

int pop(KStacks *st, int sn, int *pvalue) {
    if (sn < 0 || sn >= st->k) return -1; 
    if (isEmpty(st, sn)) return -2; 
    int i = st->top[sn];       
    st->top[sn] = st->next[i];    
    st->next[i] = st->freeTop;    
    st->freeTop = i;
    if (pvalue) *pvalue = st->arr[i];
    return 0;
}

void freeKStacks(KStacks *st) {
    if (!st) return;
    free(st->arr);
    free(st->top);
    free(st->next);
    free(st);
}


int main(void) {
    int k = 3;   
    int n = 10;  
    KStacks *st = createKStacks(k, n);
    if (!st) { fprintf(stderr, "Allocation failed\n"); return 1; }

    push(st, 0, 15);
    push(st, 1, 45);
    push(st, 0, 17);
    push(st, 2, 11);
    push(st, 1, 39);
    push(st, 2, 9);

    int val;
    if (pop(st, 0, &val) == 0) printf("Popped from stack 0: %d\n", val);
    if (pop(st, 1, &val) == 0) printf("Popped from stack 1: %d\n", val);
    if (pop(st, 2, &val) == 0) printf("Popped from stack 2: %d\n", val);

    for (int i = 0; i < 10; ++i) {
        int r = push(st, i % k, i + 100);
        if (r == -2) { printf("Array full at iteration %d\n", i); break; }
    }

    while (!isEmpty(st, 0)) {
        if (pop(st, 0, &val) == 0) printf("stack0 pop: %d\n", val);
    }

    freeKStacks(st);
    return 0;
}
