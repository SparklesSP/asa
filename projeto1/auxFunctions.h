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

int inStack(link node, link* stack, int top);
