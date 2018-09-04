#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "node.h"

#define MAX_TAM_STR 50
#define equalString(A,B) (strcmp(A, B) == 0)

struct node {
    int id;
    float x;
    float y;
};

struct city {
    char* name;
    Node* nodes;
    int dim;
};

char* getName(City* c){
    return c->name;
}

Node* getNodes(City* c){
    return c->nodes;
}

int getDim(City* c){
    return c->dim;
}

void printNodes(City* c){
    for(int i = 0;i < c->dim;i++){
        printf("[%d] %.1f %.1f\n",c->nodes[i].id,c->nodes[i].x,c->nodes[i].y);
    }
}

City* readFile(char* input_file){
    FILE* input = fopen(input_file, "r");  
    char* trsh     = malloc(MAX_TAM_STR*sizeof(char));
    char* temp     = malloc(MAX_TAM_STR*sizeof(char));
    char* aux_name = malloc(MAX_TAM_STR*sizeof(char));
    int   aux_dim;
       
	fscanf(input,"%s %s", trsh, aux_name); //Ignora "NAME:" e armazena o nome do problema em aux_name.
    
    while(!equalString(trsh,"TYPE:")){ //Loop para ignorar o comentário do arquivo de entrada.
        fscanf(input,"%s", trsh);
    }
    
    fscanf(input,"%s", temp); //Lê o campo TYPE e armazena em uma variável temporária.

    if(!equalString(temp,"TSP")){ //Verifica o valor de temp. Se TYPE é diferente de "TSP", devemos parar a leitura do arquivo,pois é um tipo inválido.
        free(trsh);
        free(temp);
        free(aux_name);
        fclose(input);
        return NULL;
    }
 
    fscanf(input,"%s %d", trsh, &aux_dim); //Ignora "dim:" e armazena o número de cidades. 
    
    fscanf(input,"%s %s", trsh, temp); //Lê o campo EDGE_WEIGHT_TYPE e armazena em uma variável temporária.

    if(!equalString(temp,"EUC_2D")){ //Verifica o valor de temp.Se EDGE_WEIGHT_TYPE é diferente de "EUC_2D", devemos parar a leitura do arquivo,pois é a única opção válida que indica distancia Euclidiana em um plano 2D.
        free(trsh);
        free(temp);
        free(aux_name);
        fclose(input);
        return NULL;
    }

    fscanf(input,"%s", trsh); //Ignora "NODE_COORD_SECTION".

    City* new   = malloc(sizeof(City));
    new->nodes = malloc(aux_dim*sizeof(Node));

    for(int i = 0; i < aux_dim; i++){ //Loop para ler o id e as coordenadas dos pontos.
        fscanf(input,"%d %f %f\n", &new->nodes[i].id, &new->nodes[i].x, &new->nodes[i].y);
    }

    new->name = malloc ((strlen(aux_name)+1)*sizeof(char));
    strcpy(new->name, aux_name);
    new->dim = aux_dim;
    free(trsh);
    free(temp);
    free(aux_name);
    fclose(input);

    return new; //Retornamos a City criada, com seus respectivos campos preenchidos.
}

City* freeCity(City* c){
    free(c->name);
    free(c->nodes);
    free(c);            
    return NULL;
}

float dist(Node a, Node b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float** createDistMatrix(City* c){
    Node* n = getNodes(c);
    float** mat = malloc((c->dim)*sizeof(float*));
    for(int i = 1; i < c->dim; i++){
        mat[i]= malloc((i+1)*sizeof(float));
    }
  
    for(int i = 0; i < getDim(c); i++){
        for(int j=0; j < i+1; j++){
            mat[i][j] = dist(n[i], n[j]);
        }
    }

    for(int i = 0; i < getDim(c); i++){
        for(int j=0; j < i+1; j++){
            printf("%2.0f ", mat[i][j]);
        }
        printf("\n");
    }
    return mat;
}