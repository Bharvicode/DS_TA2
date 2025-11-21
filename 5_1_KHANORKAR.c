#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

int isEmpty(void) {
    return top == -1;
}

int isFull(void) {
    return top == MAX - 1;
}

void push(int val) {
    if (isFull()) {
        printf("Stack overflow: cannot push %d\n", val);
        return;
    }
    stack[++top] = val;
    printf("%d pushed onto stack\n", val);
}

int pop(void) {
    if (isEmpty()) {
        printf("Stack underflow: cannot pop\n");
        return -1; 
    }
    return stack[top--];
}

int peek(void) {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}

void display(void) {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = top; i >= 0; --i)
        printf("%d%s", stack[i], i ? " " : "");
    printf("\n");
}

int main(void) {
    int choice, value;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek (top)\n4. Display\n5. Exit\nChoose an option: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    return 1;
                }
                push(value);
                break;
            case 2:
                value = pop();
                if (value != -1) printf("Popped: %d\n", value);
                break;
            case 3:
                value = peek();
                if (value != -1) printf("Top: %d\n", value);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}