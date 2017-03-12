typedef struct node {

  int value;
  struct node *next;
} *link;

link* initializeNodes(link* list, int numFotos);

link* addNode(link* list, int lesser, int greater);

int tarjanAlgorithm(link* list, int numFotos);

int tarjanVisit(link* list, int* low, int* d, link node, int visited, link* stack, int stackTop);

void sortFrees(link* list, int numFotos);

void freeRow(link node);

int min(int a, int b);

int inStack(link node, link* stack, int top);
