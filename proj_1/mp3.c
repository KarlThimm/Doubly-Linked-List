#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mp3.h"
#define BUFFERSIZE 128
node_t* head = NULL;
node_t* ending = NULL;

int main(){
  ModeFunc(&head, &ending);
}

void ModeFunc(node_t** headptr, node_t** tailptr){
  char buffer[BUFFERSIZE] = {'\0'};
  int mode = 0;
  int count;
  while(mode != 5){
    printf("\n(1) Add MP3\n(2) Delete MP3\n(3) Print Forwards\n(4) Print Backwards\n(5) Close Program\nEnter your choice :\n"); 
    if(fgets(buffer, BUFFERSIZE, stdin) != NULL){ 
      count = sscanf(buffer, "%d", &mode);
      if(count == 0){
	mode = 0;
      }
    }
    switch(mode){
    case 1:insert(headptr, tailptr);
      break;
    case 2: delete(headptr, tailptr);
      break;
    case 3: printForwards(*headptr);
      break;
    case 4: printBackwards(*tailptr);
      break;
    case 5: freelist();
      break;
    default: printf("No Selection, Try Again.\n");
      break;
    }
  }
}

node_t* createNode(){
  node_t* newNode = calloc(1,sizeof(node_t));
  char buffer[BUFFERSIZE] = {'\0'};
  int len;
  printf("Enter any song title:");
  if(fgets(buffer, BUFFERSIZE, stdin) != NULL){ 
    len = strlen(buffer);
    newNode->title = calloc(len, sizeof(char));
    strncpy(newNode->title, buffer, len-1);
  }
  printf("Enter the artist of the song's name:");
  if(fgets(buffer, BUFFERSIZE, stdin) != NULL){ 
    len = strlen(buffer);
    newNode->name = calloc(len, sizeof(char));
    strncpy(newNode->name, buffer, len-1);
  }
  return newNode;
}

void insert(node_t** headptr, node_t** tailptr){
  node_t* newNode = createNode();
  if(*headptr == NULL){
    *headptr = newNode;
    *tailptr = newNode;
    printf("Created New Node");
    print(newNode);
  }else{
    (*tailptr)->next = newNode;
    newNode->prev = *tailptr;
    *tailptr = newNode;
  }
}

void print(node_t* NodeCreated){
  printf("Title: %s, Artist: %s \n", NodeCreated->title, NodeCreated->name);
}

void printForwards(node_t* head){
  if(head == NULL){
    printf("The List Is Empty\n");
  }else{
    printf("Printed from beginning to end: \n");
  }
   while(head != NULL){
    print(head);
    head = head->next;
  }
}

void deleteNode(node_t** headptr, node_t** tailptr, node_t* del){
  if(*headptr == NULL || *tailptr == NULL || del == NULL){
    return;
  }
  if(*headptr == del){
    *headptr = del->next;
  }
  if(*tailptr == del){ //must account for tailptr
    *tailptr = del->prev;
  }
  if(del->prev != NULL){
    del->prev->next = del->next;
  }
  if(del->next != NULL){
    del->next->prev = del->prev;
  }
  free(del->name);
  free(del->title);
  free(del);
    
}

void printBackwards(node_t* ending){
  if(ending == NULL){
    printf("The List Is Empty\n");
  }else{
    printf("Printed from end to beginning: \n");
  }
  while(ending != NULL){
    print(ending);
    ending = ending->prev;
  }
}

void delete(node_t** headptr, node_t** tailptr){
  char buffer[BUFFERSIZE] = {'\0'};
  char* artist;
  if(*headptr == NULL){
    printf("The List Is Empty");
    return;
  }else{
    printf("Type which artist's mp3s you want to delete: ");
    if(fgets(buffer, BUFFERSIZE, stdin) != NULL){ 
      int len = strlen(buffer);
      artist = calloc(len,sizeof(char));
      strncpy(artist, buffer, len-1);    
    }
  }
  bool flag = false;
  node_t* current = *headptr;
  node_t* next = NULL;
  while(current != NULL){
    if(strcmp(current->name, artist) == 0 ){
      next = current->next;
      deleteNode(headptr, tailptr, current);
      current = next;     
      flag = true;
    }else{
      current=current->next;
    }
  }
  if(flag == true){
    printf("All songs by %s are now deleted\n", artist);
  }else if(flag == false){
    printf("No MP3s from %s were found!\n", artist);
  }
  free(artist);
}

void freelist(){
  node_t *temp;
  int count = 0;
  while (head != NULL) {
    temp = head;
    head = head->next; 
    free(temp->name);  
    free(temp);        
    count++;
  }
  printf("Deleted Memory For %d MP3 Record(s)...\n", count);
}
