/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientGET.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 09:32:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void	responseWithInputCGI(std::string endPoint, size_t questionMarkPos)
{
	std::string	scriptHandler	= "." + endPoint.substr(0, questionMarkPos);
	std::string query_string	= endPoint.substr(questionMarkPos + 1);

	std::cout << "HTTP/1.1 200 OK\r\n";
	setenv("QUERY_STRING", query_string.c_str(), 1);
	setenv("SCRIPT_FILENAME", scriptHandler.c_str(), 1);
	setenv("SCRIPT_NAME", "/usr/bin/php-cgi", 1);
	setenv("REDIRECT_STATUS", "200", 1);
	execlp(scriptHandler.c_str(), scriptHandler.c_str(), NULL);
}

bool	Server::handleInputGET(std::string endPoint)
{
	size_t				questionMarkPos	= endPoint.find("?");
	ChildProcessData	aux;

	std::cout << "handleInputGET" << std::endl;
	if (questionMarkPos == std::string::npos)
		return (write_error("Error: questionMarkPos not found"));
	if (executeFork(aux) == false)
		return (write_error("Error: Server::handleInputGET: executeFork"));
	if (aux.pid == CHILD_PROCESS) {
		dup2(_client_fd, STDOUT_FILENO);
		responseWithInputCGI(endPoint, questionMarkPos);
	}
	return (true);
}
