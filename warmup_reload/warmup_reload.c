#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funcao para pegar a ultima posicao do arquivo
long int file_size(FILE *pFile)
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
    // caractere que delimita a separacao no csv
    char virgula[2] = ",", informacao[100];
    // token para pegar as informacoes separadas por "," no strtok
    char *token;
    // definicao das variaveis
    int numero_usp;
    char nome[50], curso[50];
    float nota;

    // arquivo binario "registros" a ser escrito
    FILE *registros;  
    registros = fopen ("registros.dat" , "wb" );

    // loop para pegar as informacoes em csv
    while(fgets(informacao, sizeof(informacao), stdin) != NULL) {        
        // pegar o primeiro token
        token = strtok(informacao, virgula);
        
        // pegar as informacoes separadas por virgula
        while( token != NULL ) {
            // transforma o char em int para o numero usp
            numero_usp = atoi(token);
            token = strtok(NULL, virgula);
            // pega o char com o nome
            strcpy(nome, token);
            token = strtok(NULL, virgula);
            // pega o char com o curso
            strcpy(curso, token);
            token = strtok(NULL, virgula);
            // transforma o char da nota em floar
            nota = atof(token);
            // escreve as informacoes no arquivo registros
            fwrite(&numero_usp, sizeof(int), 1, registros);
            fwrite(&nome, sizeof(char), 50, registros);
            fwrite(&curso, sizeof(char), 50, registros);
            fwrite(&nota, sizeof(float), 1, registros);
            // pega proximo token
            token = strtok(NULL, virgula);
        }
        
    }
    // fecha o arquivo apos a escritura
    fclose(registros);

    // se der erro na abertura do arquivo
    if((registros=fopen("registros.dat", "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        // definicao das variaveis relativas ao primeiro e ultimo registro
        long int comeco, index_final;
        // pega a ultima posicao do arquivo
        index_final = file_size(registros);
        // como as informacoes sao multiplas de 108 e queremos as
        // 10 ultimas posicoes do arquivo, comecamos a partir do decimo
        // registro antes do ultimo
        comeco = index_final - (10 * 108);
        // printa os registros desejados
        print_file_data(registros, comeco, index_final);
    }
    
    // fecha o arquivo
    fclose(registros); 
    return 0;

}
