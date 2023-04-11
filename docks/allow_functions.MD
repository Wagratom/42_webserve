# Allowed functions webserv

## [Execve](https://man7.org/linux/man-pages/man2/execve.2.html) \ `int execve(const char *pathname, char *const argv[], char *const envp[]);`

* `execve()` executa o programa referenciado pelo `pathname` do arquivo. Isso faz com que o programa que está sendo executado pelo processo que chama a função seja substituído por um novo programa, com uma pilha, heap e segmentos de dados.
* `pathname` deve ser um executável binário ou um script começando com uma linha no formato:
* `argv` é uma matriz passada para o novo programa como seus argumentos de linha de comando. Por convenção, a primeiro string (ou seja, argv[0]) devem conter o nome do arquivo associado com o arquivo sendo executado. A matriz argv deve ser encerrada por um ponteiro NULL.
* `envp` é um array de envs (variaveis de ambiente), convencionalmente no formato chave=valor, que são passados como o ambiente do novo programa. A matriz envp deve ser encerrada por um ponteiro NULL.
* `Valor de retorno:` Em caso de erro -1 é retornado e [errno](#errno) é definido para indicar o erro.

## [Dup](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node22.html) \  `int dup(int oldfd);`

* `dup()` cria uma cópia de um descritor de arquivo existente `oldfd` e fornece um novo descritor tendo exatamente as mesmas características que aquele passado como argumento na chamada.
* Ela garante que o valor de retorno: seja o menor entre todos os valores de descritores possíveis.
* `Valor de retorno: ` novo descritor de arquivo ou -1 em caso de erro.

## [Dup2](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node22.html) \ `int dup2(int oldfd, int newfd);`

* `dup2()` determina que `newfd` será a cópia de `oldfd`, fechando antes `newfd` se ele já estiver aberto.
* `Valor de retorno: ` novo descritor de arquivo ou -1 em caso de erro.

## [Pipe](https://man7.org/linux/man-pages/man2/pipe.2.html) \ `int pipe(int pipefd[2]);`

* `pipe()` cria um pipe, um canal de dados unidirecional que pode ser usado para comunicação entre processos. A matriz `pipefd` é usada para retorna dois descritores de arquivo referentes às extremidades do tubo.
* `pipefd[0]` refere-se à extremidade de leitura do tubo.
* `pipefd[1]` refere-se para a extremidade de gravação do tubo.
* Dados gravados no final de gravação de o pipe é armazenado em um buffer pelo kernel até que seja lido  da extremidade de leitura do pipe.
* `Valor de retorno:` Em caso de erro -1 é retornado e [errno](#errno) é definido para indicar o erro.

## [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html) \ `char *strerror(int errnum);`

* `strerror()` retorna um ponteiro para uma string que descreve o código de erro passado como argumento em `errnum` (geralmente [errno](#errno)), possivelmente usando a parte LC_MESSAGES da localidade atual para selecionar o idioma apropriado.
* Esta string não pode ser modificada pela aplicação, mas pode ser modificada por uma chamada subsequente a strerror()
* `valor de retorno:` A função strerror() retorna a string de descrição de erro apropriada, ou uma mensagem "Erro desconhecido nnn" se o número de erro for desconhecido.

## [gai_strerro](https://man7.org/linux/man-pages/man3/gai_strerror.3p.html) \ `const char *gai_strerror(int ecode);`
* `gai_strerror()` retorna uma string de texto descrevendo um valor de erro para as funções [getaddrinfo](#getaddrinfo) e `getnameinfo()` listadas no cabeçalho <netdb.h>.
* `Valor de retorno:` retorna um ponteiro para uma string que descreve o erro em caso de falha. Se o argumento passado para a função não for um valor de erro conhecido, a função retornará um ponteiro para uma string que indica um erro desconhecido.

## [Errno](#errno)
* `errno` é uma variável global definida na biblioteca padrão da linguagem C e é usada para indicar o tipo de erro que ocorreu durante a execução de uma chamada de sistema ou de uma função da biblioteca padrão.
* Cada valor possível para errno corresponde a um código de erro específico, que é documentado em detalhes na documentação da função ou da chamada de sistema correspondente.
* `Valor de retorno:` none

## [Fork](https://man7.org/linux/man-pages/man2/fork.2.html) \ `pid_t fork(void);`
* `fork()` cria um novo processo duplicando o processo que a chamou. O novo processo é referido como processo filho, enquanto o processo que chamou é referido como processo pai.
* O processo filho e o processo pai são executados em espaços de memória separados. Ambos os espaços de memória possuem o mesmo conteúdo exceto pelos seguintes pontos... As gravações de memória, mapeamentos de arquivo e desmapeamentos realizados por um dos processos não afetam o outro.
* `valor de retnorno` Em caso de sucesso, o PID do processo filho é retornado no processo pai, e 0 é retornado no processo filho. Em caso de falha, -1 é retornado no processo pai, nenhum processo filho é criado, e [errno](#errno) é definido para indicar o erro.

## [Htons, Htonl, Ntohs, Ntohl](https://www.gta.ufrj.br/ensino/eel878/sockets/htonsman.html)

* são funções de conversão de `byte order` em C. Elas são usadas para converter números inteiros entre as representações de `byte order host` e `network`.
* A representação de `byte order host` é a forma como os bytes são armazenados na memória em um determinado sistema, enquanto a representação de `byte order network` é uma convenção universal para a representação de dados em redes de computadores. Essas funções são usadas para garantir que as comunicações em rede sejam realizadas corretamente, independentemente da arquitetura do sistema que está enviando ou recebendo dados.
* `Valor de retorno:` Cada função retorna o valor convertido.

## [Select](https://man7.org/linux/man-pages/man2/select.2.html) \ `int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, struct timeval *restrict timeout);`

* `select()` permite que um programa monitore vários descritores de arquivos, aguardando até que um ou mais dos descritores de arquivos estejam "prontos" para alguma classe de operação de E/S (Saida/Entrada). Um descritor de arquivo é considerado pronto se for possível executar uma operação de E/S correspondente (por exemplo, read(2), ou um write(2) suficientemente pequeno) sem bloquear.
* select so  pode monitorar descritores de arquivos cujos números sejam menores que FD_SETSIZE (1024). Todas as aplicações modernas devem, em vez disso, deve usar [poll](#poll) ou [epoll](#epoll), que não sofrem essa limitação.
* `valor de retorno:` em caso de sucesso retornam o número de descritores de arquivo contidos nos três conjuntos de descritores retornados (ou seja, o número total de bits definidos em readfds, writefds, exceptfds). O valor de retorno: pode ser zero se o tempio lmite expirou antes de algum descritor de arquivo ficar pronto. Em caso de erro, -1 é retornado e [errno](#errno) é definido para indicar o erro; os conjuntos de descritores de arquivo não são modificados e o tempo limite se torna indefinido.

## [Poll](https://man7.org/linux/man-pages/man2/poll.2.html) \ `int poll(struct pollfd *fds, nfds_t nfds, int timeout);`

* `poll()` realiza uma tarefa semelhante ao [select](#select) : aguarda que um conjunto de descritores de arquivos se torne pronto para executar operações de E/S.
* A principal diferença entre as duas é que o [select](#select) tem um limite máximo para o número de descritores de arquivo que pode monitorar, enquanto o `poll()` não tem esse limite.

## [Epoll](https://man7.org/linux/man-pages/man7/epoll.7.html)
* Tanto a `API epoll` quanto a `API poll` têm a mesma finalidade: monitorar múltiplos descritores de arquivo para ver se a E/S é possível em qualquer um deles.
* A principal diferença é que o poll é baseado em lista e pode ser lento quando usado com grandes conjuntos de descritores de arquivo, pois precisa pesquisar toda a lista de descritores de arquivo sempre que um evento ocorre. Em contraste, o epoll é baseado em árvore e é escalável, o que significa que seu desempenho não é afetado pelo tamanho do conjunto de descritores de arquivo.

## [Epoll_create](https://man7.org/linux/man-pages/man2/epoll_create.2.html) \ `int epoll_create(int size);`

* `epoll_create()` retorna um descritor de arquivo que se refere à nova instância [epoll](#epoll). Este descritor de arquivo é usado para todas as chamadas subsequentes à interface epoll.
* `size` base no número máximo esperado de descritores de arquivo a serem monitorados. Esse numero pode ser aumentado.
* `Valor de retorno:` Essas chamadas de sistema retornam um descritor de arquivo (um inteiro não negativo) em caso de sucesso. Em caso de erro, -1 é retornado e [errno](#errno) é configurado para indicar o erro.

## [Epoll_ctl](https://man7.org/linux/man-pages/man2/epoll_ctl.2.html) \ ` int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`

* Esta chamada do sistema é usada para adicionar, modificar ou remover entradas na lista de interesse da instância epoll](#epoll) referenciada pelo descritor de arquivo e`pfd`. Ela solicita que a operação op seja realizada para o descritor de arquivo de destino, `fd`.
* Os valores válidos para o argumento op são...
* Quando bem-sucedida, epoll_ctl() retorna zero. Quando ocorre um erro, epoll_ctl() retorna -1 e [errno](#errno) é definido para indicar o erro.

## [Epoll_wait](https://man7.org/linux/man-pages/man2/epoll_wait.2.html) \ `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`

* `epoll_wait()` aguarda por eventos na instância [epoll](#epoll) referenciada pelo descritor de arquivo `epfd`. O buffer apontado por `events` é usado para retornar informações da lista de prontos sobre descritores de arquivo na lista de interesse que têm alguns eventos disponíveis. Até `maxevents` são retornados por epoll_wait(). O argumento maxevents deve ser maior que zero.
* `Valor de retorno:` em caso de sucesso, retorna o número de descritores de arquivo prontos para a entrada/saída solicitada, ou zero se nenhum descritor de arquivo ficou pronto durante o tempo limite solicitado em milissegundos. Em caso de falha, retorna -1 e define [errno](#errno) para indicar o erro.


## [socket](https://man7.org/linux/man-pages/man2/socket.2.html) \ `int socket(int domain, int type, int protocol);`
* `socket()` cria um ponto de extremidade para comunicação e retorna um descritor de arquivo que se refere a esse ponto de extremidade.
* `Type` especifica o tipo de socket a ser criado, que determina o comportamento da comunicação.
* `domain` especifica um domínio de comunicação; isso seleciona a família de protocolos que será usada para comunicação.
* O `protocolo` especifica um protocolo particular a ser usado com o socket. Normalmente, apenas um único protocolo existe para suportar um tipo de socket específico dentro de uma determinada família de protocolos.

## [Accept](https://man7.org/linux/man-pages/man2/accept.2.html) \ `int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);`

* `accept()` é usada com tipos de socket. Ela extrai o primeiro pedido de conexão na fila de conexões pendentes para o socket de escuta, `sockfd`, cria um novo socket conectado e retorna um novo descritor de arquivo que se refere a esse socket.
`Valor de retorno:` em caso de sucesso, retornam um descritor de arquivo para o soquete aceito (um inteiro não negativo). Em caso de erro, -1 é retornado, [errno](#errno) é definido para indicar o erro e addrlen permanece inalterado.

## [listen](https://man7.org/linux/man-pages/man2/listen.2.html) \ `int listen(int sockfd, int backlog);`

* `listen()` marca o socket referido pelo descritor de arquivo `sockfd` como um socket passivo, ou seja, como um socket que será usado para aceitar solicitações de conexão entrantes usando a função `accept(2)`.
* `sockfd` é um descritor de arquivo que se refere a um socket do tipo SOCK_STREAM ou SOCK_SEQPACKET.
* `backlog` define o comprimento máximo que a fila de conexões pendentes para sockfd pode crescer. Se uma solicitação de conexão chegar quando a fila estiver cheia, o cliente pode receber um erro com uma indicação de ECONNREFUSED ou, se o protocolo subjacente suportar retransmissão, a solicitação pode ser ignorada para que uma nova tentativa de conexão tenha sucesso mais tarde.
* `Valor de retorno:` Em caso de sucesso, a função retorna zero. Em caso de erro, a função retorna -1 e a variável [errno](#errno) é configurada para indicar o erro.

## [Send](https://man7.org/linux/man-pages/man2/send.2.html) \ `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`

* `send()` permitem enviar mensagens de um socket para outro. A chamada `send()` só pode ser usada quando o socket está em um estado conectado (para que o destinatário pretendido seja conhecido). A única diferença entre `send()` e `write(2)` é a presença de flags.
* `Valor de retorno:` em caso de sucesso, retornam o número de bytes enviados. Em caso de erro, -1 é retornado e [errno](#errno) é definido para indicar o erro.

## [Bind](https://man7.org/linux/man-pages/man2/bind.2.html) \ `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

* `bind()` é usada para associar um endereço a um socket criado com a função `socket()`. O endereço especificado é atribuído ao socket referido pelo descritor de arquivo `sockfd`.
* O tamanho da estrutura de endereço é especificado pelo parâmetro `addrlen`.
* `Valor de retorno: ` em caso de sucesso, é retornado zero. Em caso de erro, é retornado -1 e [errno](#errno) é definido para indicar o erro.

## [connect](https://man7.org/linux/man-pages/man2/connect.2.html) \ `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

* `connect()` conecta o socket referido pelo descritor de arquivo `sockfd` ao endereço especificado por `addr`. O argumento `addrlen` especifica o tamanho de `addr`
* O formato do endereço em `addr` é determinado pelo espaço de endereços do socket `sockfd`.
* `Valor de retorno: ` em caso de sucesso, é retornado zero. Em caso de erro, é retornado -1 e [errno](#errno) é definido para indicar o erro.

## [getaddrinfo](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
* `getaddrinfo()` é frequentemente usada para obter uma lista de endereços que um servidor pode usar para vincular ou conectar. A função retorna uma lista de estruturas `addrinfo`, cada uma contendo informações de endereço que podem ser usadas para se comunicar com outras máquinas na rede.
* Com base nessas informações, o servidor pode escolher o endereço mais apropriado para vincular ou conectar, dependendo das suas necessidades.
* `Valor de retorno:` retorna 0 se for bem sucedido, ou um dos seguintes códigos de erro diferentes de zero...

## [freeaddrinfo](https://man7.org/linux/man-pages/man3/freeaddrinfo.3p.html)

* `freeaddrinfo()` libera uma ou mais estruturas addrinfo retornadas por [getaddrinfo](#getaddrinfo), juntamente com qualquer armazenamento adicional associado a essas estruturas.
* Se o campo `ai_next` da estrutura não for nulo, a lista inteira de estruturas será liberada. A função `freeaddrinfo()` suporta a liberação de sublistas arbitrárias de uma lista de addrinfo originalmente retornada por getaddrinfo().
* `Valor de retorno:` none.

## [setsockopt](https://man7.org/linux/man-pages/man3/setsockopt.3p.html)
* `setsockopt()` é usada para configurar opções de um socket, como o tempo limite de recebimento ou envio de dados. É necessário especificar o nível do protocolo em que a opção reside e o nome da opção, além do valor que se deseja atribuir a ela.
* `Valor de retorno` em caso de sucesso, retorna 0. Caso contrário, retornará -1 e setará a variável [errno](#errno) para indicar o erro ocorrido.

## [getsockname](https://man7.org/linux/man-pages/man2/getsockname.2.html)

* `getsockname()` retorna o endereço atual para o qual o socket sockfd está vinculado, no buffer apontado por `addr`. O argumento `addrlen` deve ser inicializado para indicar a quantidade de espaço (em bytes) apontada por `addr`. Ao retornar, ele contém o tamanho real do endereço do socket. O endereço retornado é truncado se o buffer fornecido for muito pequeno; nesse caso, addrlen retornará um valor maior do que foi fornecido na chamada.
* `Valor de retorno` Em caso de sucesso, o valor 0 é retornado. Em caso de erro, o valor -1 é retornado e a variável [errno](#errno) é definida para indicar o erro.

## [getprotobyname](https://man7.org/linux/man-pages/man3/getprotent.3p.html)

* `getprotobyname()` Ela recebe como argumento uma string contendo o nome do protocolo e retorna um ponteiro para a estrutura `protoent`, que contém informações como o nome do protocolo, número do protocolo e família de protocolo.
`Valor de retorno`  em caso de falhar, ela retorna um ponteiro nulo e define a variável [errno](#errno) para indicar o erro.

## [fcntl](https://man7.org/linux/man-pages/man2/fcntl.2.html)

* `fcntl` usada para modificar outras propriedades do descritor de arquivo, como alterar suas propriedades, definir o tamanho do buffer de leitura e escrita, ativar o modo assíncrono ou habilitar a execução do descritor de arquivo como um processo filho independente do processo principal.
