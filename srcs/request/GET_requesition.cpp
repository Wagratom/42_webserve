/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_requesition.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:35:31 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 09:38:30 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

#include <sys/types.h>
#include <sys/wait.h>

#define TYPE_HTML "text/html\n\n"

// static std::string	path_file(std::string endPoint, std::string filename)
// {
// 	if (endPoint == "/")
// 		return (std::string("./" + filename));
// 	return (std::string("." + endPoint + "/" + filename));
// }

int	Server::GET_requesition( void )
{
	int fd[2];

	if (pipe(fd) == -1)
		write_error("Error: Server::GET_requesition: pipe");
	int pid = fork();
	if (pid == -1)
		write_error("Error: Server::GET_requesition: fork");
	if (pid == 0)
	{
		char**	argv = new char*[3];

		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		argv[0] = (char *)"/usr/bin/php-cgi";
		argv[1] = (char *)_parser_request->get_endPoint().c_str();
		argv[2] = NULL;
		if (execve("/usr/bin/php-cgi", argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	char buffer[5000];

	while (read(fd[0], buffer, 5000));
	std::cout << buffer << std::endl;
	return (true);
}

/*
int	Server::GET_requesition( void )
{
	boost::process::environment env;
	std::ifstream	file;

	write_debug("GET request response");
	env["REQUEST_METHOD"] = "GET";
	env["QUERY_STRING"] = "name=John&age=30";
	env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	env["CONTENT_LENGTH"] = "27";
	env["HTTP_COOKIE"] = "session_id=123456789";
	if (!open_file_index(file))
		return (404);
	if (serv_webpage(file) == false)
		return (0);
	return (true);
}
*/

bool	Server::serv_webpage( std::ifstream& file)
{
	std::string		content_file;
	std::string		buffer;

	content_file = "HTTP/1.1 200 OK\r\n";
	content_file += "Content-Type: text/html\r\n\r\n";
	while (std::getline(file, buffer))
		content_file += buffer;
	if (send(_client_fd, content_file.c_str(), content_file.length(), 0) == -1)
		return (false);
	return (true);
}

