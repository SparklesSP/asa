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

link* addNode(link* list, int lesser, int greater, int* values);

int getStartingNode(int* values, int numFotos);

int tarjanAlgorithm(link* list, int numFotos);

int tarjanVisit(int* scc, int sccCount, link* list, int* low, int* d, link node, int visited, link* stack, int stackTop, int numFotos);

void sortFrees(link* list, int numFotos);

void freeRow(link node);

int min(int a, int b);

int main() {

  int numFotos, numPares;
  scanf("%d%d", &numFotos, &numPares);

  link* list= malloc(sizeof(struct node) * numFotos);
  list = initializeNodes(list, numFotos);

  int values[numFotos];
  int i;
  for (i = 0; i < numPares; i++) {

    int lesser, greater;
    scanf("%d%d", &lesser, &greater);
    list = addNode(list, lesser, greater, values);
  }

  int a = getStartingNode(values, numFotos);
  if (a == -2) {

    printf("%s\n", MSG_INCOMPLETE);
  } else if(a == -1) {

    printf("%s\n", MSG_ERROR);
  } else {

    int result = tarjanAlgorithm(list, numFotos);

    if (result == -1)
      printf("%s\n", MSG_ERROR);
    else if (result == -2)
      printf("%s\n", MSG_INCOMPLETE);

  }
  sortFrees(list, numFotos);
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
  int i;
  for (i = 0; i < numFotos; i++) {

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
  int i;
  for (i = 0; i < numFotos; i++) {

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
  int i;
  for (i = 0; i < numFotos; i++)
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
  int n;
  for(n = 0; n < numFotos; n++) {

    printf("%d ", scc[n]);
  }
  printf("\n");
  return 1;
}

int tarjanVisit(int* scc, int sccCount, link* list, int* low, int* d, link node, int visited, link* stack, int stackTop, int numFotos) {

  int top = numFotos - 1;
  d[node->value] = low[node->value] = visited++;

  stack[stackTop] = node;
  link v = node->next;
  while(v != NULL && worked == 0) {

    if (d[v->value] != INFINITY)
      return -1;

    int a = tarjanVisit(scc, sccCount + 1, list,low, d, list[v->value], visited, stack, stackTop + 1, numFotos);
    d[v->value] = INFINITY;
    if (a == -1) {
      return -1;
    }
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
  if (sccCount == numFotos - 1)
    worked = 1;

  if (sccCount == 0 && worked == 1)
    return 1;


  return -2;
}

int min(int a, int b) {

  if (a <= b)
    return a;

  return b;
}
