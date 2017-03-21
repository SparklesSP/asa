#include <stdio.h>
#include <stdlib.h>

#define MSG_ERROR      "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"
#define INFINITY 10000

typedef struct node {

  int value;
  int* nexts;
  int numNexts;

} *link;

link* initializeNodes(link* list, int numFotos);

link* addNode(link* list, int lesser, int greater, int* values);

int getStartingNode(int* values, int numFotos, int* d);

int tarjanAlgorithm(link* list, int numFotos, int* d);

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, link* stack, int stackTop, int numFotos);

void sortFrees(link* list, int numFotos);

int min(int a, int b);

int worked = 0;

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

  int d[numFotos];
  int a = getStartingNode(values, numFotos, d);
  if (a == -2) {

    printf("%s\n", MSG_INCOMPLETE);
  } else if(a == -1) {

    printf("%s\n", MSG_ERROR);
  } else {

    int result = tarjanAlgorithm(list, numFotos, d);

    if (result == -1)
      printf("%s\n", MSG_ERROR);
    else if (result == -2)
      printf("%s\n", MSG_INCOMPLETE);

  }
  sortFrees(list, numFotos);
  return 0;
}


int startingNode = -1;

link* initializeNodes(link* list, int numFotos) {
  int i;
  for (i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->numNexts = 0;
    list[i]->nexts = malloc(sizeof(int) * numFotos);
  }
  return list;
}

link* addNode(link* list, int lesser, int greater, int* values) {

  values[greater - 1] = -1;
  list[lesser - 1]->nexts[list[lesser - 1]->numNexts++] = greater - 1;
  return list;
}

int getStartingNode(int* values, int numFotos, int* d) {

  int count = 0;
  int i;
  for (i = 0; i < numFotos; i++) {

    d[i] = INFINITY;
    if(values[i] != -1) {
      startingNode = i;
      count++;
    }
  }
  if(count > 1)
    return -2;
  return startingNode;
}

int tarjanAlgorithm(link* list, int numFotos, int* d) {

  int visited = 0;
  int stackTop = 0;
  int sccCount = 0;
  int scc[numFotos];

  link* stack = malloc(sizeof(struct node) * numFotos);

  int a = tarjanVisit(scc, sccCount, list, d, list[startingNode], visited, stack, stackTop, numFotos);
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

int tarjanVisit(int* scc, int sccCount, link* list, int* d, link node, int visited, link* stack, int stackTop, int numFotos) {

  d[node->value] = visited++;

  stack[stackTop] = node;
  link v;
  int i = 0;
  int value = node->value;
  if (node->numNexts > 0)
    for (i = 0; i < node->numNexts && worked == 0; i++) {

      v = list[node->nexts[i]];
      if (d[v->value] != INFINITY)
        return -1;
      int a = tarjanVisit(scc, sccCount + 1, list, d, v, visited, stack, stackTop + 1, numFotos);
      d[value] = INFINITY;
      if (a == -1)
        return -1;
    }



  if (sccCount == numFotos - 1)
    worked = 1;

  scc[sccCount] = stack[sccCount]->value + 1;

  if (sccCount == 0 && worked == 1)
    return 1;
  d[value] = INFINITY;
  return -2;


}

int min(int a, int b) {

  if (a <= b)
    return a;

  return b;
}

void sortFrees(link* list, int numFotos) {

  int i;
  for (i = 0; i < numFotos; i++) {

    free(list[i]->nexts);
    free(list[i]);
  }
  free(list);
}
