/**
 * @file forca.c
 * @brief Implementacao das funcoes de logica do jogo da forca.
 *
 * Contem o corpo de todas as funcoes declaradas em forca.h,
 * que controlam o funcionamento interno do jogo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "forca.h"
// Inclusoes para funcionalidades dependentes de sistema operacional (delay).
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

/**
 * @brief Remove espaços em branco do inicio e do fim de uma string.
 *
 * Modifica a string original para remover todos os
 * caracteres de espaço, tabulacao ou quebra de linha de suas extremidades.
 *
 * @param str A string a ser modificada.
 */
void apararString (char *str) {
    int i;
    // Checagem de segurança para string nula ou vazia.
    if (str==NULL||str[0]=='\0')  return;
    // Remove espacos do final: percorre do fim para o comeco.
    for(i=strlen(str)-1;i>=0&&isspace((unsigned char)str[i]);i--);
    str[i+1]='\0';
    // Remove espacos do inicio: encontra o primeiro caractere valido.
    for(i=0;str[i]!='\0'&&isspace((unsigned char)str[i]);i++);
    // Se encontrou espacos no inicio, move o resto da string para frente.
    if(i>0) memmove(str,&str[i],strlen(&str[i])+1);
}

/**
 * @brief Limpa o buffer de entrada (stdin) ate a proxima quebra de linha.
 *
 * Util para consumir caracteres indesejados deixados por funcoes como scanf,
 * garantindo que a proxima leitura de entrada funcione como esperado.
 */
void limparBuffer (void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Pausa a execucao do programa por um determinado tempo.
 *
 * Funcao multiplataforma que usa Sleep() no Windows e usleep() em
 * sistemas POSIX (Linux, macOS).
 *
 * @param milissegundos O tempo de pausa em milissegundos.
 */
void delayMS (int milissegundos) {
    #ifdef _WIN32
        Sleep(milissegundos);
    #else
        usleep(milissegundos * 1000);
    #endif
}

/**
 * @brief Conta o numero de palavras (linhas) em um arquivo.
 * @param nomeArquivo O nome do arquivo a ser lido.
 * @return O numero de linhas no arquivo.
 */
int contarPalavras (char *nomeArquivo){
    int count=0;
    char buffer[TAM_MAX_PALAVRA];
    FILE *arq = fopen(nomeArquivo,"r");
    // Tratamento de erro caso o arquivo de palavras nao seja encontrado.
    if(arq==NULL){
        printf("Erro ao abrir o arquivo: %s\n",nomeArquivo);
        exit(1);
    }
    // Le cada linha do arquivo para conta-las.
    while(fgets(buffer,TAM_MAX_PALAVRA,arq)!=NULL)
        count++;
    fclose(arq);
    return count;
}

/**
 * @brief Preenche um vetor de inteiros com o valor zero.
 * @param v O vetor a ser zerado.
 * @param n O tamanho do vetor.
 */
void zerarVetor (int v[], int n){
    int i;
    for(i=0;i<n;i++)
        v[i]=0;
}

/**
 * @brief Carrega uma palavra aleatoria de um arquivo.
 *
 * Sorteia uma linha do arquivo e le a palavra contida nela,
 * tratando a string para remover espaços ou quebras de linha.
 *
 * @param nomeArquivo O nome do arquivo de palavras.
 * @param palavra A string que recebera a palavra sorteada.
 * @param tamanho O numero total de palavras no arquivo.
 */
void carregarPalavras (char *nomeArquivo, char *palavra, int tamanho){
    // Sorteia um numero de 0 a (tamanho-1) para a linha.
    int linhaAleatoria=rand()%tamanho,i;
    FILE *arq = fopen(nomeArquivo,"r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo: %s\n",nomeArquivo);
        exit(1);
    }
    // Le o arquivo linha por linha ate chegar na linha sorteada.
    for(i=0;i<linhaAleatoria+1;i++)
        fgets(palavra,TAM_MAX_PALAVRA,arq);
    // Limpa a palavra lida de possiveis espaços ou \n.
    apararString(palavra);
    fclose(arq);
}

/**
 * @brief Prepara a string da forca com underscores.
 * @param str A string a ser preenchida com '_'.
 * @param tamanho O comprimento da palavra secreta.
 */
void reiniciarForca (char *str, int tamanho){
    int i;
    for(i=0;i<tamanho;i++)
        str[i]='_';
    // Adiciona o '\0' para finalizar a string.
    str[i]='\0';
}

/**
 * @brief Inicia uma nova partida, reiniciando vidas e exibindo uma contagem regressiva.
 * @param p Ponteiro para a struct do jogador.
 */
void iniciarPartida (Jogador *p){
    p->vidas=VIDAS;
    printf("Boa sorte, %s!\nLa vamos nos ...\n\n",p->nome);
    // Contagem regressiva para criar um suspense.
    delayMS(DELAY_1s);
    printf("3 ...\n");
    delayMS(DELAY_1s);
    printf("2 ...\n");
    delayMS(DELAY_1s);
    printf("1 ...\n");
    delayMS(DELAY_1s);
}

/**
 * @brief Desenha o estado atual do jogo na tela.
 *
 * Exibe o boneco da forca, as letras ja utilizadas e a palavra
 * com os acertos e os underscores.
 *
 * @param p A struct do jogador (para saber as vidas).
 * @param palavra A string que mostra os acertos e os underscores.
 * @param letras O vetor que controla as letras ja utilizadas.
 * @param n O tamanho do vetor de letras.
 */
void desenharForca (Jogador p, char *palavra, int letras[], int n){
    int i;
    char c='A';
    // Matriz de strings contendo a arte da forca para cada estado de vida.
    // O indice do vetor corresponde ao numero de vidas.
    const char *desenhos[]={
        // 0 vidas. (Fim de jogo)
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|                   |\n|                  /|\\\n|                 / | \\\n|                /  |  \\\n|                   |\n|                   |\n|                   |\n|                   |\n|                  / \\\n|                 /   \\\n|                /     \\\n|              _/       \\_\n|\n|\n|\n|\n",
        // 1 vida.
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|                   |\n|                  /|\\\n|                 / | \\\n|                /  |  \\\n|                   |\n|                   |\n|                   |\n|                   |\n|                  /\n|                 /\n|                /\n|              _/\n|\n|\n|\n|\n",
        // 2 vidas.
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|                   |\n|                  /|\\\n|                 / | \\\n|                /  |  \\\n|                   |\n|                   |\n|                   |\n|                   |\n|\n|\n|\n|\n|\n|\n|\n|\n",
        // 3 vidas.
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|                   |\n|                  /|\n|                 / |\n|                /  |\n|                   |\n|                   |\n|                   |\n|                   |\n|\n|\n|\n|\n|\n|\n|\n|\n",
        // 4 vidas.
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|                   |\n|                   |\n|                   |\n|                   |\n|                   |\n|                   |\n|                   |\n|                   |\n|\n|\n|\n|\n|\n|\n|\n|\n",
        // 5 vidas.
        " ___________________\n|/                  |\n|                 -----\n|                | \" \" |\n|                |  |  |\n|                | ___ |\n|                 -----\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n",
        // 6 vidas.
        " ___________________ \n|/                  |\n|                 -----\n|                |     |\n|                |     |\n|                |     |\n|                 -----\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n",
        // 7 vidas.
        " ___________________ \n|/                  |\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n"
    };
    printf("\n\n\tLetras utilizadas: ");
    for(i=0;i<n;i++){
        if(letras[i])   printf("%c ",c+i);
    }
    printf("\n\n");
    // Seleciona o desenho correto com base nas vidas do jogador.
    i=p.vidas;
    if(i<0) i=0; // Garante que o indice nao seja negativo.
    printf("%s",desenhos[i]);
    // Imprime a palavra na forca.
    printf("|\tPalavra: ");
    for(i=0;palavra[i]!='\0';i++)
        printf("%c ",toupper(palavra[i]));
    printf("\n\n");
}

/**
 * @brief Verifica se uma letra ja foi utilizada e a marca como usada.
 *
 * Usa um vetor de inteiros, onde o indice
 * corresponde a letra do alfabeto (A=0, B=1, ...).
 *
 * @param letra A letra a ser verificada.
 * @param letras O vetor de controle de letras.
 * @return 1 se a letra ja foi usada, 0 caso contrario.
 */
int verificarLetra (char letra, int letras[]){
    // Calcula o indice (0-25) com base no caractere ASCII 'A'.
    if(letras[toupper(letra)-'A'])    return 1;
    // Se nao foi usada, marca como 1 (true) e retorna 0.
    else    letras[toupper(letra)-'A']=1;
    return 0;
}

/**
 * @brief Testa se a letra digitada existe na palavra secreta.
 *
 * Se a letra for encontrada, a funcao tambem atualiza a string
 * de exibicao (palavraNaForca) com a letra nos locais corretos.
 *
 * @param letra A letra digitada pelo jogador.
 * @param palavra A palavra secreta.
 * @param palavraNaForca A string de exibicao a ser atualizada.
 * @return O numero de vezes que a letra foi encontrada.
 */
int testarLetra (char letra, char *palavra, char *palavraNaForca){
    int count=0,i,tamanho=strlen(palavra);
    // Itera por toda a palavra secreta.
    for(i=0;i<tamanho;i++){
        // Compara as letras ignorando maiusculas/minusculas.
        if(toupper(palavra[i])==toupper(letra)){
            count++;
            // Atualiza a palavra de exibicao com a letra correta.
            palavraNaForca[i] = toupper(letra);
        }
    }
    return count;
}

/**
 * @brief Registra o resultado da partida no arquivo de resultados.
 *
 * Salva a data/hora, nome do jogador, palavra da partida e o
 * resultado (Vitoria/Derrota) em uma nova linha do arquivo.
 *
 * @param nomeArquivo O nome do arquivo de resultados.
 * @param palavra A palavra secreta da partida.
 * @param p A struct do jogador com o resultado.
 */
void registrarResultado (char *nomeArquivo, char *palavra, Jogador p){
    time_t tempo;
    struct tm *infoTempo;
    char dataHora[TAM_MAX_PALAVRA];
    // Obtem e formata a data e hora atuais.
    time(&tempo);
    infoTempo = localtime(&tempo);
    strftime(dataHora,TAM_MAX_PALAVRA,"%d/%m/%Y %H:%M",infoTempo);
    // Abre o arquivo em modo "append" (adicionar ao final).
    FILE *arq = fopen(nomeArquivo,"a");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo: %s\n",nomeArquivo);
        exit(1);
    }
    // Escreve a linha no arquivo formatada.
    fprintf(arq,"[%s]\t%s\t%s\t%s\n",dataHora,p.nome,palavra,p.vidas>0?"Vitoria":"Derrota");
    fclose(arq);
}