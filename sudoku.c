#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   //No se repitan números en las filas
   for(int i = 0; i < 9; i++){
      int fila[10] = {0};
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
            if(fila[n->sudo[i][j]] == 1){
               return 0;
            }
            fila[n->sudo[i][j]] = 1;
         }
      }
   }
   //No se repitan números en las columnas
   for(int i = 0; i < 9; i++){
      int columna[10] = {0};
      for(int j = 0; j < 9; j++){
         if(n->sudo[j][i] != 0){
            if(columna[n->sudo[j][i]] == 1){
               return 0;
            }
            columna[n->sudo[j][i]] = 1;
         }
      }
   }
   //No se repitan números en las submatrices
   for(int i = 0; i < 9; i++){
      int subMatriz[10] = {0};
      int iniciarFila = (i/3)  * 3;
      int iniciarColumna = (i%3) * 3;
      for(int j = 0; j < 3; j++){
         for(int k = 0; k < 3; k++){
            if(n->sudo[iniciarFila + j][iniciarColumna + k] != 0){
               if(subMatriz[n->sudo[iniciarFila + j][iniciarColumna + k] != 0]){
                  if(subMatriz[n->sudo[iniciarFila + j][iniciarColumna + k]] == 1)
                  return 0;
               }
               subMatriz[n->sudo[iniciarFila + j][iniciarColumna + k]] = 1;
            }
         }
      }
   }
   return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

   for (int i = 0; i < 9; i++) {
           for (int j = 0; j < 9; j++) {
               if (n->sudo[i][j] == 0) {
                   // Probar todos los números del 1 al 9
                   for (int num = 1; num <= 9; num++) {
                       Node* newNode = copy(n);
                       newNode->sudo[i][j] = num;
                       if (is_valid(newNode)) {
                           pushBack(list, newNode);
                       } else {
                           free(newNode); // Liberar memoria si el nodo no es válido
                       }
                   }
                   // Solo necesitamos generar nodos para la primera celda vacía encontrada
                   return list;
               }
           }
       }

       return list;
}



int is_final(Node* n){
   for (int i = 0; i < 9; i++){
       for (int j = 0; j < 9; j++){
           if (n->sudo[i][j] == 0){
               return 0;
           }
       }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* stack = createStack();
   push(stack, initial);

   while (!is_empty(stack)){
       Node* n = top(stack);
       pop(stack);
       if (is_final(n)){
           return n;
       }
       List* list = get_adj_nodes(n);
       Node* aux = first(list);
       while (aux){
           push(stack, aux);
           aux = next(list);
       }
       free(n);
      
   }
   
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/