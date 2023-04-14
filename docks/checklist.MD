# checklist

## Mandatory part
- [ ] Seu programa deve aceitar um arquivo de configuração como argumento ou usar um caminho padrão.
- [X] Você não pode executar outro servidor web.
- [ ] Seu servidor nunca deve bloquear e o cliente deve poder ser interrompido adequadamente, se necessário.
- [ ] Ele deve ser não-bloqueante e usar apenas 1 poll() (ou equivalente) para todas as operações de I/O entre o cliente e o servidor (incluindo listen).
- [ ] O poll() (ou equivalente) deve verificar leitura e escrita ao mesmo tempo.
- [ ] Você nunsca deve fazer uma operação de leitura ou escrita em passar pelo poll() (ou equivalente).
- [ ] Verificar o valor de errno é estritamente proibido após uma operação de leitura ou escrita.
- [ ] Você não precisa usar o poll() (ou equivalente) antes de ler seu arquivo de configuração.

- [ ] Você pode usar todas as macros e definições, como FD_SET, FD_CLR, FD_ISSET, FD_ZERO (entender o que e como elas fazem é muito útil).
- [ ] Uma solicitação ao seu servidor nunca deve ficar pendurada para sempre.
- [ ] Seu servidor deve ser compatível com o navegador da web de sua escolha.
- [ ] Consideraremos que o NGINX está em conformidade com o HTTP 1.1 e pode ser usado para comparar cabeçalhos e comportamentos de resposta.
- [ ] Seus códigos de status de resposta HTTP devem ser precisos.
- [ ] Seu servidor deve ter páginas de erro padrão se nenhuma for fornecida.
- [ ] Você não pode usar o fork para algo que não seja CGI (como PHP ou Python, e assim por diante).
- [ ] Você deve ser capaz de servir um site totalmente estático.
- [ ] Os clientes devem ser capazes de fazer upload de arquivos.
- [ ] Você precisa pelo menos dos métodos GET, POST e DELETE.
- [ ] Faça testes de estresse em seu servidor. Ele deve permanecer disponível a todo custo.
- [ ] Seu servidor deve ser capaz de ouvir em várias portas (consulte o arquivo de configuração).
