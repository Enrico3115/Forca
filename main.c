/**
 * @file main.c
 * @brief Arquivo principal do jogo da Forca.
 *
 * Responsavel por inicializar o jogo, controlar o laço principal
 * das partidas, coletar a entrada do usuario e chamar as funcoes
 * de logica do jogo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "forca.h"

int main (){
    // Inicializa a semente para geracao de numeros aleatorios.
    srand(time(NULL));

    // Declaracao das variaveis principais do jogo.
    Jogador p;
    char palavra[TAM_MAX_PALAVRA],palavraNaForca[TAM_MAX_PALAVRA],palavraTeste[TAM_MAX_PALAVRA],letra,c;
    int tamanhoArquivo = contarPalavras (ARQUIVO_PALAVRAS), letras[TAM_LETRAS];

    // Pede o nome do jogador apenas uma vez, no inicio do programa.
    do{
        printf("\nAntes de comecarmos, digite seu nome, pode ser apelido: ");
        fgets(p.nome,TAM_MAX_PALAVRA,stdin);
        apararString(p.nome);
    }while(p.nome[0]=='\0'); // Garante que nao foi digitada uma string vazia.

    // Laço principal do jogo: permite jogar multiplas partidas.
    do{
        // Limpa a tela para uma nova partida.
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Prepara as variaveis para uma nova rodada.
        zerarVetor(letras,TAM_LETRAS);
        carregarPalavras(ARQUIVO_PALAVRAS,palavra,tamanhoArquivo);
        reiniciarForca(palavraNaForca,strlen(palavra));
        iniciarPartida (&p); // Inicia vidas e contagem regressiva.

        // Laço de uma unica partida: continua enquanto o jogador tem vidas e nao acertou a palavra.
        while(p.vidas>0 && strcasecmp(palavra,palavraNaForca)!=0){
            // Limpa a tela a cada jogada para manter a interface limpa.
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            // Mostra o estado atual do jogo (forca, palavra, letras usadas).
            desenharForca(p,palavraNaForca,letras,TAM_LETRAS);

            // Pergunta ao jogador sua proxima acao (Letra ou Palavra).
            do{
                printf("Digite uma letra ou tente uma palavra (L/P): ");
                scanf(" %c",&c);
                limparBuffer();
            }while(toupper(c)!='L'&&toupper(c)!='P');
            printf("\n");

            // Se o jogador escolheu 'L' (Letra).
            if(toupper(c)=='L'){
                // Pede por uma letra valida.
                do{
                    printf("Digite uma letra valida: ");
                    scanf(" %c",&letra);
                    limparBuffer();
                }while(!isalpha(letra));

                // Verifica se a letra ja foi usada.
                if(verificarLetra(letra,letras)){
                    printf("\nLetra ja utilizada!");
                    p.vidas-=2; // Penalidade maior por erro repetido.
                }
                else{
                    // Se a letra nao esta na palavra, perde uma vida.
                    if(testarLetra(letra,palavra,palavraNaForca)==0){
                        p.vidas--;
                        printf("\nLetra errada!");
                    }
                }
            }
            // Se o jogador escolheu 'P' (Palavra).
            else{
                // Pede para o jogador digitar seu palpite.
                do{
                    printf("Digite uma palavra: ");
                    fgets(palavraTeste,TAM_MAX_PALAVRA,stdin);
                    apararString(palavraTeste);
                }while(palavraTeste[0]=='\0'); // Garante que nao foi digitada uma string vazia.

                // Compara a palavra do palpite com a palavra secreta.
                if(strcasecmp(palavra,palavraTeste)==0){
                    delayMS(DELAY_3s);
                    break; // Se acertou, sai do laço da partida.
                }
                else{
                    printf("\nPalavra errada!");
                    p.vidas-=2; // Penalidade maior por errar a palavra.
                }
            }
            // Um delay para o jogador poder ler a mensagem (letra errada, etc.).
            delayMS(DELAY_3s);
        }

        // --- Fim da Partida ---
        // Limpa a tela para mostrar o resultado final.
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Desenha o estado final do jogo, revelando a palavra.
        desenharForca(p,palavra,letras,TAM_LETRAS);

        // Exibe a mensagem de vitoria ou derrota.
        if(p.vidas>0) printf("\n\nParabens, %s! Voce acertou em cheio.\n",p.nome);
        else    printf("\n\nSinto muito, %s! Voce foi enforcado, fim de linha.\n",p.nome);

        // Salva o resultado no arquivo de resultados.
        registrarResultado(ARQUIVO_RESULTADOS,palavra,p);

        // Pergunta se o jogador quer jogar novamente.
        do{
            printf("\nQuer jogar novamente (S/N): ");
            scanf(" %c",&c);
            limparBuffer();
        }while(toupper(c)!='S'&&toupper(c)!='N');

    }while(toupper(c)=='S');

    return 0;
}