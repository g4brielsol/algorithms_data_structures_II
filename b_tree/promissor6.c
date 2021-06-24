// Agora está tudo funfando com o numero USP e Nota, só testar com as outras variáveis


// insertioning a key on a B-tree in C
// esse aqui vai, fé no pai


#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct aluno {
  int numero_usp;
  float nota;

};

struct btreeNode {
  struct aluno item[MAX + 1];
  int count;
  struct btreeNode *link[MAX + 1];
};

struct btreeNode *root;

// Node creation
struct btreeNode *createNode(struct aluno *item, struct btreeNode *child) {
  struct btreeNode *newNode;
  newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  newNode->item[1] = *item;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert
// valor do i na funcao insertion, posicao a ser inserida, no pai, no a inserir
void insertValue(int item, float nota, int pos, struct btreeNode *node, struct btreeNode *child) {
  // j = quantidade de nos existentes
  int j = node->count;
  // desloca os nos nas posicoes enquanto nao chegar a posicao a ser inserida o novo
  while (j > pos) {
    node->item[j + 1] = node->item[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  // valor do i na funcao insertion é inserido na posicao desejada
  node->item[j + 1].numero_usp = item;
  node->item[j + 1].nota = nota;
  // no child é inserido na posicao desejada
  node->link[j + 1] = child;
  // valor de nós é incrementado
  node->count++;
  //printf("test %d\n", item);//node->item[j + 1].numero_usp); FUNCIONANDO MAS VALOR 0
}

// Split node
// (itme )valor do i na funcao insertion, (*pval) ponteiro para i na funcao insertion, posicao a ser inserida (pos),
void splitNode(int item, float nota, struct aluno **pval, int pos,
              //no pai, no a inserir, ponteiro para no a inserir
              struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode) {
  int median, j;

  // se pos > 2
  if (pos > MIN)
  {
    //median = 3
    median = MIN + 1;
  }
  else
  {
    // senao median = 2
    median = MIN;
  }

  // aloca um novo no em memoria
  *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
  j = median + 1;
  // copia o valor do no pai para o fim do novo no
  while (j <= MAX) {
    (*newNode)->item[j - median] = node->item[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  // altera a quantidade de valores do no pai
  node->count = median;
  (*newNode)->count = MAX - median;

  // se pos for 0, 1 ou 2. insere o no pai
  if (pos <= MIN)
  {
    insertValue(item, nota, pos, node, child);
  }
  // senao insere o novo no
  else
  {
    insertValue(item, nota, pos - median, *newNode, child);
  }

  // altera o valor do i no insertion para o maior valor do no pai
  (*pval)->numero_usp = node->item[node->count].numero_usp;
  (*pval)->nota = node->item[node->count].nota;
  // altera o valor do primeiro no filho do novo no para o maior valor do no pai
  (*newNode)->link[0] = node->link[node->count];
  // decrementa a quantidade de valores do no pai
  node->count--;
}

// Set the value of node
       // valor do insert, posicao memoria i,          root,                  nó filho
int setNodeValue(int item, float nota, struct aluno **pval, struct btreeNode *node, struct btreeNode **child) {
  int pos;
  struct aluno *copia = malloc(sizeof(struct aluno));
  // se não tiver pai e retorna 1
  if (!node) {
    copia->numero_usp = item;
    copia->nota = nota;
    // printf("test %d\n", copia->numero_usp);FUNCIONANDO
    // valor do i na funcao insertion() vai ser o valor do item
    *pval = copia;
    // valor do child é nulo
    *child = NULL;
    //printf("test POINTER POINTER %d\n", (*pval)->numero_usp); // FUNCIONANDO
    return 1;
  }
  // se o valor for menor que o 2 valor do nó pai
  if (item < node->item[1].numero_usp) 
  {
    // a posicao sera a inicial
    pos = 0;
  }
  // se o valor for maior ou igual que o 2 valor do nó pai 
  else 
  {
    // comeca no maior valor do no pai, checa do maior para o menor
    // para ver se tem itens como mesmo valor, se nao tiver o valor
    // de pos sera 1
    for (pos = node->count; (item < node->item[pos].numero_usp && pos > 1); pos--)
    {  
      // se o valor for igual a algum nó do no pai e retorna 0
      if (item == node->item[pos].numero_usp) {
        printf("Duplicates not allowed\n");
        return 0;
      }
    }
  }
  // se retornar 1 na chamada do setNodeValue com pos 0 ou 1
  if (setNodeValue(item, nota, pval, node->link[pos], child)) 
  {
    // se a quantidade de nós atual é menor que o máximo
    if (node->count < MAX)
    {
      // insere o nó
      //printf("test %d\n", item); FUNCIONANDO MAS 0
      //insertValue(copia->numero_usp, pos, node, *child);
      insertValue(item, nota, pos, node, *child);
    } 
    // se a quantidade de nós for igual ao máximo
    else 
    {
      //printf("test %d\n", item);
      // faz o split dos nós
      //splitNode(copia->numero_usp, pval, pos, node, *child, child);
      splitNode(item, nota, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insertion(int item, float nota) {
  // flag para criar no
  int flag; 
  // valor a ser alterado para copiar para o novo no
  struct aluno *i= NULL;
  struct btreeNode *child;

  // se retornar 1, cria o no e linka com o filho
  flag = setNodeValue(item, nota, &i, root, &child);
  if (flag)
    root = createNode(i, child);
}

// Traverse the tree
void traversal(struct btreeNode *myNode) {
  int i;
  // se existir o no
  if (myNode) {
    // para a quantidade de nos existentes do no atual
    for (i = 0; i < myNode->count; i++) {
      // recursao nos nos filhos
      traversal(myNode->link[i]);
      // printa o valor em ordem do no
      printf("%d %f\n ", myNode->item[i + 1].numero_usp, myNode->item[i + 1].nota);
    }
    // chama a recursao do nó com maior valor
    traversal(myNode->link[i]);
  }
}

int main() {
  //int item, ch;

  insertion(1, 1.4);
  insertion(2, 2.7);
  insertion(3, 3.1);
  insertion(4, 4.2);
  insertion(5, 5.8);
  insertion(10000000, 10000000.43);
  insertion(7, 7.9);
  insertion(8, 8.4);
  insertion(9, 9.3);
  insertion(10, 10.4);
  insertion(11, 11.4);
  insertion(12, 12.3);
  insertion(13, 13.6);
  insertion(14, 14.4);
  insertion(15, 15.9);
  insertion(16, 16.2);
  insertion(17, 17.5);
  insertion(18, 18.9);
  insertion(19, 19.7);
  insertion(20, 20.6);

  traversal(root);
}