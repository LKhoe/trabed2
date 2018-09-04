#ifndef NODE_H 
#define NODE_H

typedef struct node Node;
typedef struct city City;

char* getName(City* c);
Node* getNodes(City* c);
int getDim(City* c);
void printNodes(City* c);
City* readFile(char* input_file);
City* freeCity(City* c);
float dist(Node a, Node b);
float** createDistMatrix(City* c);





#endif