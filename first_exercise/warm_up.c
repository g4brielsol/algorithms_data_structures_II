#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funcao para pegar a ultima posicao do arquivo
int file_size(FILE *pFile, char nome_arquivo[10])
{
    // variavel para armazenar a ultima posicao do arquivo
    long int index_final;

    // caso 
    if((pFile=fopen(nome_arquivo, "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        fseek(pFile, 0, SEEK_END);
        index_final = ftell(pFile);
    }

    fclose(pFile);
    return index_final;
}

void print_file_data(FILE *pFile, long int comeco, long int index_final)
{
    fseek(pFile, comeco, SEEK_SET);

    while(ftell(pFile) < index_final)//!feof(pFile)) 
    {
        int numero_usp;
        char nome[50], curso[50];
        float nota;
        fread(&numero_usp, sizeof(int), 1, pFile);
        fread(&nome, sizeof(char), 50, pFile);
        fread(&curso, sizeof(char), 50, pFile);
        fread(&nota, sizeof(float), 1, pFile);
        printf("nUSP: %d\n", numero_usp);
        printf("Nome: %s\n", nome);
        printf("Curso: %s\n", curso);
        printf("Nota: %.2f\n", nota);
        //printf("Ftell %ld", ftell(pFile));
        if (ftell(pFile) < index_final)
        {
            printf("\n");
        }
        
        // printf("pFile %ld\n", ftell(pFile));
        // printf("Fim %ld\n", index_final);
    }
}

int main()
{
    char nome_arquivo[10];
    int operacao;

    scanf("%s", nome_arquivo);
    scanf("%d", &operacao);

    FILE *pFile;
    if((pFile=fopen(nome_arquivo, "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {

        long int comeco, index_final;
        index_final = file_size(pFile, nome_arquivo);

        if(operacao == 1)
        {
            comeco = 0;
            print_file_data(pFile, comeco, index_final);
        }
        else if(operacao == 2)
        {
            comeco = 0;
            index_final = index_final/2;
            print_file_data(pFile, comeco, index_final);
        }
        else if(operacao == 3)
        {
            comeco = index_final/2;
            print_file_data(pFile, comeco, index_final);
        }
        else if(operacao == 4)
        {
            int faixa_comeco, faixa_fim;
            scanf("%d", &faixa_comeco);
            scanf("%d", &faixa_fim);
            faixa_comeco = (faixa_comeco * 108) - 108;
            faixa_fim = faixa_fim * 108;
            print_file_data(pFile, faixa_comeco, faixa_fim);
        }
        else if(operacao == 5)
        {
            int posicao_registro;
            scanf("%d", &posicao_registro);
            posicao_registro = (posicao_registro * 108) - 108;
            print_file_data(pFile, posicao_registro, posicao_registro + 1);
        }

    }
    
    fclose(pFile); 
    
    return 0;

}
