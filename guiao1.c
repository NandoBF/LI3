#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    void* data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct deque {
    Node* front;
    Node* rear;

} Deque;

bool isEmpty(Deque* deque){
    return(deque->front == NULL);
}

void printDeque(Deque* deque, void(*printFunc)(void*)){
    if(isEmpty(deque)) printf("Empty Deque");

    Node* useNode = deque->front; 
    while(useNode != NULL){
        printFunc(useNode->data);
        printf(" ");
        useNode = useNode->next;
    }
    printf("\n");

    return;
}


void printInt(void* data){
    printf("%d", *(int*)data);
}


Deque* create(){
    Deque* newDeque = (Deque*)malloc(sizeof(Deque));
    newDeque->front = NULL;
    newDeque->rear = NULL;
    return newDeque;
}

void push(Deque* deque, void* data){
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = deque->rear;

    if(isEmpty(deque)) deque->front = newNode;
    else deque->rear->next = newNode;

    deque->rear = newNode;
}


void pushFront(Deque* deque, void* data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = deque->front;
    newNode->prev = NULL;

    if(isEmpty(deque)) deque->front = newNode;
    else deque->front->prev = newNode;
    
    deque->front = newNode;
}

void* pop(Deque* deque){
    if(isEmpty(deque)){
        printf("Cannot delete from rear\n");
        return NULL;
    } 

    Node* temp = deque->rear;
    void* data = temp->data;

    deque->rear = deque->rear->prev;
    if(deque->rear != NULL){
        deque->rear->next = NULL;
    } else {
        deque->front = NULL;
    }

    free(temp);
    return data;
}

void* popFront(Deque* deque){
    if(isEmpty(deque)){
        printf("Cannot delete from front\n");
        return NULL;
    } 

    Node* temp = deque->front;
    void* data = temp->data;
    
    deque->front = deque->front->next;
    if(deque->front != NULL){
        deque->front->prev = NULL;
    } else {
        deque->rear = NULL;
    }
    free(temp);
    return data;
}


int size(Deque* deque){
    if(isEmpty(deque)) return 0;

    int size = 0;
    Node* temp = deque->front;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }
    return size;
}

void reverse(Deque* deque){
    if(isEmpty(deque)) return;

    Node* current = deque->front;
    Node* temp = NULL;

    while(current != NULL){
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    temp = deque->front;
    deque->front = deque->rear;
    deque->rear = temp;
}

void destroy(Deque* deque){
    Node* current = deque->front;
    Node* temp = NULL;
    while(current->next){
        temp = current->next;
        free(current);
        current = temp;
    }
    free(deque);
}


int main(){
    Deque* deq = create();
    //printf("%d\n", isEmpty(deq));
    printDeque(deq, printInt);
    int qq = 87;
    int qq1 = 55;
    int qq2 = 67;
    push(deq, &qq);
    push(deq, &qq1);
    pushFront(deq, &qq2);
    printDeque(deq, printInt);
    pop(deq);
    printDeque(deq, printInt);
    printf("Size: %d\n", size(deq));
    reverse(deq);
    printDeque(deq, printInt);
     
     
    return 0;
}
