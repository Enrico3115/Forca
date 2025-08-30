/**
 * @file forca.h
 * @brief Arquivo de cabecalho para o jogo da forca.
 *
 * Contem todas as definicoes de constantes, estruturas de dados
 * e prototipos de funcoes utilizadas no projeto do jogo da forca.
 */

// Define o tamanho maximo para strings como palavras e nomes.
#define TAM_MAX_PALAVRA 100
// Define o tamanho do alfabeto (A-Z) para o vetor de letras utilizadas.
#define TAM_LETRAS 27
// Define o nome do arquivo que contem o banco de palavras.
#define ARQUIVO_PALAVRAS "palavras.txt"
// Define o nome do arquivo para registrar os resultados das partidas.
#define ARQUIVO_RESULTADOS "resultados.txt"
// Define a quantidade inicial de vidas do jogador.
#define VIDAS 7
// Define um delay padrao de 1 segundo (em milissegundos).
#define DELAY_1s 1000
// Define um delay padrao de 3 segundos (em milissegundos).
#define DELAY_3s 3000

/**
 * @struct Jogador
 * @brief Estrutura para armazenar os dados do jogador.
 */
typedef struct{
    char nome[TAM_MAX_PALAVRA]; // Nome do jogador.
    int vidas;                  // Vidas restantes do jogador na partida atual.
} Jogador;

/**
 * @brief Remove espaços em branco do inicio e do fim de uma string.
 * @param str A string a ser modificada.
 */
void apararString (char *str);

/**
 * @brief Limpa o buffer de entrada (stdin) ate a proxima quebra de linha.
 */
void limparBuffer (void);

/**
 * @brief Pausa a execucao do programa por um determinado tempo.
 * @param milissegundos O tempo de pausa em milissegundos.
 */
void delayMS (int milissegundos);

/**
 * @brief Conta o numero de palavras (linhas) em um arquivo.
 * @param nomeArquivo O nome do arquivo a ser lido.
 * @return O numero de linhas no arquivo.
 */
int contarPalavras (char *nomeArquivo);

/**
 * @brief Preenche um vetor de inteiros com o valor zero.
 * @param v O vetor a ser zerado.
 * @param n O tamanho do vetor.
 */
void zerarVetor (int v[], int n);

/**
 * @brief Carrega uma palavra aleatoria de um arquivo.
 * @param nomeArquivo O nome do arquivo de palavras.
 * @param palavra A string que recebera a palavra sorteada.
 * @param tamanho O numero total de palavras no arquivo.
 */
void carregarPalavras (char *nomeArquivo, char *palavra, int tamanho);

/**
 * @brief Prepara a string da forca com underscores '_'.
 * @param str A string a ser preenchida com '_'.
 * @param tamanho O comprimento da palavra secreta.
 */
void reiniciarForca (char *str, int tamanho);

/**
 * @brief Inicia uma nova partida, reiniciando vidas e exibindo uma contagem regressiva.
 * @param p Ponteiro para a struct do jogador.
 */
void iniciarPartida (Jogador *p);

/**
 * @brief Desenha o estado atual do jogo na tela.
 * @param p A struct do jogador (para saber as vidas).
 * @param palavra A string que mostra os acertos e os underscores.
 * @param letras O vetor que controla as letras ja utilizadas.
 * @param n O tamanho do vetor de letras.
 */
void desenharForca (Jogador p, char *palavra, int letras[], int n);

/**
 * @brief Verifica se uma letra ja foi utilizada e a marca como usada.
 * @param letra A letra a ser verificada.
 * @param letras O vetor de controle de letras.
 * @return 1 se a letra ja foi usada, 0 caso contrario.
 */
int verificarLetra (char letra, int letras[]);

/**
 * @brief Testa se a letra digitada existe na palavra secreta.
 * @param letra A letra digitada pelo jogador.
 * @param palavra A palavra secreta.
 * @param palavraNaForca A string de exibicao a ser atualizada com os acertos.
 * @return O numero de vezes que a letra foi encontrada na palavra.
 */
int testarLetra (char letra, char *palavra, char *palavraNaForca);

/**
 * @brief Registra o resultado da partida no arquivo de resultados.
 * @param nomeArquivo O nome do arquivo de resultados.
 * @param palavra A palavra secreta da partida.
 * @param p A struct do jogador com o resultado.
 */
void registrarResultado (char *nomeArquivo, char *palavra, Jogador p);