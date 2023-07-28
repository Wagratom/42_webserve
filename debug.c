	[0;31m	Debug mode is on[0;37m
[0;36m	Starting parser
[0;34mOpening/Reading file of confinguration...
File name: confis/ProjWJP.conf
ParserConfigurationFile...
[0;36m	Creating server configured
[0;34mCreating epoll...

Creating server...
Port: 8080
ServerName: www.localhost localhost

Creating server...
Port: 8081
ServerName: www.localhost localhost
[0;36m	Starting server[0;34m
New connection accepted: 6
New connection accepted: 7
createNewResponses
createNewResponses
cleanupFd: 7
cleanupResponse: 7
[0;36m
	 Header received
[0;34mPOST /uploads/ HTTP/1.1
Host: localhost:8080
Connection: keep-alive
Content-Length: 459756
Cache-Control: max-age=0
sec-ch-ua: "Not/A)Brand";v="99", "Microsoft Edge";v="115", "Chromium";v="115"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
Origin: http://localhost:8080
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary3JXsdY5KD027uQvU
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
cp-extension-installed: Yes
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: http://localhost:8080/
Accept-Encoding: gzip, deflate, br
Accept-Language: pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
Cookie: wp-settings-time-3=1680293779; wp-settings-time-1=1680607718

------W
[0;36m	 ENV Pasing
[0;34m
REQUEST_METHOD: POST
REQUEST_URI: /uploads/
SERVER_PROTOCOL: HTTP/1.1
SERVER_PORT8080
HTTP_HOSTlocalhost:8080
CONTENT_LENGTH=459756
CONTENT_TYPE=multipart/form-data; boundary=----WebKitFormBoundary3JXsdY5KD027uQvU
HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
HTTP_ACCEPT_ENCODING=gzip, deflate, br
HTTP_ACCEPT_LANGUAGE=pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
HTTP_CONNECTION=keep-alive
HTTP_COOKIE=wp-settings-time-3=1680293779; wp-settings-time-1=1680607718
HTTP_HOST=localhost:8080
HTTP_USER_AGENT=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
SERVER_PORT=8080
[0;36m	 Tratavive request
[0;34m
handlePostRequest
responseLocation: /uploads/
responseLocationPost
generetePathToResponse
handleScriptPOST
checkPermitionFile: ./root/scripts/handleUPLOAD.php
checkClientMaxBodySize
handlePostBody
createProcessResponse
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
Is end Post

Content-type: text/html; charset=UTF-8

Array
(
    [name] => TP_AEDI_salao_de_festas_2023-1.pdf
    [type] => application/pdf
    [tmp_name] => /tmp/phpiX86xc
    [error] => 0
    [size] => 459537
)
<br>Conteúdo do arquivo temporário:<br><pre></pre>Arquivo salvo com sucesso em ../../uploads/TP_AEDI_salao_de_festas_2023-1.pdfGenerete response to client process
Response server
hasProcess: 0
generetePathToResponse
getContentAllFile: ./root/index.html
hasProcess: 0
sendResponseClient
cleanupResponse: 6
Keep-Alive

createNewResponses
cleanupFd: 6
cleanupResponse: 6
New connection accepted: 6
createNewResponses
cleanupFd: 6
cleanupResponse: 6
New connection accepted: 6
createNewResponses
[0;36m
	 Header received
[0;34mGET /favicon.ico HTTP/1.1
Host: localhost:8080
Connection: keep-alive
sec-ch-ua: "Not/A)Brand";v="99", "Microsoft Edge";v="115", "Chromium";v="115"
sec-ch-ua-mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
sec-ch-ua-platform: "Windows"
Accept: image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: no-cors
Sec-Fetch-Dest: image
Referer: http://localhost:8080/uploads/
Accept-Encoding: gzip, deflate, br
Accept-Language: pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
Cookie: wp-settings-time-3=1680293779; wp-settings-time-1=1680607718


[0;36m	 ENV Pasing
[0;34m
REQUEST_METHOD: GET
REQUEST_URI: /favicon.ico
SERVER_PROTOCOL: HTTP/1.1
SERVER_PORT8080
HTTP_HOSTlocalhost:8080
CONTENT_LENGTH=null
CONTENT_TYPE=null
HTTP_ACCEPT=image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
HTTP_ACCEPT_ENCODING=gzip, deflate, br
HTTP_ACCEPT_LANGUAGE=pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
HTTP_CONNECTION=keep-alive
HTTP_COOKIE=wp-settings-time-3=1680293779; wp-settings-time-1=1680607718
HTTP_HOST=localhost:8080
HTTP_USER_AGENT=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
SERVER_PORT=8080
[0;36m	 Tratavive request
[0;34m
handle_GET_requesition
responseFileServer
getContentAllFile: ./root/favicon.ico
sendResponseClient
cleanupResponse: 6
Keep-Alive

createNewResponses
cleanupFd: 6
cleanupResponse: 6
New connection accepted: 6
createNewResponses
cleanupFd: 6
cleanupResponse: 6
checking Timeout process: 0
checking Timeout process: 0
New connection accepted: 6
createNewResponses
New connection accepted: 7
createNewResponses
cleanupFd: 7
cleanupResponse: 7
[0;36m
	 Header received
[0;34mPOST /uploads/ HTTP/1.1
Host: localhost:8080
Connection: keep-alive
Content-Length: 459756
Cache-Control: max-age=0
sec-ch-ua: "Not/A)Brand";v="99", "Microsoft Edge";v="115", "Chromium";v="115"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
Upgrade-Insecure-Requests: 1
Origin: http://localhost:8080
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryXDAjDbQsLY6EnmBC
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
cp-extension-installed: Yes
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: http://localhost:8080/uploads/
Accept-Encoding: gzip, deflate, br
Accept-Language: pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
Cookie: wp-settings-time-3=1680293779; wp-settings-time-1=1680607718

------Web
[0;36m	 ENV Pasing
[0;34m
REQUEST_METHOD: POST
REQUEST_URI: /uploads/
SERVER_PROTOCOL: HTTP/1.1
SERVER_PORT8080
HTTP_HOSTlocalhost:8080
CONTENT_LENGTH=459756
CONTENT_TYPE=multipart/form-data; boundary=----WebKitFormBoundaryXDAjDbQsLY6EnmBC
HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
HTTP_ACCEPT_ENCODING=gzip, deflate, br
HTTP_ACCEPT_LANGUAGE=pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
HTTP_CONNECTION=keep-alive
HTTP_COOKIE=wp-settings-time-3=1680293779; wp-settings-time-1=1680607718
HTTP_HOST=localhost:8080
HTTP_USER_AGENT=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.183
SERVER_PORT=8080
[0;36m	 Tratavive request
[0;34m
handlePostRequest
responseLocation: /uploads/
responseLocationPost
generetePathToResponse
handleScriptPOST
checkPermitionFile: ./root/scripts/handleUPLOAD.php
checkClientMaxBodySize
handlePostBody
createProcessResponse
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
handlePostBody
Read body post
handleProcessResponse
Is end Post

Content-type: text/html; charset=UTF-8

Array
(
    [name] => TP_AEDI_salao_de_festas_2023-1.pdf
    [type] => application/pdf
    [tmp_name] => /tmp/phpu2CEHN
    [error] => 0
    [size] => 459537
)
<br>Conteúdo do arquivo temporário:<br><pre></pre>Arquivo salvo com sucesso em ../../uploads/TP_AEDI_salao_de_festas_2023-1.pdfGenerete response to client process
Response server
hasProcess: 0
generetePathToResponse
getContentAllFile: ./root/index.html
hasProcess: 0
sendResponseClient
cleanupResponse: 6
Keep-Alive

createNewResponses
cleanupFd: 6
cleanupResponse: 6
New connection accepted: 6
createNewResponses
cleanupFd: 6
cleanupResponse: 6
