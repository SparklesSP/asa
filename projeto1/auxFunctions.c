#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.h"

#define INFINITY 10000

link* initializeNodes(link* list, int numFotos) {

  for (int i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->next = NULL;
  }
  return list;
}

link* addNode(link* list, int lesser, int greater) {

  link temp;

  if(list[lesser - 1]->next != NULL)
    temp = list[lesser - 1]->next;
  else
    temp = NULL;

  link newNode = malloc(sizeof(struct node));
  newNode->value = greater - 1;
  newNode->next = temp;

  list[lesser - 1]->next = newNode;
  return list;
}

void sortFrees(link* list, int numFotos) {
  for (int i = 0; i < numFotos; i++) {

    freeRow(list[i]);
  }
  free(list);
}

void freeRow(link node) {

  if(node->next != NULL) {
    freeRow(node->next);
  }
  free(node);
}

int tarjanAlgorithm(link* list, int numFotos) {

  int visited = 0;
  int stackTop = 0;
  int low[numFotos];
  int d[numFotos];

  for (int i = 0; i < numFotos; i++) {

    d[i] = INFINITY;
  }

  for (int i = 0; i < numFotos; i++) {

    link* stack = malloc(sizeof(struct node) * numFotos);
    if(d[list[i]->value] == INFINITY) {
      int a = tarjanVisit(list, low, d, list[i], visited, stack, stackTop);
      if (a == -1) {
        free(stack);
        return -1;
      }
      free(stack);
    }

  }
  for(int i = 0; i < numFotos; i++) {
    printf("%d ", 1 + d[i]);
  }
  printf("\n");
  return 1;
}

int tarjanVisit(link* list, int* low, int* d, link node, int visited, link* stack, int stackTop) {

  d[node->value] = visited;
  low[node->value] = visited++;

  stack[stackTop++] = node;
  link v = NULL;
  if (node->next != NULL)
    v = list[node->next->value];

  while(v != NULL) {

    if (inStack(v, stack, stackTop) == 1)
      return -1;

    if(d[v->value] == INFINITY) {

      tarjanVisit(list,low, d, v, visited, stack, stackTop);
      low[node->value] = min(low[node->value], low[v->value]);

    }

    if (v->next != NULL)
      v = list[v->next->value];
    else
      v = NULL;
  }

  if(low[node->value] == d[node->value]) {

    v = stack[stackTop--];
    while(node != v) {

      v = stack[stackTop--];
    }
  }
  return 1;
}

int min(int a, int b) {

  if (a <= b)
    return a;

  return b;
}

int inStack(link node, link* stack, int top) {
  int count = 0;
  for (int i = 0; i < top; i++) {

    if (node->value == stack[i]->value)
      count++;
  }
  if (count > 1)
    return 1;
  return 0;
}
