#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funcao para pegar a ultima posicao do arquivo
long int file_size(FILE *pFile, char nome_arquivo[10])
{
    // variavel para armazenar a ultima posicao do arquivo
    long int index_final;
    // vai para o fim do arquivo
    fseek(pFile, 0, SEEK_END);
    // armazena o valor da ultima posicao no arquivo
    index_final = ftell(pFile);
    // retorna o long int
    return index_final;
}

// Funcao para printar as informacoes conforme o exercicio pede
void print_file_data(FILE *pFile, long int comeco, long int index_final)
{
    // muda a posicao inicial no arquivo de acordo com a operacao escolhida
    fseek(pFile, comeco, SEEK_SET);
    // enquanto a posicao do arquivo for menor que a posicao final indicada pela operacao
    while(ftell(pFile) < index_final) 
    {
        // definicao das variaveis
        int numero_usp;
        char nome[50], curso[50];
        float nota;
        // le os parametros
        fread(&numero_usp, sizeof(int), 1, pFile);
        fread(&nome, sizeof(char), 50, pFile);
        fread(&curso, sizeof(char), 50, pFile);
        fread(&nota, sizeof(float), 1, pFile);
        // printa conforme o exercicio pede
        printf("nUSP: %d\n", numero_usp);
        printf("Nome: %s\n", nome);
        printf("Curso: %s\n", curso);
        printf("Nota: %.2f\n", nota);
        // se for o ultimo registro, nao printa o pula linha
        if (ftell(pFile) < index_final)
        {
            printf("\n");
        }
    }
}

int main()
{
    // nome do arquivo a ser aberto
    char nome_arquivo[10];
    // operacao a ser feita
    int operacao;

    scanf("%s", nome_arquivo);
    scanf("%d", &operacao);

    FILE *pFile;
    // se der erro na abertura do arquivo
    if((pFile=fopen(nome_arquivo, "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    // caso a leitura do arquivo funcione
    else
    {
        // definicao das variaveis relativas ao primeiro e ultimo registro
        long int comeco, index_final;
        // pega a ultima posicao do arquivo
        index_final = file_size(pFile, nome_arquivo);
        // operacao 1
        if(operacao == 1)
        {
            // inicio no comeco do arquivo
            comeco = 0;
            // printa os valores desejados
            print_file_data(pFile, comeco, index_final);
        }
        // operacao 2
        else if(operacao == 2)
        {
            // inicio no comeco do arquivo
            comeco = 0;
            // fim na metade do arquivo
            index_final = index_final/2;
            // printa os valores desejados
            print_file_data(pFile, comeco, index_final);
        }
        // operacao 3
        else if(operacao == 3)
        {
            // comeco na metade do arquivo
            comeco = index_final/2;
            // printa os valores desejados
            print_file_data(pFile, comeco, index_final);
        }
        // operacao 4
        else if(operacao == 4)
        {
            // define as variaves de faixa
            int faixa_comeco, faixa_fim;
            // le as variaveis de faixa
            scanf("%d", &faixa_comeco);
            scanf("%d", &faixa_fim);
            // como cada registro é 108 bytes, as faixas de comeco e fim
            // vao ser multiplas de 108
            faixa_comeco = (faixa_comeco * 108) - 108;
            faixa_fim = faixa_fim * 108;
            // printa os valores desejados
            print_file_data(pFile, faixa_comeco, faixa_fim);
        }
        else if(operacao == 5)
        {
            // define e le a posicao do registro desejado
            int posicao_registro;
            scanf("%d", &posicao_registro);
            // a posicao do registro é multipla de 108 bytes
            posicao_registro = (posicao_registro * 108) - 108;
            // printa os valores desejados
            print_file_data(pFile, posicao_registro, posicao_registro + 1);
        }

    }
    
    // fecha o arquivo
    fclose(pFile); 
    return 0;

}
