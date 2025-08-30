# Jogo da Forca
===================================================================
                        JOGO DA FORCA EM C
===================================================================

Trabalho Prático Final da disciplina de Programação e Desenvolvimento de Software I (PDS-I), da graduação
em Engenharia de Sistemas da UFMG.

-------------------------------------------------------------------
1. AUTOR
-------------------------------------------------------------------

Nome: Enrico Moreira Soares de Almeida

-------------------------------------------------------------------
2. DESCRIÇÃO DO PROJETO
-------------------------------------------------------------------

Este projeto é uma implementação completa do clássico jogo da forca, desenvolvido inteiramente na linguagem C.
A aplicação utiliza conceitos de programação estruturada, manipulação de arquivos, 
modularização e tratamento de entradas do usuário para oferecer uma experiência de jogo funcional e robusta.

-------------------------------------------------------------------
3. FUNCIONALIDADES PRINCIPAIS
-------------------------------------------------------------------

* Seleção aleatória de palavras a partir do arquivo "palavras.txt" a cada nova partida.
* Jogo interativo com desenho da forca e do boneco atualizados a cada jogada.
* Controle de letras já utilizadas para evitar palpites repetidos.
* Opção para o jogador tentar adivinhar a palavra inteira a qualquer momento.
* Registro de todas as partidas (nome do jogador, palavra, resultado e data/hora) no arquivo "resultados.txt".
* Sistema de "Jogar Novamente" para partidas consecutivas sem fechar o programa.
* Interface limpa, com limpeza de tela entre as jogadas.

-------------------------------------------------------------------
4. COMO COMPILAR E EXECUTAR
-------------------------------------------------------------------

O projeto foi desenvolvido em C padrão e não requer bibliotecas externas, apenas um compilador C.

**Pré-requisitos:**
* Um compilador C, como o GCC (GNU Compiler Collection), instalado no sistema.

**Passo 1: Compilação**

Navegue até a pasta raiz do projeto ("TP_Forca_Enrico") pelo terminal e execute os seguintes comandos para compilar os arquivos:

gcc -c forca.c

gcc main.c forca.o -o forca

Ou, de forma mais direta, utilizando apenas um comando, pode-se compilar dessa forma:

gcc main.c forca.c -o forca -Wall

Isso irá gerar um arquivo executável chamado "forca" (ou "forca.exe" no Windows). 

**Passo 2: Execução**

* No Linux ou macOS, execute o seguinte comando no terminal:
  ./forca

* No Windows (Prompt de Comando ou PowerShell), execute:
  .\forca.exe
  ou simplesmente
  forca

-------------------------------------------------------------------
5. COMO JOGAR
-------------------------------------------------------------------

- Ao iniciar o jogo, você será solicitado a inserir seu nome.
- O objetivo é adivinhar a palavra secreta, que é sorteada aleatoriamente pelo sistema.
- Você começa com 7 vidas.
- A cada rodada, você pode escolher entre duas ações:

  1. Tentar uma Letra (digitando 'L'):
     - Se a letra estiver na palavra, ela será revelada na posição correta.
     - Se a letra não estiver na palavra, você perde uma vida.
     - Se você repetir uma letra já usada, perderá duas vidas como penalidade.

  2. Tentar a Palavra Inteira (digitando 'P'):
     - Se você acertar a palavra, vence a partida imediatamente.
     - Se errar a palavra, perderá duas vidas como penalidade.

- O jogo termina quando você adivinha a palavra corretamente (Vitória) ou quando suas vidas chegam a zero (Derrota).
- Ao final, seu resultado é salvo em "resultados.txt" e você pode escolher jogar novamente.

-------------------------------------------------------------------
6. OBSERVAÇÕES
-------------------------------------------------------------------

* O projeto foi testado em ambiente Linux (com GCC) e Windows (com MinGW), e espera-se alta portabilidade entre sistemas.
* As entradas do usuário são tratadas para remover espaços extras e evitar erros com o buffer de entrada, tornando a experiência mais robusta.
