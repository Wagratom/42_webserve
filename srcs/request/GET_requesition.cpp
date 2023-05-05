/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_requesition.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:35:31 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 10:35:29 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

#include <sys/types.h>
#include <sys/wait.h>

#define TYPE_HTML "text/html\n\n"

// static std::string	path_file(std::string endPoint, std::string filename)
// {
	// if (endPoint == "/")
		// return (std::string("./" + filename));
	// return (std::string("." + endPoint + "/" + filename));
// }

static bool	create_tools( int fd[], int& pid)
{
	if (pipe(fd) == -1)
		write_error("Error: Server::GET_requesition: pipe");
	pid = fork();
	if (pid == -1)
		write_error("Error: Server::GET_requesition: fork");
	return(true);
}

int	Server::GET_requesition( void )
{
	int	fd[2];
	int	pid;
	int	status;

	create_tools(fd, pid);
	if (pid == 0)
		send_cgi(fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 0)
		send_response_to_client(fd[0]);
	char buffer[5000];

	while (read(fd[0], buffer, 5000));
	std::cout << buffer << std::endl;
	return (true);
}

bool	Server::send_cgi( int fd[] )
{
	char**		argv = new char*[3];
	std::string	path;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	generete_path_to_response(path);
	argv[0] = (char *)"/usr/bin/php-cgi";
	argv[1] = (char *)path.c_str();
	argv[2] = NULL;
	std::cout << "argv[1]: " << argv[1] << std::endl;
	if (execve("/usr/bin/php-cgi", argv, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (true);
}

bool	Server::send_response_to_client( int response )
{
	std::string	_response = "HTTP/1.1 200 OK\n";
	char	buffer[4096];
	int 	bytes_read;
	while (read(response, buffer, 4096))
	{
		bytes_read = read(response, buffer, 4096);
		if (bytes_read == -1)
			write_error("Error: Server::send_response_to_client: 500 Internal Server Error");
		_response += buffer;
	}
	send(_client_fd, _response.c_str(), _response.size(), 0);
	return (true);
}
