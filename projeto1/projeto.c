/*
*
*      Marcos Faria - 84742  || Grupo TG046
*
*/
#include <stdio.h>
#include <stdlib.h>

#define MSG_ERROR      "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"
#define INFINITY 10000
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node {

  int value;
  int color;
  struct node *next;
} *link;

void initializeNodes(link* list, int numFotos);
void addNode(link* list, int hero, int child);
void dfs(link* list, int numFotos, int* path);
void dfsVisit(link* list, link node, int* path, int numFotos);
int isSuficient(int* path, int numFotos, link* list);
void sortPrints(int* path, int numFotos);
void sortFrees(link* list, int numFotos, int* path);
void freeRow(link node);

int cycles = 0;
int pathCount = 0;

/*

-------------------------------- MAIN

*/
int main() {

  int numFotos = 0;
  int numPares = 0;
  scanf("%d%d", &numFotos, &numPares);

  link* list= calloc(numFotos, sizeof(struct node));
  initializeNodes(list, numFotos);
  int* path = calloc(numFotos, sizeof(int));

  int i;
  for (i = 0; i < numPares; i++) {

    int hero, child;
    scanf("%d%d", &hero, &child);
    addNode(list, hero, child);
  }

  dfs(list, numFotos, path);

  if (cycles == 1) {

    printf("%s\n", MSG_ERROR);
    sortFrees(list, numFotos, path);
    return 0;
  }
  if (isSuficient(path, numFotos, list) == 0) {

    printf("%s\n", MSG_INCOMPLETE);
    sortFrees(list, numFotos, path);
    return 0;
  }

  sortPrints(path, numFotos);
  sortFrees(list, numFotos, path);
  return 0;
}

/*

-------------------------------- Auxiliar Functions


*/

void sortPrints(int* path, int numFotos) {

  printf("%d", path[numFotos - 1] + 1);
  int i;
  for (i = numFotos - 2; i >= 0; i--)
    printf(" %d", path[i] + 1);
  printf("\n");

}

void initializeNodes(link* list, int numFotos) {

  int i;
  for (i = 0; i < numFotos; i++) {

    list[i] = malloc(sizeof(struct node));
    list[i]->value = i;
    list[i]->next = NULL;
  }
}

void addNode(link* list, int hero, int child) {

  link newNode = malloc(sizeof(struct node));
  newNode->value = child - 1;
  newNode->next = list[hero - 1]->next;

  list[hero - 1]->next = newNode;
}

void sortFrees(link* list, int numFotos, int* path) {
  int i;
  for (i = 0; i < numFotos; i++) {

    freeRow(list[i]);
  }
  free(path);
  free(list);
}

void freeRow(link node) {

  if(node->next != NULL)
    freeRow(node->next);

  free(node);
}

void dfs(link* list, int numFotos, int* path) {

  int i;
  for (i = 0; i < numFotos; i++)
    if (list[i]->color == WHITE)
      dfsVisit(list, list[i], path, numFotos);

}

void dfsVisit(link* list, link node, int* path, int numFotos) {

  node->color = GRAY;
  link v = node->next;
  while (v != NULL){

    if (list[v->value]->color == GRAY) {

      cycles = 1;
      return;
    }
    else if(list[v->value]->color == WHITE) {

      dfsVisit(list, list[v->value], path, numFotos);
    }
    v = v->next;
  }
  node->color = BLACK;
  path[pathCount++] = node->value;
}

int isSuficient(int* path, int numFotos, link* list) {

  int i;
  for (i = numFotos - 1; i > 0;) {

    link child = list[path[i--]];
    link parent = list[path[i]];

    link v = list[child->value];
    while (v != NULL && cycles == 0) {

      if(v->value == parent->value)
        break;
      v = v->next;
    }
    if (v == NULL)
      return 0;
  }
  return 1;
}
