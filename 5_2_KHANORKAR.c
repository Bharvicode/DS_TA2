#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    int capacity;
    int front;   
    int rear;   
    int size;    
} Queue;

Queue *createQueue(int capacity) {
    if (capacity <= 0) return NULL;
    Queue *q = malloc(sizeof(Queue));
    if (!q) return NULL;
    q->data = malloc(sizeof(int) * capacity);
    if (!q->data) { free(q); return NULL; }
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

void destroyQueue(Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
}

int isEmpty(Queue *q) {
    return q ? (q->size == 0) : 1;
}

int isFull(Queue *q) {
    return q ? (q->size == q->capacity) : 0;
}

int enqueue(Queue *q, int value) {
    if (!q || isFull(q)) return -1;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
    return 0;
}

int dequeue(Queue *q, int *out) {
    if (!q || !out || isEmpty(q)) return -1;
    *out = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    if (q->size == 0) {
    
        q->front = 0;
        q->rear = -1;
    }
    return 0;
}

int front(Queue *q) {
    if (!q || isEmpty(q)) return INT_MIN;
    return q->data[q->front];
}

int rear(Queue *q) {
    if (!q || isEmpty(q)) return INT_MIN;
    return q->data[q->rear];
}

void printQueue(Queue *q) {
    if (!q) return;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents (front -> rear): ");
    for (int i = 0, idx = q->front; i < q->size; ++i, idx = (idx + 1) % q->capacity) {
        printf("%d", q->data[idx]);
        if (i + 1 < q->size) printf(" ");
    }
    printf("\n");
}

int main(void) {
    Queue *q = createQueue(5);
    if (!q) {
        fprintf(stderr, "Failed to create queue\n");
        return 1;
    }

    printf("Enqueue 10, 20, 30\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);

    int x;
    if (dequeue(q, &x) == 0) printf("Dequeued: %d\n", x);
    printQueue(q);

    printf("Enqueue 40, 50, 60\n");
    enqueue(q, 40);
    enqueue(q, 50);
    if (enqueue(q, 60) != 0) printf("Queue is full, cannot enqueue 60\n");
    printQueue(q);

    printf("Front: %d, Rear: %d\n", front(q), rear(q));

    while (!isEmpty(q)) {
        dequeue(q, &x);
        printf("Popped %d\n", x);
    }

    printQueue(q);
    destroyQueue(q);
    return 0;
}
