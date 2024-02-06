#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* head;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = (Node*)malloc(sizeof(Node));
    queue->head->next = queue->head;  // Point to itself initially
    queue->rear = queue->head;
    return queue;
}

bool isEmpty(Queue* queue) {
    return (queue->head->next == queue->head);
}

void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = queue->head;  // New node points to the head
    queue->rear->next = newNode;  // Rear node points to the new node
    queue->rear = newNode;  // Update the rear pointer
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data;
    Node* temp = queue->head->next;
    data = temp->data;
    queue->head->next = temp->next;  // Update the head node to point to the next node
    if (temp == queue->rear) {
        queue->rear = queue->head;  // If dequeued node is the rear, update rear to head
    }
    free(temp);
    return data;
}

void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = queue->head->next;
    while (temp != queue->head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    displayQueue(queue);
    printf("Dequeued: %d\n", dequeue(queue));
    displayQueue(queue);
    printf("Dequeued: %d\n", dequeue(queue));
    displayQueue(queue);
    printf("Dequeued: %d\n", dequeue(queue));
    displayQueue(queue);
    printf("Dequeued: %d\n", dequeue(queue));
    return 0;
}
