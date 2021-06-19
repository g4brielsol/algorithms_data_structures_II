
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Aluno // Cria uma STRUCT para armazenar os dados de uma pessoa
{
    int numero_usp;
    char nome[50];
    char sobrenome[50];
    char curso[50];
    float nota;
} Aluno; // Define o nome do novo tipo criado

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
int procurar_registro(FILE *pFile, long int comeco, long int index_final, int numero_usp)
{
    // muda a posicao inicial no arquivo de acordo com a operacao escolhida
    fseek(pFile, comeco, SEEK_SET);
    while(ftell(pFile) < index_final) 
    {
        // definicao das variaveis
        Aluno aluno;
        // le os parametros
        fread(&aluno.numero_usp, sizeof(int), 1, pFile);
        printf("arquivo %d\n", aluno.numero_usp);
        printf("procura %d\n", numero_usp);
        if((numero_usp == aluno.numero_usp) && (aluno.numero_usp >= 0))
        {
             printf("1 \n");
            return 1;
        }    
    }
    return -1;
}

void printar_dados(int numero_usp)
{
    FILE *dados;
    //se der erro na abertura do arquivo
    if((dados=fopen("dados.dat", "r"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        // definicao das variaveis relativas ao primeiro e ultimo registro
        long int comeco, index_final;
        int contador = 0;
        // pega a ultima posicao do arquivo
        index_final = file_size(dados);// - 154;
        comeco = 0;
        // muda a posicao inicial no arquivo de acordo com a operacao escolhida
        fseek(dados, comeco, SEEK_SET);
        // enquanto a posicao do arquivo for menor que a posicao final indicada pela operacao
        //printf("printar dados %d \n", numero_usp);
        while(ftell(dados) < index_final) 
        {
            // definicao das variaveis
            int numero_usp_arquivo;
            char nome[50], sobrenome[50], curso[50];
            float nota;
            Aluno aluno;
            // le os parametros
            fread(&aluno, sizeof(struct Aluno), 1, dados);
            printf("%d\n", aluno.numero_usp);
            if((aluno.numero_usp == numero_usp) && (aluno.numero_usp >= 0))
            {
                // le os parametros
                // fread(&nome, sizeof(char), 50, registros);
                // fread(&sobrenome, sizeof(char), 50, registros);
                // fread(&curso, sizeof(char), 50, registros);
                // fread(&nota, sizeof(float), 1, registros);
                // printa conforme o exercicio pede
                printf("-------------------------------\n");
                printf("USP number: %d\n", aluno.numero_usp);
                printf("Name: %s\n", aluno.nome);
                printf("Surname: %s\n", aluno.sobrenome);
                printf("Course: %s\n", aluno.curso);
                printf("Test grade: %.2f\n", aluno.nota);
                printf("-------------------------------\n");
            }

            //contador += 1;
            //comeco = contador * 158;
            //fseek(registros, comeco, SEEK_SET);    
            // printf("registro %ld\n", ftell(registros));
            // printf("final %ld\n", index_final);
        }
    }
    fclose(dados);
    return;
}

void deletar_registro(int numero_usp)
{
    // printf("entrou no deletar registro\n");
    FILE *registros;
    //se der erro na abertura do arquivo
    if((registros=fopen("registros.dat", "r+"))==NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        // definicao das variaveis relativas ao primeiro e ultimo registro
        long int comeco, index_final;
        int contador = 0;
        // pega a ultima posicao do arquivo
        index_final = file_size(registros);
        comeco = 0;
        // muda a posicao inicial no arquivo de acordo com a operacao escolhida
        fseek(registros, comeco, SEEK_SET);
        // enquanto a posicao do arquivo for menor que a posicao final indicada pela operacao
        // printf("%ld\n", ftell(registros));
        // printf("%ld\n", index_final);
        while(ftell(registros) < index_final) 
        {
            // definicao das variaveis
            int numero_usp_arquivo;
            int deletar = -1;
            //char nome[50], sobrenome[50], curso[50];
            //float nota;
            long int local_sobrescrever;
            // le os parametros
            local_sobrescrever = ftell(registros);
            fread(&numero_usp_arquivo, sizeof(int), 1, registros);
            if((numero_usp_arquivo == numero_usp) && (numero_usp_arquivo >= 0))
            {
                fseek(registros, local_sobrescrever, SEEK_SET);    
                fwrite(&deletar, sizeof(int), 1, registros);
            }
        }
    }
    fclose(registros);
    return;
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
        char nome[50], sobrenome[50], curso[50];
        float nota;
        // le os parametros
        printf("%ld\n", ftell(pFile));
        fread(&numero_usp, sizeof(int), 1, pFile);
        fread(&nome, sizeof(char), 50, pFile);
        fread(&sobrenome, sizeof(char), 50, pFile);
        fread(&curso, sizeof(char), 50, pFile);
        fread(&nota, sizeof(float), 1, pFile);
        // printa conforme o exercicio pede
        printf("nUSP: %d\n", numero_usp);
        printf("Nome: %s\n", nome);
        printf("Sobrenome: %s\n", sobrenome);
        printf("Curso: %s\n", curso);
        printf("Nota: %.2f\n", nota);
        // se for o ultimo registro, nao printa o pula linha
        if (ftell(pFile) < index_final)
        {
            printf("\n");
        }
    }
}

// Funcao para printar as informacoes conforme o exercicio pede
void print_registros_data(FILE *pFile, long int comeco, long int index_final)
{
    // muda a posicao inicial no arquivo de acordo com a operacao escolhida
    fseek(pFile, comeco, SEEK_SET);
    // enquanto a posicao do arquivo for menor que a posicao final indicada pela operacao
    printf("entrou no procurar registors\n");
    printf("%ld\n", ftell(pFile));
    printf("%ld\n", index_final);
    while(ftell(pFile) < index_final) 
    {
        // definicao das variaveis
        int numero_usp;
        // le os parametros
        fread(&numero_usp, sizeof(int), 1, pFile);
        // printa conforme o exercicio pede
        printf("nUSP: %d\n", numero_usp);
        // se for o ultimo registro, nao printa o pula linha
        if (ftell(pFile) < index_final)
        {
            printf("\n");
        }
    }
}

int main()
{
    FILE *Arq;
    Arq=fopen("6.in","rt");
    // caractere que delimita a separacao no csv
    char virgula_espaco[2] = " ,", espaco[2] = " ", informacao[100];
    // token para pegar as informacoes separadas por "," e " " no strtok
    char *token;
    // definicao das variaveis
    int numero_usp, registro_existente;;
    char nome[50], sobrenome[50], curso_1[50], curso_2[50], curso_3[50], comando[7];
    Aluno aluno_lido;
    float nota;
    long int comeco, index_final;

    // arquivo binario "registros" a ser escrito
    FILE *registros, *dados;  
    // loop para pegar as informacoes em csv
    while(fgets(informacao, sizeof(informacao), Arq) != NULL) {        
        //printf("%s", informacao);
        token = strtok(informacao, virgula_espaco);
        // pegar as informacoes separadas por virgula
        while( token != NULL ) {
            // pega o char com o comando
            strcpy(comando, token);
            //printf("%s\n", comando);
            if(strcmp(comando, "insert") == 0)
            {
                Aluno aluno_lido;
                registros = fopen ("registros.dat" , "a+b" );
                dados = fopen ("dados.dat" , "a+b" );
                // retira o comando inicial da frase
                // transforma o char em int para o numero usp
                token = strtok(NULL, virgula_espaco);
                numero_usp = atoi(token);
                aluno_lido.numero_usp = atoi(token);
                //printf("%d\n", numero_usp);
                //pega a ultima posicao do arquivo
                index_final = file_size(registros);
                comeco = 0;
                printf("procura antes %d\n", aluno_lido.numero_usp);
                registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                if(registro_existente == -1)
                {
                    // pega o char com o nome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(aluno_lido.nome, token);
                    //printf("%s\n", nome);
                    // pega o char com o sobrenome
                    token = strtok(NULL, virgula_espaco);
                    strcpy(aluno_lido.sobrenome, token);
                    //printf("%s\n", sobrenome);
                    // pega o char com o curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_1, token);
                    //printf("%s\n", curso_1);
                    // pega o char com o curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_2, token);
                    //printf("%s\n", curso_2);
                    // pega o char com o curso
                    token = strtok(NULL, virgula_espaco);
                    strcpy(curso_3, token);
                    //printf("%s\n", curso_3);
                    //strcat(aluno_lido.curso, curso_1);
                    strcat(aluno_lido.curso, espaco);
                    strcat(aluno_lido.curso, curso_2);
                    strcat(aluno_lido.curso, espaco);
                    strcat(aluno_lido.curso, curso_3);
                    printf("%s\n", curso_1);
                    // transforma o char da nota em floar
                    token = strtok(NULL, virgula_espaco);
                    aluno_lido.nota = atof(token);
                    //printf("%f\n", nota);
                    // escreve as informacoes no arquivo registros
                    printf("insert %d\n", aluno_lido.numero_usp);
                    fwrite(&aluno_lido.numero_usp, sizeof(int), 1, registros);
                    // fwrite(&aluno_lido.numero_usp, sizeof(int), 1, dados);
                    // fwrite(&aluno_lido.nome, sizeof(char), 50, dados);
                    // fwrite(&aluno_lido.sobrenome, sizeof(char), 50, dados);
                    // fwrite(&aluno_lido.curso, sizeof(char), 50, dados);
                    // fwrite(&aluno_lido.nota, sizeof(float), 1, dados);
                    fwrite(&aluno_lido, sizeof(struct Aluno), 1, dados);
                }
                else
                {
                    printf("O Registro ja existe!\n");
                }
                fclose(registros);
                fclose(dados);
            }
            else if(strcmp(comando, "search") == 0)
            {
                if((registros=fopen("registros.dat", "r"))==NULL)
                {
                    printf("Registro nao encontrado\n");
                }
                if((dados=fopen("dados.dat", "r"))==NULL)
                {
                    ;
                }
                else
                {
                    // retira o comando inicial da frase
                    // transforma o char em int para o numero usp
                    token = strtok(NULL, virgula_espaco);
                    numero_usp = atoi(token);
                    //printf("nuemro usp antes funcao %d\n", numero_usp);
                            // pega a ultima posicao do arquivo
                    index_final = file_size(registros);
                    comeco = 0;
                    registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                    //printf("%d", registro_existente);
                    if(registro_existente == -1)
                    {
                        printf("Registro nao econtrado!\n");
                    }
                    else
                    {
                        printf("printar dados %d\n", numero_usp);
                        printar_dados(numero_usp);
                    }
                    fclose(registros);
                    fclose(dados);
                    
                }
                //break;
            }
            else if(strcmp(comando, "delete") == 0)
            {
                // registros = fopen ("registros.dat" , "r" );
                // dados = fopen ("dados.dat" , "r" );
                if((registros=fopen("registros.dat", "r"))==NULL)
                {
                    ;
                }
                if((dados=fopen("dados.dat", "r"))==NULL)
                {
                    ;
                }
                else
                {
                    // retira o comando inicial da frase
                    // transforma o char em int para o numero usp
                    token = strtok(NULL, virgula_espaco);
                    numero_usp = atoi(token);
                    //printf("nuemro usp antes funcao %d\n", numero_usp);
                            // pega a ultima posicao do arquivo
                    index_final = file_size(registros);
                    comeco = 0;
                    registro_existente = procurar_registro(registros, comeco, index_final, numero_usp);
                    if(registro_existente == -1)
                    {
                    ;// printf("Registro nao econtrado!\n");
                    }
                    else
                    {
                        deletar_registro(numero_usp);
                    }
                    fclose(registros);
                    fclose(dados);    
                }                
                //break;
            }
            else if(strcmp(comando, "exit") == 0)
            {
                break;
            }
        // // pega proximo token
        token = strtok(NULL, virgula_espaco);             
        }
        //break;
    }
    // fecha o arquivo apos a escritura
//    fclose(registros);
//    fclose(dados);

    //se der erro na abertura do arquivo
    // if((registros=fopen("dados.dat", "r"))==NULL)
    // {
    //     printf("Erro na abertura do arquivo\n");
    // }
    // else
    // {
    //     // definicao das variaveis relativas ao primeiro e ultimo registro
    //     long int comeco, index_final;
    //     // pega a ultima posicao do arquivo
    //     index_final = file_size(registros);
    //     // como as informacoes sao multiplas de 108 e queremos as
    //     // 10 ultimas posicoes do arquivo, comecamos a partir do decimo
    //     // registro antes do ultimo
    //     //comeco = index_final - (10 * 108);
    //     comeco = 0;
    //     // printa os registros desejados
    //     print_file_data(registros, comeco, index_final);
    // }

    //     //se der erro na abertura do arquivo
    // if((registros=fopen("registros.dat", "r"))==NULL)
    // {
    //     printf("Erro na abertura do arquivo\n");
    // }
    // else
    // {
    //     // pega a ultima posicao do arquivo
    //     index_final = file_size(registros);
    //     comeco = 0;
    //     // printa os registros desejados
    //     print_registros_data(registros, comeco, index_final);
    // }
    
    // // fecha o arquivo
    // fclose(registros);
    // fclose(dados); 

    //free(token);
    return 0;

}
