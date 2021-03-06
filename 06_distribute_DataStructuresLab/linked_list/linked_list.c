#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int value;
    struct item* rest;
} Item;

Item* new_item(int value){
    Item* newitem = (Item *) malloc(sizeof(Item));
    newitem->value = value;
    newitem->rest = NULL;
    return newitem;
}

Item* insert_front(Item* listptr, int value){
    Item* newitem = new_item(value);
    newitem->rest = listptr;
    return newitem;
}


int get(Item* listptr, int index){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (ctr==index){
            return p->value;
        }
        ctr++;
    }
    return -1;
}


void free_all(Item* listptr) {
    Item *p;
    Item *next;
    for(p = listptr; p!= NULL; p = next){
        next = p->rest;
        free(p);
    }
}

int get_index(Item* listptr, int value){
  Item* p;
  int index = 0;

  for(p=listptr; p != NULL; p=p->rest,index++){
    if(p->value == value) {
      return index;
    }
  }

  return -1;
}

Item* remove_item(Item* listptr, int value){
  Item *curr, *prev;
  int first = 1;

  for(curr=listptr; curr != NULL; curr= curr->rest){
    if(curr->value == value){

      // if the value was found at the first location
      if(first) {
        prev = curr->rest;
        free(curr);
        return prev;
      }

      // not the first location
      else {
        prev->rest = curr->rest;
        free(curr);
        return listptr;
      }
    }
    prev = curr;

    if(first) {
      first = 0;
    }
  }

  // item not found
  return NULL;
}


int main(){
    Item* listptr;
    int i;
    listptr = new_item(0);
    for (i=1; i < 6; i++){
        listptr=insert_front(listptr, i);
    }
    for (i=0; i < 6; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    listptr = remove_item(listptr, 3);
    for (i=0; i <= 5; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    printf("Index for 3 %d\n", get_index(listptr, 3));
    printf("Index for 2 %d\n", get_index(listptr, 2));
    printf("Index for 1 %d\n", get_index(listptr, 1));

    free_all(listptr);
}
