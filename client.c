#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "node.h"

int main(int argc, char*argv[]){
   
	City *c = readFile(argv[1]);

	if(c != NULL){

		printf("Nome: %s Dim: %d\n", getName(c), getDim(c));
		createDistMatrix(c);
		//printNodes(c);
		freeCity(c);
	}
	
	return 0;
}

/*
name: berlin52
COMMENT: 52 locations in Berlin (Groetschel)
TYPE: TSP
DIMENSION: 52
EDGE_WEIGHT_TYPE: EUC_2D
NODE_COORD_SECTION
1 565.0 575.0
2 25.0 185.0
3 345.0 750.0
4 945.0 685.0
...
52 1740.0 245.0
EOF
*/