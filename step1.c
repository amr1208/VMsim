// initalising the list
#include <stdio.h>
#include <stdlib.h>


struct node{
    int i;
    struct node *next;
    struct node *prev;
};

struct list{
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    int length;
};

void *allocator(int size, int *counter){
    struct node* current = malloc(size); 
    if (!current){
        return NULL;
    }
    (*counter)++;
    return current;
}

void deAllocator(void *p, int *counter){
    if (p != NULL){
        free(p);
        (*counter)--;
    }
}

void initialiseList(struct list *pList, int *counter){
    pList->head = allocator(sizeof(struct node),counter);
    pList->tail = allocator(sizeof(struct node),counter);
    
    pList->head->next = pList->tail;
    pList->tail->prev = pList->head;
    pList->head->prev = NULL;
    pList->tail->next = NULL;
    pList->head-> i = 0;
    pList->tail-> i = 0;
    pList->left = pList->head;
    pList->right = pList->tail;
    pList->length = 0;

}

void freeList(struct list *pList, int *counter){
    if (pList->length == 0 && pList->head == pList->left && pList->tail == pList->right) {
        deAllocator(pList->head,counter);
        deAllocator(pList->tail,counter);

        pList->head = NULL;
        pList->left = NULL;
        pList->tail = NULL;
        pList->right = NULL;

        pList->length = -1;
    }
}
// this was taken from the appendix provided in the assignment
void printList(struct list *pList, int *counter) {
    struct node *cur  = pList->head;
    while (cur) {
        printf(" | %d | ", cur->i);
        cur = cur->next;
    }
    if (!(pList->head) || !(pList->tail) || *(counter) == 0)
        printf(" ||");
    printf("\ncounter = %d\n", *(counter));
}

int main() { 
    int counter = 0; 
    struct list myList; 
    initialiseList(&myList, &counter); 
    printList(&myList, &counter); 
    freeList(&myList, &counter); 
    printList(&myList, &counter); 
}

