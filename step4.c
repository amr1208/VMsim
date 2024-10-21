// interact with the user 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BLOCKSIZE 1
#define maxInput 5 * BLOCKSIZE
//defining a node
struct node{
    int i; //integer stored in node
    struct node *next; //pointer to the next node
    struct node *prev; // pointer to the previous node
};
// defining a list handle
struct list{
    struct node *head; //pointer to the head
    struct node *tail; //pointer to the tail
    struct node *right; //pointer to the node storing the last-added even integer
    struct node *left; //pointer to the node storing the last-added odd integer,
    int length; //  number of nodes in the free space
};
// allocate size bytes of memory
void *allocator(int size, int *counter){
    struct node* current = malloc(size); 
    if (!current){
        return NULL;
    }
    (*counter)++;
    return current;
}
//function to free up memory 
void deAllocator(void *p, int *counter){
    if (p != NULL){
        free(p);
        (*counter)--;
    }
}
// function that allocates head and tail to list
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
// check to see if list is empty
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
// allocates a new object to list
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
// store digit in list
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
//removes digit from list
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
// method clears list by calling pullint multiple time
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
// adapted psuedocode implementation from worksheet
//#include <ctype.h>
int getInput(char *s){
    int i = 0;
    char c = '\0';

    while (c != '\n' && i<maxInput){
        c = getchar();
        if (isdigit(c)){
            s[i] = c;
            i++;
        }
    }
    if (i == maxInput){
        while (c != '\n'){
            c = getchar();
        }
    }
    return i;
}

// code modified from worksheet
int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  char sPush[maxInput];
  char sPull[maxInput];
  int lenPush = getInput(sPush);
  int lenPull = getInput(sPull);
  int i = 0;
  int j = 0;
  while ((i + j) < (lenPush + lenPull)) {
    if (i < lenPush) {
      pushInt(&myList, &counter, sPush[i] - '0');
      i++;
      printList(&myList, &counter);
    }
    if (j < lenPull) {
      pullInt(&myList, &counter,  sPull[j] - '0');
      j++;
      printList(&myList, &counter);
    }
  }
  printList(&myList, &counter);
  clearList(&myList, &counter);
  printList(&myList, &counter);
}