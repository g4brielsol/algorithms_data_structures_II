#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// definicao da quantidade maxima e minima de nos
#define MAX 3
#define MIN 2
// struct para armazenar as informacoes dos alunos
struct aluno {
  int numero_usp;
  char nome[50];
  char sobrenome[50];
  char curso[50];
  float nota;
};

// struct dos nos da arvore B
struct no_arvoreB {
  struct aluno item[MAX + 1];
  int count;
  struct no_arvoreB *link[MAX + 1];
};
// definicao do no raiz da arvore
struct no_arvoreB *root;

// funcao para criar um no da arvore
struct no_arvoreB *criarNode(struct aluno *item, struct no_arvoreB *filho) {
  struct no_arvoreB *novoNo;
  novoNo = (struct no_arvoreB *)malloc(sizeof(struct no_arvoreB));
  novoNo->item[1] = *item;
  novoNo->count = 1;
  novoNo->link[0] = root;
  novoNo->link[1] = filho;
  return novoNo;
}

// funcao para inserir um aluno na arvore em relacao a posicao a ser inserida calculada na funcao colocarValorNo
void inserirValor(struct aluno aluno_a_inserir, int pos, 
                  struct no_arvoreB *node, struct no_arvoreB *filho) {
  // j = quantidade de nos existentes
  int j = node->count;
  // desloca os nos nas posicoes enquanto nao chegar a posicao a ser inserida o novo
  while (j > pos) {
    node->item[j + 1] = node->item[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  // copia os valores do aluno a ser inserido na posicao desejada
  node->item[j + 1].numero_usp = aluno_a_inserir.numero_usp;
  strcpy(node->item[j + 1].nome, aluno_a_inserir.nome);
  strcpy(node->item[j + 1].sobrenome, aluno_a_inserir.sobrenome);
  strcpy(node->item[j + 1].curso, aluno_a_inserir.curso);
  node->item[j + 1].nota = aluno_a_inserir.nota;
  // no filho é inserido na posicao desejada
  node->link[j + 1] = filho;
  // valor de nós é incrementado
  node->count++;
}

// funcao para dividir o no e criar outro para fazer a ordenacao correta
void dividirNo(struct aluno aluno_a_inserir, struct aluno **pval, int pos,
              struct no_arvoreB *node, struct no_arvoreB *filho, struct no_arvoreB **novoNo) {
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
  *novoNo = (struct no_arvoreB *)malloc(sizeof(struct no_arvoreB));
  j = median + 1;
  // copia o valor do no pai para o fim do novo no
  while (j <= MAX) {
    (*novoNo)->item[j - median] = node->item[j];
    (*novoNo)->link[j - median] = node->link[j];
    j++;
  }
  // altera a quantidade de valores do no pai
  node->count = median;
  (*novoNo)->count = MAX - median;

  // se pos for 0, 1 ou 2. insere o no pai
  if (pos <= MIN)
  {
    inserirValor(aluno_a_inserir, pos, node, filho);
  }
  // senao insere o novo no
  else
  {
    inserirValor(aluno_a_inserir, pos - median, *novoNo, filho);
  }

  //altera os valores do aluno no inserir para o maior valor do no pai
  (*pval)->numero_usp = node->item[node->count].numero_usp;
  strcpy((*pval)->nome, node->item[node->count].nome);
  strcpy((*pval)->sobrenome, node->item[node->count].sobrenome);
  strcpy((*pval)->curso, node->item[node->count].curso);
  (*pval)->nota = node->item[node->count].nota;
  // altera o valor do primeiro no filho do novo no para o maior valor do no pai
  (*novoNo)->link[0] = node->link[node->count];
  // decrementa a quantidade de valores do no pai
  node->count--;
}

// funcao para inserir o valor do aluno a ser inserido
int colocarValorNo(struct aluno aluno_a_inserir, struct aluno **pval, struct no_arvoreB *node, struct no_arvoreB **filho) {
  int pos;
  struct aluno *copia = malloc(sizeof(struct aluno));
  // se não tiver pai e retorna 1
  if (!node) {
    // insere os valores ao no para ser inserido
    copia->numero_usp = aluno_a_inserir.numero_usp;
    strcpy(copia->nome, aluno_a_inserir.nome);
    strcpy(copia->sobrenome, aluno_a_inserir.sobrenome);
    strcpy(copia->curso, aluno_a_inserir.curso);
    copia->nota = aluno_a_inserir.nota;
    // valor do aluno na funcao inserir() vai ser o valor do item
    *pval = copia;
    // valor do filho é nulo
    *filho = NULL;
    return 1;
  }
  // se o valor for menor que o segundo valor do nó pai
  if (aluno_a_inserir.numero_usp < node->item[1].numero_usp) 
  {
    // a posicao sera a inicial
    pos = 0;
  }
  // se o valor for maior ou igual que o segundo valor do nó pai 
  else 
  {
    // comeca no maior valor do no pai, checa do maior para o menor
    // para ver se tem itens com mesmo valor, se nao tiver o valor
    // de pos sera 1
    for (pos = node->count; (aluno_a_inserir.numero_usp < node->item[pos].numero_usp && pos > 1); pos--)
    {  
      // se o valor for igual a algum nó do nó pai, retorna 0
      if (aluno_a_inserir.numero_usp == node->item[pos].numero_usp) {
        return 0;
      }
    }
  }
  // se retornar 1 na chamada do colocarValorNo com pos 0 ou 1
  if (colocarValorNo(aluno_a_inserir, pval, node->link[pos], filho)) 
  {
    // se a quantidade de nós atual é menor que o máximo
    if (node->count < MAX)
    {
      // insere o nó
      inserirValor(aluno_a_inserir, pos, node, *filho);
    } 
    // se a quantidade de nós for igual ao máximo
    else 
    {
      // vai dividir a arvore para ordenar da maneira certa
      dividirNo(aluno_a_inserir, pval, pos, node, *filho, filho);
      return 1;
    }
  }
  return 0;
}

// funcao para inserir o aluno na arvore
void inserir(struct aluno aluno_a_inserir) {
  // flag para criar no
  int flag; 
  // valor a ser alterado para copiar para o novo no
  struct aluno *i= NULL;
  struct no_arvoreB *filho;

  // se retornar 1, cria o no e linka com o filho
  flag = colocarValorNo(aluno_a_inserir, &i, root, &filho);
  if (flag)
    root = criarNode(i, filho);
}

// funcao para procurar registro, modifica o ponteiro para 1 caso encontre o registro
void procurar_registro(struct no_arvoreB *myNode, int numero_usp, int *registro_existente) {
  int i;
  // se existir o no
  if (myNode) {
    // para a quantidade de nos existentes do no atual
    for (i = 0; i < myNode->count; i++) {
      // recursao nos nos filhos
      procurar_registro(myNode->link[i], numero_usp, registro_existente);
      // printa o valor em ordem do no
      if ((myNode->item[i + 1].numero_usp == numero_usp) && (myNode->item[i + 1].numero_usp > 0)){
          *registro_existente = 1;
      }
    }
    // chama a recursao do nó com maior valor
    procurar_registro(myNode->link[i], numero_usp, registro_existente);
  }
}

// Alterar o valor do nó a ser printado
void printar_dados(struct no_arvoreB *myNode, int numero_usp, struct aluno *printar_aluno) {
  int i;
  // se existir o no
  if (myNode) {
    // para a quantidade de nos existentes do no atual
    for (i = 0; i < myNode->count; i++) {
      // recursao nos nos filhos
      printar_dados(myNode->link[i], numero_usp, printar_aluno);
      // ao encontrar o valor a ser printado, altera o ponteiro do nó para printar
      if (myNode->item[i + 1].numero_usp == numero_usp)
      {
         printar_aluno->numero_usp = myNode->item[i + 1].numero_usp;
         strcpy(printar_aluno->nome, myNode->item[i + 1].nome);
         strcpy(printar_aluno->sobrenome, myNode->item[i + 1].sobrenome);
         strcpy(printar_aluno->curso, myNode->item[i + 1].curso);
         printar_aluno->nota = myNode->item[i + 1].nota;
      }
    }
  // chama a recursao do nó com maior valor
  printar_dados(myNode->link[i], numero_usp, printar_aluno);
  }
}


// fazer o update dos valores do aluno
void update_aluno(struct no_arvoreB *myNode, struct aluno aluno) {
  int i;
  // se existir o no
  if (myNode) {
    // para a quantidade de nos existentes do no atual
    for (i = 0; i < myNode->count; i++) {
      // recursao nos nos filhos
      update_aluno(myNode->link[i], aluno);
      // printa o valor em ordem do no
      if ((myNode->item[i + 1].numero_usp == aluno.numero_usp)){
        myNode->item[i + 1].numero_usp = aluno.numero_usp;
        strcpy(myNode->item[i + 1].nome, aluno.nome);
        strcpy(myNode->item[i + 1].sobrenome, aluno.sobrenome);
        strcpy(myNode->item[i + 1].curso, aluno.curso);
        myNode->item[i + 1].nota = aluno.nota;
      }
    }
    // chama a recursao do nó com maior valor
    update_aluno(myNode->link[i], aluno);
  }
}

// deletar registro em memória
void deletar_registro(struct no_arvoreB *myNode, int numero_usp) {
  int i;
  // se existir o no
  if (myNode) {
    // para a quantidade de nos existentes do no atual
    for (i = 0; i < myNode->count; i++) {
      // recursao nos nos filhos
      deletar_registro(myNode->link[i], numero_usp);
      // printa o valor em ordem do no
      if ((myNode->item[i + 1].numero_usp == numero_usp)){
          myNode->item[i + 1].numero_usp = -1;
      }
    }
    // chama a recursao do nó com maior valor
    deletar_registro(myNode->link[i], numero_usp);
  }
}

int main()
{
    FILE *Arq;
    Arq=fopen("3.in","rt");
    // caractere que delimita a separacao no csv
    char virgula_espaco[4] = "\" ,", espaco[2] = " ", informacao[100];
    // token para pegar as informacoes separadas por "," e " " no strtok
    char *token;
    // definicao das variaveis
    int numero_usp, registro_existente;;
    char  curso_1[50], curso_2[50], curso_3[50], comando[7];
    struct aluno aluno_lido;
    
    // loop para pegar as informacoes em csv
    while(fgets(informacao, sizeof(informacao), Arq) != NULL) {
    //while(fgets(informacao, sizeof(informacao), stdin) != NULL) {        
        token = strtok(informacao, virgula_espaco);
        // pegar as informacoes separadas por virgula
        while( token != NULL ) {
            // pega o char com o comando
            strcpy(comando, token);
            if(strcmp(comando, "insert") == 0)
            {
                // retira o comando inicial da frase
                // transforma o char em int para o numero usp
                token = strtok(NULL, virgula_espaco);
                numero_usp = atoi(token);
                aluno_lido.numero_usp = atoi(token);
                // assume que o registro nao existe
                registro_existente = -1;
                // se o registro existir, o valor da variavel registro_existente
                // sera modificado para 1
                procurar_registro(root, numero_usp, &registro_existente);
                // se o registro nao existir
                if(registro_existente == -1)
                {
                    // pega o char com o nome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(aluno_lido.nome, token);
                    // pega o char com o sobrenome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(aluno_lido.sobrenome, token);
                    // pega o char com parte do nome do curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_1, token);
                    // pega o char com parte do nome do curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_2, token);
                    // pega o char com parte do nome do curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_3, token);
                    // concatena o nome do curso e coloca na variavel do aluno
                    strcpy(aluno_lido.curso, "");
                    strcat(curso_1, espaco);
                    strcat(curso_1, curso_2);
                    strcat(curso_1, espaco);
                    strcat(curso_1, curso_3);
                    strcat(aluno_lido.curso, curso_1);
                    // transforma o char da nota em float
                    token = strtok(NULL, virgula_espaco);
                    aluno_lido.nota = atof(token);
                    // insere o aluno na arvore
                    inserir(aluno_lido);
                  }
                else
                {
                    printf("O Registro ja existe %d!\n", numero_usp);
                }
            }
            else if(strcmp(comando, "search") == 0)
            {
              // retira o comando inicial da frase
              // transforma o char em int para o numero usp
              token = strtok(NULL, virgula_espaco);
              numero_usp = atoi(token);
              // assume que o registro nao existe
              registro_existente = -1;
              procurar_registro(root, numero_usp, &registro_existente);
              // se o registro nao existir
              if(registro_existente == -1)
              {
                  printf("Registro nao encontrado!\n");
              }
              // se o registro existir
              else
              {
                  // procura o aluno a ser printado e aloca os valore no ponteiro para printar
                  struct aluno printar_aluno;
                  printar_dados(root, numero_usp, &printar_aluno);
                  printf("-------------------------------\n");
                  printf("nUSP: %d\n", printar_aluno.numero_usp);
                  printf("Nome: %s\n", printar_aluno.nome);
                  printf("Sobrenome: %s\n", printar_aluno.sobrenome);
                  printf("Curso: %s\n", printar_aluno.curso);
                  printf("Nota: %.2f\n", printar_aluno.nota);
                  printf("-------------------------------\n");
              }
            }
            // se o comando for delete
            else if(strcmp(comando, "delete") == 0)
            {
              // retira o comando inicial da frase
              // transforma o char em int para o numero usp
              token = strtok(NULL, virgula_espaco);
              numero_usp = atoi(token);
              // assume que o registro nao existe
              registro_existente = -1;
              // procura o registro e caso exista o valor da
              // variavel registro_existente será 1
              procurar_registro(root, numero_usp, &registro_existente);
              if(registro_existente == -1)
              {
                  printf("Registro nao econtrado!\n");
              }
              else
              {
                  deletar_registro(root, numero_usp);
              }
            }
            else if(strcmp(comando, "update") == 0)
            {
              // retira o comando inicial da frase
              // transforma o char em int para o numero usp
              token = strtok(NULL, virgula_espaco);
              numero_usp = atoi(token);
              aluno_lido.numero_usp = atoi(token);
              // assume que o registro nao existe
              registro_existente = -1;
              // se o registro existir, o valor da variavel
              // registro_existente sera 1
              procurar_registro(root, numero_usp, &registro_existente);
              if(registro_existente == 1)
              {
                // pega o char com o nome
                token = strtok(NULL, virgula_espaco);
                strcpy(aluno_lido.nome, token);
                // pega o char com o sobrenome
                token = strtok(NULL, virgula_espaco);
                strcpy(aluno_lido.sobrenome, token);
                // pega o char com o curso
                token = strtok(NULL, virgula_espaco);
                strcpy(curso_1, token);
                // pega o char com o curso
                token = strtok(NULL, virgula_espaco);
                strcpy(curso_2, token);
                // concatenar o nome do novo curso no aluno
                strcpy(aluno_lido.curso, "");
                strcat(curso_1, espaco);
                strcat(curso_1, curso_2);
                strcat(aluno_lido.curso, curso_1);
                // pega o valor da nova nota
                token = strtok(NULL, virgula_espaco);
                aluno_lido.nota = atof(token);
                update_aluno(root, aluno_lido);
              }
            }
            else if(strcmp(comando, "exit") == 0)
            {
                break;
            }
        // pega proximo token
        token = strtok(NULL, virgula_espaco);             
        }
    }
    return 0;

}
