typedef struct node {

  int value;
  struct node *next;
} *link;

link* addNode(link* list, int lesser, int greater);
void sortFrees(link* list, int numFotos);
void freeRow(link node);
