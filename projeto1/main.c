#include <stdio.h>
#include <stdlib.h>
#include "auxFunctions.c"

#define MSG_ERROR      "Incoerente"
#define MSG_INCOMPLETE "Insuficiente"

int main() {

  int numFotos, numPares;
  scanf("%d%d", &numFotos, &numPares);

  link* list= malloc(sizeof(struct node) * numFotos);
  list = initializeNodes(list, numFotos);

  int values[numFotos];
  for (int i = 0; i < numPares; i++) {

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
