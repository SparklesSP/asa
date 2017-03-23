#include <stdio.h>
#include <stdlib.h>

#define MSG_ERROR      "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"
#define INFINITY 10000

typedef struct node {

  int value;
  int inStack;
  struct node *next;
} *link;

link* initializeNodes(link* list, int numFotos);

link* addNode(link* list, int hero, int child);

int tarjanAlgorithm(link* list, int numFotos);

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, int numFotos);

void sortFrees(link* list, int numFotos);

void freeRow(link node);

int min(int a, int b);

void push(link node, int stackCount);

link pop(int stackCount);

int main() {

  int numFotos, numPares;
  scanf("%d%d", &numFotos, &numPares);

  link* list= malloc(sizeof(struct node) * numFotos);
  list = initializeNodes(list, numFotos);

  int i;
  for (i = 0; i < numPares; i++) {

    int hero, child;
    scanf("%d%d", &hero, &child);
    list = addNode(list, hero, child);
  }

  int result = tarjanAlgorithm(list, numFotos);

  if (result == -1)
    printf("%s\n", MSG_ERROR);
  else if (result == -2)
    printf("%s\n", MSG_INCOMPLETE);


  sortFrees(list, numFotos);
  return 0;
}

int worked = 0;

link* initializeNodes(link* list, int numFotos) {
  int i;
  for (i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->inStack = 0;
    list[i]->next = NULL;
  }
  return list;
}

link* addNode(link* list, int hero, int child) {

  link newNode = malloc(sizeof(struct node));
  newNode->value = child - 1;
  newNode->next = list[hero - 1]->next;
  newNode->inStack = 0;

  list[hero - 1]->next = newNode;
  return list;
}

void sortFrees(link* list, int numFotos) {
  int i;
  for (i = 0; i < numFotos; i++) {

    freeRow(list[i]);
  }
  free(list);
}

void freeRow(link node) {

  if(node->next != NULL)
    freeRow(node->next);

  free(node);
}

link* stack;
int tarjanAlgorithm(link* list, int numFotos) {

  int visited = 0;
  int sccCount = 0;
  int d[numFotos];
  int* low = calloc(numFotos, sizeof(int));
  int scc[numFotos];
  stack = malloc(sizeof(struct node) * numFotos);

  int i;
  for (i = 0; i < numFotos; i++)
    d[i] = INFINITY;

  for (i = 0; i < numFotos; i++)
    if(d[i] == INFINITY)
      int a = tarjanVisit(scc, sccCount, list, d, list[i], visited, numFotos);


  int n;
  for(n = 0; n < numFotos; n++)
    printf("%d ", scc[n]);

  printf("\n");
  return 1;
}

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, int numFotos) {

  d[node->value] = low[node->value] visited++;
  link v = node->next;

  addToStack(node, stackCount++);
  while(v != NULL) {

    if(d[v->value] == INFINITY || v->inStack == 1) {

      if(d[v->value] == INFINITY)
        int a = tarjanVisit(scc, sccCount, list, d, list[v->value], visited, numFotos);

      low[node->value] = min(low[node->value], low[v->value])
    }
    v = v->next;
  }

  if (d[node->value] == low[node->value])
    return -1;

  return -2;
}

void push(link node, int stackCount){

  node->inStack = 1;
  stack[stackCount] = node;
}

link pop(int stackCount) {

  return stack[stackCount];
}

int min(int a, int b) {

  if(a <= b)
    return a

  return b
}
