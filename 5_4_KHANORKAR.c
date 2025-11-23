#include <stdio.h>
#include <stdlib.h>

int *arr;
int size, mid;
int len1, len2;
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

int isFull1() { return (front1 == (rear1 + 1) % len1); }
int isFull2() { return (front2 == (rear2 + 1) % len2); }
int isEmpty1() { return front1 == -1; }
int isEmpty2() { return front2 == -1; }

void enqueue1(int x) {
    if (len1 == 0) { printf("Queue1 capacity 0\n"); return; }
    if (isFull1()) { printf("Queue1 Overflow\n"); return; }
    if (isEmpty1()) front1 = rear1 = 0;
    else rear1 = (rear1 + 1) % len1;
    arr[rear1] = x;
}

int dequeue1(int *ok) {
    if (isEmpty1()) { *ok = 0; return 0; }
    int val = arr[front1];
    if (front1 == rear1) front1 = rear1 = -1;
    else front1 = (front1 + 1) % len1;
    *ok = 1;
    return val;
}

void enqueue2(int x) {
    if (len2 == 0) { printf("Queue2 capacity 0\n"); return; }
    if (isFull2()) { printf("Queue2 Overflow\n"); return; }
    if (isEmpty2()) front2 = rear2 = 0;
    else rear2 = (rear2 + 1) % len2;
    arr[mid + rear2] = x;
}

int dequeue2(int *ok) {
    if (isEmpty2()) { *ok = 0; return 0; }
    int val = arr[mid + front2];
    if (front2 == rear2) front2 = rear2 = -1;
    else front2 = (front2 + 1) % len2;
    *ok = 1;
    return val;
}

void display1() {
    if (isEmpty1()) { printf("Queue1 empty\n"); return; }
    int i = front1;
    while (1) {
        printf("%d ", arr[i]);
        if (i == rear1) break;
        i = (i + 1) % len1;
    }
    printf("\n");
}

void display2() {
    if (isEmpty2()) { printf("Queue2 empty\n"); return; }
    int i = front2;
    while (1) {
        printf("%d ", arr[mid + i]);
        if (i == rear2) break;
        i = (i + 1) % len2;
    }
    printf("\n");
}

int main() {
    int choice, x, ok;
    printf("Enter total array size: ");
    if (scanf("%d", &size) != 1 || size <= 0) return 0;
    arr = malloc(sizeof(int) * size);
    mid = size / 2;
    len1 = mid;
    len2 = size - mid;
    while (1) {
        printf("1:Enq1 2:Deq1 3:Dis1 4:Enq2 5:Deq2 6:Dis2 0:Exit\n");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;
        switch (choice) {
            case 1:
                printf("val: ");
                if (scanf("%d", &x) == 1) enqueue1(x);
                break;
            case 2:
                x = dequeue1(&ok);
                if (ok) printf("Dequeued: %d\n", x);
                else printf("Queue1 Underflow\n");
                break;
            case 3:
                display1();
                break;
            case 4:
                printf("val: ");
                if (scanf("%d", &x) == 1) enqueue2(x);
                break;
            case 5:
                x = dequeue2(&ok);
                if (ok) printf("Dequeued: %d\n", x);
                else printf("Queue2 Underflow\n");
                break;
            case 6:
                display2();
                break;
            default:
                printf("Invalid\n");
        }
    }
    free(arr);
    return 0;
}