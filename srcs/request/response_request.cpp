/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_request.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:18:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::parse_order_request( std::string& buffer )
{
	_parser_request = new Parser_request(buffer);

	if (_parser_request == NULL)
		return (write_error_prefix("Error: Server::parse_request: _parser_file is NULL"));
	if (_parser_request->set_envs_order_line(_verbs) == false)
		return (false);
	return (true);
}

bool	Server::response_request( std::string& buffer )
{
	if (parse_order_request(buffer) == false)
		return (false);
	if (_parser_request->set_envs_header() == false)
		return (false);
	if (_parser_request->get_metodo() == "GET")
		handle_GET_requesition();
	if (_parser_request->get_metodo() == "POST")
		return handle_POST_requesition();
	if (_parser_request->get_metodo() == "DELETE")
		std::cout << "Pediu DELETE" << std::endl;
	write_debug("\n");
	return (true);
}

bool	Server::handle_POST_requesition()
{
	char**		argv = new char*[4];
	setenv("HELLO", "hello_world", 1);

	argv[0] = (char *)"/usr/bin/php-cgi7.4";
	argv[1] = (char *)"/home/wallas/42_webserve/script.cgi";
	argv[2] = NULL;
	// std::string hello_env = "HELLO=hello_world";
	// char* envs[50];

	// envs[0] = strdup("REQUEST_METHOD=POST");
	// envs[1] = strdup("SERVER_PROTOCOL=HTTP/1.1");
	// envs[2] = strdup("CONTENT_LENGTH=21");
	// envs[3] = strdup("CONTENT_TYPE=application/x-www-form-urlencoded");
	// envs[4] = strdup("HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
	// envs[5] = strdup("HTTP_ACCEPT_ENCODING=gzip, deflate, br");
	// envs[6] = strdup("HTTP_ACCEPT_LANGUAGE=pt-BR,pt;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
	// envs[7] = strdup("HTTP_CONNECTION=keep-alive");
	// envs[8] = strdup("HTTP_COOKIE=wp-settings-time-3=1680293779; wp-settings-time-1=1680607718");
	// envs[9] = strdup("HTTP_HOST=localhost:8080");
	// envs[10] = strdup("HTTP_USER_AGENT=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.37");
	// envs[11] = strdup("SERVER_PORT=8080");
	// envs[12] = strdup("REDIRECT_STATUS=1");
	// envs[13] = strdup("SCRIPT_NAME=/home/wallas/42_webserve/script.cgi");
	// envs[14] = NULL;
	if (execve("/usr/bin/php-cgi7.4", argv, NULL) == -1)
	std::cout << strerror(errno) << std::endl;
	exit(ERROR_SERVE);
	return (true);
}
