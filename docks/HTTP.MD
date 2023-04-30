## Request http
```
1 GET /index.html HTTP/1.1
2 Host: www.example.com
3 User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:80.0) Gecko/20100101 Firefox/80.0
4 Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
5 Accept-Language: en-US,en;q=0.5
6 Accept-Encoding: gzip, deflate, br
7 Connection: keep-alive
8 Upgrade-Insecure-Requests: 1
```

<h3>Order line</h3>

<p>* Linha 1, contém o método de: <strong>solicitação</strong> (GET), o <strong>recurso solicitado</strong> (/index.html) e a <strong>versão do protocolo</strong> HTTP usada (HTTP/1.1).</p>

<h3>order header</h3>
<p>São As demais linhas, que contém:<br>
* Linha 2 contém o <strong>Host do servidor</strong>,<br>
* Linha 3 contém o <strong>User-Agent do navegador usado</strong>,<br>
* Linha 4 contém as <strong>preferências de Accept para tipos de conteúdo</strong>,<br>
* Resto contêm as informações relevantes para a solicitação. </p>

## Types verbs

* Esses são os principais métodos de solicitação (request) HTTP que podem ser usados para interagir com recursos em um servidor web

	* `GET` solicita um recurso específico. Geralmente usado para recuperar informações de uma página da web.
	* `POST` envia dados para o servidor para processar. Geralmente usado para enviar formulários e outros dados do usuário para o servidor.
	* `PUT` atualiza um recurso existente com novos dados.  Geralmente usado para atualizar informações existentes em um servidor.
	* `DELETE` remove um recurso específico do servidor. Geralmente usado para excluir informações do servidor.
	* `PATCH` atualiza parcialmente um recurso existente. Geralmente usado para excluir informações do servidor.
	* `OPTIONS` solicita informações sobre os métodos de solicitação suportados pelo servidor e outras opções de comunicação.
	* `HEAD` solicita apenas os cabeçalhos de resposta, sem o corpo da mensagem. Geralmente usado para verificar informações sobre um recurso sem baixar todo o conteúdo.
	* `TRACE` retorna uma mensagem de resposta que contém informações sobre como a solicitação foi tratada pelo servidor. Geralmente usado para fins de depuração.
	* `CONNECT` estabelece um túnel para o servidor para transmissão de dados criptografados. Geralmente usado em conexões seguras SSL.
