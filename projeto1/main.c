#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.c"

#define MSG_ERROR "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"


int main() {

  int numFotos, numPares;
  scanf("%d%d", &numFotos, &numPares);

  link* list = malloc(sizeof(struct node) * numFotos);

  for (int i = 0; i < numPares; i++) {
    int lesser, greater;

    scanf("%d%d", &lesser, &greater);
    list = addNode(list, lesser, greater);
  }

  

  sortFrees(list, numFotos);
  return 0;
}
