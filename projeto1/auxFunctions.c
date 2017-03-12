#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.h"

#define INFINITY 10000
int sccCount = 0;
int startingNode = -1;

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
  int low[numFotos];
  int d[numFotos];
  int scc[numFotos];

  for (int i = 0; i < numFotos; i++)
    d[i] = INFINITY;

  link* stack = malloc(sizeof(struct node) * numFotos);

  int a = tarjanVisit(scc, list, low, d, list[startingNode], visited, stack, stackTop);
  if (a == -1) {
    free(stack);
    return -1;
  } else if (sccCount < numFotos) {
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

int tarjanVisit(int* scc, link* list, int* low, int* d, link node, int visited, link* stack, int stackTop) {

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

      tarjanVisit(scc, list,low, d, v, visited, stack, stackTop);
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
      scc[sccCount] = v->value + 1;
      sccCount++;
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

  for (int i = 0; i < top; i++) {

    if (node->value == stack[i]->value)
      return 1;
  }
  return 0;
}
