#include <stdio.h>
#include <stdlib.h>

struct n{
    int x;
    struct n * next;
};
typedef struct n node;

void bastir(node * r){
    while(r != NULL){
        printf("%d ", r->x); //We print the value of r for x.
        r = r -> next; //We are passing r to the next node.
    }
    printf("\n");
}

void ekle(node *r,  int x){ //This function adds a new node to a given node pointer r and assigns the given x value to that new node.
    while(r -> next != NULL){ //As long as r's next is not NULL, meaning r has a next node, we pass r to the next node.
        r = r -> next; //We are passing r to the next node.
    } 
r -> next = (node *) malloc (sizeof(node)); //We allocate memory for a new node and assign it to r's next, meaning we are adding a new node at the end of the list.
r -> next -> x = x; //We assign the given x value to the x of the new node we just created.
r -> next -> next = NULL; //We set the next of the new node to NULL, because it is now the last node in the list.
}

int main(){

    node * root; //We declare a pointer to node called root, which will be the starting point of our linked list.
    root = (node *) malloc (sizeof(node)); //We allocate memory for a new node and assign it to root, meaning we are creating the first node of our linked list.
    root -> next = NULL; //We set the next of root to NULL, because it is currently the only node in the list and therefore the last node.
    root -> x = 500; //We assign the value 500 to the x of root, meaning the first node of our linked list will have an x value of 500.
    int i = 0;
    for(i=0; i<5; i++){
        ekle(root, i*10); //We call the ekle function in a loop to add new nodes to our linked list. We pass root as the node pointer and i*10 as the x value for each new node. This will add nodes with x values of 0, 10, 20, 30, and 40 to the end of our linked list.
    }
     bastir(root); //We call the bastir function to print the values of all nodes in our linked list starting from root. This will print the x values of all nodes in the list, which should be 500, 0, 10, 20, 30, and 40.
}