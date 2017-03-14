#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.h"

#define INFINITY 10000
int startingNode = -1;
int worked = 0;

link* initializeNodes(link* list, int numFotos) {

  for (int i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->next = NULL;
  }
  return list;
}

link* addNode(link* list, int lesser, int greater, int* values) {

  link temp;

  if(list[lesser - 1]->next != NULL)
    temp = list[lesser - 1]->next;
  else
    temp = NULL;

  link newNode = malloc(sizeof(struct node));
  newNode->value = greater - 1;
  newNode->next = temp;

  values[newNode->value] = -1;

  list[lesser - 1]->next = newNode;
  return list;
}

int getStartingNode(int* values, int numFotos) {

  int count = 0;
  for (int i = 0; i < numFotos; i++) {

    if(values[i] != -1) {
      startingNode = i;
      count++;
    }
  }
  if(count > 1)
    return -2;
  return startingNode;
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
  int sccCount = 0;
  int low[numFotos];
  int d[numFotos];
  int scc[numFotos];

  for (int i = 0; i < numFotos; i++)
    d[i] = INFINITY;

  link* stack = malloc(sizeof(struct node) * numFotos);

  int a = tarjanVisit(scc, sccCount, list, low, d, list[startingNode], visited, stack, stackTop, numFotos);
  if (a == -1) {
    free(stack);
    return -1;
  } else if (a == -2) {
    free(stack);
    return -2;
  }
  free(stack);

  for(int i = 0; i < numFotos; i++) {

    printf("%d ", scc[i]);
  }
  printf("\n");
  return 1;
}

int tarjanVisit(int* scc, int sccCount, link* list, int* low, int* d, link node, int visited, link* stack, int stackTop, int numFotos) {

  int top = numFotos - 1;
  d[node->value] = visited;
  low[node->value] = visited++;

  stack[stackTop] = node;
  link v = node->next;
  while(v != NULL) {

    if (inStack(v, stack, stackTop) == 1)
      return -1;

    int a = tarjanVisit(scc, sccCount + 1, list,low, d, list[v->value], visited, stack, stackTop + 1, numFotos);
    if (a == -1)
      return -1;
    else if (a == 1)
      return 1;

    low[node->value] = min(low[node->value], low[v->value]);
    v = v->next;

  }

  if(low[node->value] == d[node->value]) {

    while(node != v) {
      v = stack[top--];
      if (v == NULL)
        return -2;
      scc[sccCount] = v->value + 1;
      }
  }
  if (sccCount == numFotos - 1) {
    worked = 1;
  }
  if (sccCount == 0 && worked == 1)
    return 1;

  return -2;
}

int min(int a, int b) {

  if (a <= b)
    return a;

  return b;
}

int inStack(link node, link* stack, int top) {

  for (int i = 0; i < top; i++) {

    if (node->value == stack[i]->value)
      return 1;
  }
  return 0;
}
