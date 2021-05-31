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

// funcao para procurar se o registro existe no arquivo ou nao
int procurar_registro(FILE *pFile, long int comeco, long int index_final, int numero_usp)
{
    // muda a posicao para o início no arquivo
    fseek(pFile, comeco, SEEK_SET);
    // enquanto a posicao do arquivo for menor que a posicao final do arquivo
    while(ftell(pFile) < index_final) 
    {
        // variavel a ser lida do arquivo
        int numero_usp_arquivo;
        // le o numero usp do arquivo de registro
        fread(&numero_usp_arquivo, sizeof(int), 1, pFile);
        // se o registro for igual ao procurado e for positivo
        if((numero_usp == numero_usp_arquivo) && (numero_usp_arquivo >= 0))
        {
            // 1 representa que encontrou o registro
            return 1;
        }    
    }
    // -1 representa que NAO encontrou o registro
    return -1;
}

// funcao para printar os registros encontrados
void printar_dados(int numero_usp)
{
    FILE *registros;
    //se der erro na abertura do arquivo
    if((registros=fopen("dados.dat", "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        // definicao das variaveis relativas ao primeiro e ultimo registro
        long int comeco, index_final;
        int contador = 0;
        // pega a ultima posicao do arquivo para sair do while
        index_final = file_size(registros) - 154;
        comeco = 0;
        // muda a posicao para o inicio do arquivo para leitura
        fseek(registros, comeco, SEEK_SET);
        // enquanto a posicao do arquivo for menor que a posicao final
        while(ftell(registros) < index_final) 
        {
            // definicao das variaveis
            int numero_usp_arquivo;
            char nome[50], sobrenome[50], curso[50];
            float nota;
            // le o numero usp para checar se encontra as informacoes a serem printadas
            fread(&numero_usp_arquivo, sizeof(int), 1, registros);
            // se encontrou o numero usp procurado e for positivo
            if((numero_usp_arquivo == numero_usp) && (numero_usp_arquivo >= 0))
            {
                // le os dados do numero usp encontrado
                fread(&nome, sizeof(char), 50, registros);
                fread(&sobrenome, sizeof(char), 50, registros);
                fread(&curso, sizeof(char), 50, registros);
                fread(&nota, sizeof(float), 1, registros);
                // printa conforme o exercicio pede
                printf("-------------------------------\n");
                printf("USP number: %d\n", numero_usp_arquivo);
                printf("Name: %s\n", nome);
                printf("Surname: %s\n", sobrenome);
                printf("Course: %s\n", curso);
                printf("Test grade: %.2f\n", nota);
                printf("-------------------------------\n");
            }
            // pula para a posicao do proximo numero usp
            contador += 1;
            comeco = contador * 158;
            fseek(registros, comeco, SEEK_SET);    
        }
    }
    // fechar o arquivo
    fclose(registros);
    return;
}

// deletar logicamente o numero usp 
void deletar_registro(int numero_usp)
{
    FILE *registros;
    //se der erro na abertura do arquivo
    if((registros=fopen("registros.dat", "r+"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        // definicao das variaveis de posicao do arquivo
        long int comeco, index_final;
        // pega a ultima posicao do arquivo
        index_final = file_size(registros);
        comeco = 0;
        // muda a posicao do arquivo para o inicio
        fseek(registros, comeco, SEEK_SET);
        // enquanto a posicao do arquivo for menor que a posicao final
        while(ftell(registros) < index_final) 
        {
            int numero_usp_arquivo;
            // o numero usp vai ser mudado para -1 para configurar a exclusao logica
            int deletar = -1;
            // posicao do numero usp no arquivo a ser sobrescrita
            long int local_sobrescrever;
            // guarda a posicao do numero usp a ser sobrescrita
            local_sobrescrever = ftell(registros);
            // le o numero usp
            fread(&numero_usp_arquivo, sizeof(int), 1, registros);
            // se o numero usp for encontrado e for positivo
            if((numero_usp_arquivo == numero_usp) && (numero_usp_arquivo >= 0))
            {
                // muda para a posicao do numero usp a ser trocada
                fseek(registros, local_sobrescrever, SEEK_SET);   
                // escreve -1 no numero usp a ser deletado logicamente 
                fwrite(&deletar, sizeof(int), 1, registros);
            }
        }
    }
    // fecha o arquivo
    fclose(registros);
    return;
}


int main()
{
    // caracteres que delimita a separacao no csv
    char virgula_espaco[2] = " ,", espaco[2] = " ", informacao[100];
    // token para pegar as informacoes separadas por " ," e " " no strtok
    char *token;
    // definicao das variaveis
    int numero_usp, registro_existente;
    char nome[50], sobrenome[50], curso_1[50], curso_2[50], curso_3[50], comando[7];
    float nota;
    long int comeco, index_final;

    // arquivo binario "registros" e "dados" a serem escritos
    FILE *registros, *dados;  
    // loop para pegar as informacoes em csv
    while(fgets(informacao, sizeof(informacao), stdin) != NULL) {        
        // frase para pegar as informacoes
        token = strtok(informacao, virgula_espaco);
        // pegar as informacoes separadas por virgula
        while( token != NULL ) {
            // pega o char com o comando a ser feito
            strcpy(comando, token);
            // se o comando for insert
            if(strcmp(comando, "insert") == 0)
            {
                // abre os arquivos de registro e dados com a opcao de escrever ao final
                registros = fopen ("registros.dat" , "a+b" );
                dados = fopen ("dados.dat" , "a+b" );
                // transforma o char em int do numero usp
                token = strtok(NULL, virgula_espaco);
                numero_usp = atoi(token);
                //pega a ultima posicao do arquivo de registros
                index_final = file_size(registros);
                comeco = 0;
                // procura se o registro ja existe antes de inserir
                registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                // se o registro nao existir, insere
                if(registro_existente == -1)
                {
                    // pega o char com o nome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(nome, token);
                    // pega o char com o sobrenome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(sobrenome, token);
                    // pega o char com a primeira frase do curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_1, token);
                    // pega o char com a segunda frase do curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_2, token);
                    // pega o char com a terceira frase do curso
                    token = strtok(NULL, virgula_espaco);
                    // concatena as 3 frases do curso intercaladas por espaco
                    strcpy(curso_3, token);
                    strcat(curso_1, espaco);
                    strcat(curso_1, curso_2);
                    strcat(curso_1, espaco);
                    strcat(curso_1, curso_3);
                    // transforma o char da nota em float
                    token = strtok(NULL, virgula_espaco);
                    nota = atof(token);
                    // escreve as informacoes no arquivo dados
                    fwrite(&numero_usp, sizeof(int), 1, registros);
                    fwrite(&numero_usp, sizeof(int), 1, dados);
                    fwrite(&nome, sizeof(char), 50, dados);
                    fwrite(&sobrenome, sizeof(char), 50, dados);
                    fwrite(&curso_1, sizeof(char), 50, dados);
                    fwrite(&nota, sizeof(float), 1, dados);
                }
                // se o registro ja existir, printa a frase
                else
                {
                    printf("O Registro ja existe!\n");
                }
                // fechas os arquivos de registro e de dados
                fclose(registros);
                fclose(dados);
            }
            // se o comando for search
            else if(strcmp(comando, "search") == 0)
            {
                // checa se os arquivos registros e dados existem
                if((registros=fopen("registros.dat", "r"))==NULL)
                {
                    printf("Registro nao encontrado!\n");
                }
                if((dados=fopen("dados.dat", "r"))==NULL)
                {
                    ;
                }
                // se os arquivos existirem
                else
                {
                    // transforma o char em int para o numero usp
                    token = strtok(NULL, virgula_espaco);
                    numero_usp = atoi(token);
                    // pega a ultima posicao do arquivo
                    index_final = file_size(registros);
                    comeco = 0;
                    // procurar se o numero usp existe no arquivo
                    registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                    // se o registro nao for encontrado
                    if(registro_existente == -1)
                    {
                        printf("Registro nao encontrado!\n");
                    }
                    // se encontrou o arquivo, printa os dados do aluno
                    else
                    {
                        printar_dados(numero_usp);
                    }
                    fclose(registros);
                    fclose(dados);
                    
                }
            // se for o comando delete
            }
            else if(strcmp(comando, "delete") == 0)
            {
                // checa se os arquivos existem
                if((registros=fopen("registros.dat", "r"))==NULL)
                {
                    ;
                }
                if((dados=fopen("dados.dat", "r"))==NULL)
                {
                    ;
                }
                // se os arquivos existirem
                else
                {
                    // transforma o char em int para o numero usp
                    token = strtok(NULL, virgula_espaco);
                    numero_usp = atoi(token);
                    // pega a ultima posicao do arquivo
                    index_final = file_size(registros);
                    comeco = 0;
                    // procura se o numero usp existe no arquivo de registro
                    registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                    if(registro_existente == -1)
                    {
                        ;
                    }
                    // se encontrar o registro, deleta logicamente 
                    else
                    {
                        deletar_registro(numero_usp);
                    }
                    // fecha os arquivos
                    fclose(registros);
                    fclose(dados);    
                }                
            }
        // pega proximo token
        token = strtok(NULL, virgula_espaco);             
        }
        // se o comando for exit, sai do while
        if(strcmp(comando, "exit") == 0)
        {
            break;
        }
    }
    return 0;

}
