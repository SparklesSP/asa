#include <stdio.h>
#include <stdlib.h>

#define MSG_ERROR      "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"
#define INFINITY 10000

typedef struct node {

  int value;
  struct node *next;
} *link;

link* initializeNodes(link* list, int numFotos);

link* addNode(link* list, int hero, int child, int* values);

int getStartingNode(int* values, int numFotos);

int tarjanAlgorithm(link* list, int numFotos);

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, int numFotos);

void sortFrees(link* list, int numFotos, int* values);

void freeRow(link node);

int min(int a, int b);

int main() {

  int numFotos, numPares;
  scanf("%d%d", &numFotos, &numPares);

  link* list= malloc(sizeof(struct node) * numFotos);
  list = initializeNodes(list, numFotos);

  int *values = calloc(numFotos, sizeof(int));
  int i;
  for (i = 0; i < numPares; i++) {

    int hero, child;
    scanf("%d%d", &hero, &child);
    list = addNode(list, hero, child, values);
  }

  int a = getStartingNode(values, numFotos);

  if (a == -2)
    printf("%s\n", MSG_INCOMPLETE);
  else if(a == -1)
    printf("%s\n", MSG_ERROR);
  else {

    int result = tarjanAlgorithm(list, numFotos);

    if (result == -1)
      printf("%s\n", MSG_ERROR);
    else if (result == -2)
      printf("%s\n", MSG_INCOMPLETE);

  }
  sortFrees(list, numFotos, values);
  return 0;
}


int startingNode = -1;
int worked = 0;

link* initializeNodes(link* list, int numFotos) {
  int i;
  for (i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->next = NULL;
  }
  return list;
}

link* addNode(link* list, int hero, int child, int* values) {

  link newNode = malloc(sizeof(struct node));
  newNode->value = child - 1;
  newNode->next = list[hero - 1]->next;

  values[newNode->value] = -1;
  list[hero - 1]->next = newNode;
  return list;
}

int getStartingNode(int* values, int numFotos) {

  int count = 0;
  int i;
  for (i = 0; i < numFotos; i++) {

    if(values[i] != -1) {
      startingNode = i;
      count++;
    }
  }
  if(count > 1)
    return -2;
  else if(count == 0)
    return -1;

  return startingNode;
}

void sortFrees(link* list, int numFotos, int* values) {
  int i;
  for (i = 0; i < numFotos; i++) {

    freeRow(list[i]);
  }
  free(list);
  free(values);
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
  int scc[numFotos];
  stack = malloc(sizeof(struct node) * numFotos);

  int i;
  for (i = 0; i < numFotos; i++)
    d[i] = INFINITY;

  int a = tarjanVisit(scc, sccCount, list, d, list[startingNode], visited, numFotos);
  if (a == -1)
    return -1;
  else if (a == -2)
    return -2;

  int n;
  for(n = 0; n < numFotos; n++)
    printf("%d ", scc[n]);

  printf("\n");
  return 1;
}

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, int numFotos) {
  d[node->value] = visited++;

  link v = node->next;
  while(v != NULL && worked == 0) {

    if (d[v->value] != INFINITY)
      return -1;

    int a = tarjanVisit(scc, sccCount + 1, list, d, list[v->value], visited, numFotos);
    d[v->value] = INFINITY;
    if (a == -1)
      return -1;
    else if (a == 1)
      return 1;

    v = v->next;
  }
  d[sccCount] = INFINITY;
  scc[sccCount] = node->value + 1;

  if (sccCount == numFotos - 1)
    worked = 1;

  if (sccCount == 0 && worked == 1)
    return 1;

  return -2;
}
