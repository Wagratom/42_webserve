# checklist

## Mandatory part
- [ ] Seu programa deve aceitar um arquivo de configuração como argumento ou usar um caminho padrão.
- [ ] o pode executar outro servVocê nãidor da web usando execve.
- [ ] Seu servidor nunca deve bloquear e o cliente deve poder ser interrompido adequadamente, se necessário.
- [ ] Ele deve ser não-bloqueante e usar apenas 1 poll() (ou equivalente) para todas as operações de I/O entre o cliente e o servidor (incluindo listen).
- [ ] O poll() (ou equivalente) deve verificar leitura e escrita ao mesmo tempo.
- [ ] Você nunsca deve fazer uma operação de leitura ou escrita em passar pelo poll() (ou equivalente).
- [ ] Verificar o valor de errno é estritamente proibido após uma operação de leitura ou escrita.
- [ ] Você não precisa usar o poll() (ou equivalente) antes de ler seu arquivo de configuração.
- [ ]  Seu programa não deve falhar em nenhuma circunstância (mesmo quando ficar sem memória) e não deve sair inesperadamente. Se isso acontecer, o seu projeto será considerado não funcional e sua nota será 0.
- [ ] Você precisa entregar um Makefile que irá compilar seus arquivos de origem. Ele não deve fazer uma nova vinculação (relink).
- [ ] Seu Makefile deve conter pelo menos as regras: $(NAME), all, clean, fclean e re.
- [ ] Compile seu código com c++ e as flags -Wall -Wextra -Werror.
- [ ] Seu código deve estar em conformidade com o padrão C++ 98. Em seguida, ele ainda deve compilar se você adicionar a flag -std=c++98.
- [ ] Tente sempre desenvolver usando as funcionalidades mais recentes do C++ que puder (por exemplo, escolha <cstring> em vez de <string.h>). Você pode usar funções em C, mas sempre prefira suas versões em C++ se possível.
- [ ] Qualquer biblioteca externa e as bibliotecas Boost são proibidas.
