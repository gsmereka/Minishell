<!-- <h1 align="center"> Minishell </h1> -->

<div style="align:center">
  <img src="readme_content/Title.png" alt="minishellm">
</div>

# 42_Minishell
Este projeto tem o objetivo de escrever um shell simples utilizando C.

## Índice

1. [Sobre o Projeto](#sobre-o-projeto)
2. [Utilização](#utilização)
    1. [Demonstração](#demonstração)
3. [Dependências](#dependências)
4. [Instalação](#instalação)
5. [Funcionalidades](#funcionalidades)
6. [Etapas de produção](#etapas-de-produção)
    1. [Execução REPL](#execução-repl)
    2. [Lexer](#lexer)
    3. [Expander](#expander)
    4. [Parser](#parser)
    5. [Executor](#executor)
7. [Fluxograma](#fluxograma)
8. [Medalha](#medalha)

## Sobre o Projeto

Um shell é uma interface de linha de comando que permite a interação com o sistema operacional. Ele permite a execução de comandos, navegação no sistema de arquivos e automação de tarefas rotineiras. Os shells mais populares incluem o bash (usado no Linux e macOS) e o cmd (usado no Windows). Neste projeto, utilizaremos o bash como base para o desenvolvimento do minishell.

## Utilização:

Basta utilizar normalmente como o proprio bash, limitado apenas pelas [Funcionalidades](#funcionalidades).  

### Demonstração:

![minishell](readme_content/demonstração.gif) 

## Dependências:

* As seguintes bibliotecas:  
<signal.h>  
<stdio.h>  
<sys/types.h>  
<sys/stat.h>  
<dirent.h>  
<fcntl.h>  
<sys/wait.h>  

* Compilador gcc:  
sudo apt-get update  
sudo apt-get install build-essential  

* Biblioteca Readline:
sudo apt-get install libreadline-dev  

## Instalação:

1 - Abra o terminal e digite o comando git clone https://github.com/seu-usuario/minishell.git para clonar o repositório para um diretório de sua escolha.  
2 - Navegue até o diretório recém-clonado com o comando cd minishell.  
3 - Execute o comando make para compilar o código-fonte e gerar o arquivo executável 'minishell'.  
4 - Para executar o Minishell, navegue até o diretório onde o arquivo 'minishell' foi gerado e execute o comando ./minishell.  

## Funcionalidades:
- [✔️] Exibição de um prompt quando esperando por um novo comando
- [✔️] Armazenamento do histórico de comandos executados
- [✔️] Manipulação de ctrl + C, ctrl + D e ctrl + \ durante a exibição do prompt.
- [✔️] Manipulação de ctrl + C, ctrl + D e ctrl + \ de acordo com o bash.
- [✔️] Manipulação de aspas simples (') e duplas (").
- [✔️] Manipulação de variáveis de ambiente.
- [✔️] Implementação de redirecionamentos de entrada e saída e uso de pipes
- [✔️] Implementação de comandos internos: echo, cd, pwd, export, unset, env e exit
- [✔️] Procura e inicialização do programa correto a partir de caminhos relativos e absolutos.

## Etapas de produção

Abaixo estão descritas as etapas necessárias para o desenvolvimento do minishell.

### Execuçao REPL

A implementação do comportamento REPL (Read-Eval-Print Loop) é uma etapa crucial no desenvolvimento deste projeto. Ele permite a interação interativa com o usuário, lendo suas entradas, executando as demais etapas e exibindo os resultados em seguida apropriadamente. Ele então volta para o início do loop para ler a próxima entrada, permitindo ao usuário continuar a interagir com o programa.

![minishell](readme_content/fluxograma_repl.bmp)  

## Lexer

O Lexer é responsavel pelo processamento correto dos comandos digitados pelo usuário. O lexer irá dividir a string de entrada do usuário em palavras-chave (tokens) específicas e mais fáceis de gerenciar. Isso é essencial para garantir que os comandos sejam interpretados corretamente e executados da forma esperada.

![minishellm](readme_content/fluxograma_lexer.bmp)  

## Expander

É o responsável por expandir o valor das variáveis de ambiente em cada token, garantindo que o comando final terá o resultado esperado. Também deve tratar as diferenças de comportamento entre aspas simples e aspas duplas.

## Parser

O parser é responsável por analisar a sequência de palavras-chave geradas pelo lexer, verificando se elas seguem a formatação necessária antes de serem passadas para o executor. 

![minishellm](readme_content/parser.bmp)  

## Executor

O Executor é a parte responsável por receber a lista de palavras-chave formatada pelo parser, interpretar e definir a ordem de execução dos comandos. Ele também é responsável por lidar com os redirecionamentos de entrada e saída, garantindo que os dados sejam direcionados corretamente para os comandos. Ele também é responsável por realizar a execução efetiva dos comandos, garantindo que os comandos sejam executados de maneira adequada.

![minishellm](readme_content/executor.bmp)  

## Medalha
![minishell](https://user-images.githubusercontent.com/90937264/232136316-9469796b-aa25-4cb9-b754-aac975f6b83a.png)

