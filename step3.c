// push and pull 
#include <stdio.h>
#include <stdlib.h>
#define BLOCKSIZE 1
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

void allocateBlock(struct list *pList, int *counter, int nNodes) 
{
  for (int x = 1; x <= nNodes; ++x)  {

    struct node* newOb = allocator(sizeof(struct node),counter);
     // assign value
    newOb->i = -1;
    //Set next of new node as next of prev node 
    newOb->next = pList->left->next;
    //Set the next of prev node as new node 
    pList->left->next = newOb;
    //Set prev node as previous of new node 
    newOb->prev = pList->left;
    // If there is another item, set new node as prev
    if (newOb->next != NULL)
        newOb->next->prev = newOb;
    // increase length by 1
    pList->length = pList->length+1;
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

// this was taken from the appendix provided in the assignment

void deAllocateBlock(struct list *pList, int *counter, int nNodes) {
    int n = (pList->length) - nNodes;
    while ((pList->length) > n) {
        struct node *temp = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = temp->next;
        deAllocator(temp, counter);
        (pList->length)--;
    }
}

void pushInt(struct list *pList, int *counter, int i){
    if (pList->length == 0){
        allocateBlock(pList,counter, BLOCKSIZE); 
    }
    if((i%2)==0){
        pList->right->prev->i = i;
        pList->right = pList->right->prev;
    }else{
        pList->left->next->i = i;
        pList->left = pList->left->next;
    }
    pList->length = pList->length - 1;
}

void pullInt(struct list *pList, int *counter, int i){
    if(i % 2 == 0 && pList->right != pList->tail){
    pList->right->i = -1;
    pList->right = pList->right->next;
    pList->length = pList->length + 1;
}else if(i % 2 == 1 && pList->left != pList->head){
    pList->left-> i = -1;
    pList->left = pList->left->prev;
    pList->length = pList->length + 1;
    }
    
    //pList->length = pList->length + 1;

    if (pList->length > BLOCKSIZE){
        deAllocateBlock(pList, counter,BLOCKSIZE);
    }
}

void clearList(struct list *pList, int *counter) {
  while (pList->left != pList->head) {
    pullInt(pList, counter, 1);
  }
  while (pList->right != pList->tail) {
    pullInt(pList, counter, 0);
  }
  deAllocateBlock(pList, counter, pList->length);
  freeList(pList,counter);
}

int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  int N = 6;
  int i = 0;
  while (i < N) {
    pushInt(&myList, &counter, i % 9);
    printList(&myList, &counter);
    pullInt(&myList, &counter, 0);
    printList(&myList, &counter);
    i++;
  }
  clearList(&myList, &counter);
  printList(&myList, &counter);
}

