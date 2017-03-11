#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.h"

link* addNode(link* list, int lesser, int greater) {

  link temp;

  if(list[lesser - 1]->next != NULL)
    temp = list[lesser - 1]->next;
  else
    temp = NULL;

  link newNode = malloc(sizeof(struct node));
  newNode->value = greater;

  list[lesser - 1]->next = newNode;
  newNode->next = NULL;

  return list;
}

void sortFrees(link* list, int numFotos) {
  for (int i = 0; i < numFotos; i++) {

    freeRow(list[i]);
  }
  free(list);
}

void freeRow(link node) {

  while(node->next != NULL) {
    freeRow(node->next);
  }
  free(node);
}
