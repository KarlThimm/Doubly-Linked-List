#ifndef MP3_H
#define MP3_H

typedef struct node{ 
  char* name;
  char* title;
  struct node* next;
  struct node* prev; 
} node_t;


void ModeFunc(node_t** headptr, node_t** tailptr);
node_t* createNode();
void insert(node_t** headptr, node_t** tailptr);
void print(node_t* nodenew);
void delete(node_t** headptr, node_t** tailptr);
void printForwards(node_t* head); 
void printBackwards(node_t* ending);
void deleteNode(node_t** headptr, node_t** tailptr, node_t* del);
void delete(node_t** headptr, node_t** tailptr);
void freelist();



#endif
