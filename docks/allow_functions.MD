# Allowed functions webserv

## [Execve](https://man7.org/linux/man-pages/man2/execve.2.html) \ `int execve(const char *pathname, char *const argv[], char *const envp[]);`

* `Execve()` executa o programa referenciado pelo `pathname` do arquivo. Isso faz com que o programa que está sendo executado pelo processo que chama a função seja substituído por um novo programa, com uma pilha, heap e segmentos de dados.
* `pathname` deve ser um executável binário ou um script começando com uma linha no formato:
* `argv` é uma matriz passada para o novo programa como seus argumentos de linha de comando. Por convenção, a primeiro string (ou seja, argv[0]) devem conter o nome do arquivo associado com o arquivo sendo executado. A matriz argv deve ser encerrada por um ponteiro NULL. (Assim, no novo programa, argv[argc] será  NULL.)
* `envp` é um array de envs (variaveis de ambiente), convencionalmente no formato chave=valor, que são passados como o ambiente do novo programa. A matriz envp deve ser encerrada por um ponteiro NULL.
* Em caso de error o execve ultiliza o errno para especificar.

## [Dup](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node22.html) \  `int dup(int oldfd);`

* `Dup()` cria uma cópia de um descritor de arquivo existente `oldfd` e fornece um novo descritor tendo exatamente as mesmas características que aquele passado como argumento na chamada. Ela garante que o valor de retorno seja o menor entre todos os valores de descritores possíveis.
* `Valor de retorno ` novo descritor de arquivo ou -1 em caso de erro.

## [Dup2](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node22.html) \ `int dup2(int oldfd, int newfd);`

* `Dup2()` determina que `newfd` será a cópia de `oldfd`, fechando antes `newfd` se ele já estiver aberto.
* `Valor de retorno ` novo descritor de arquivo ou -1 em caso de erro.

## [Pipe]()
