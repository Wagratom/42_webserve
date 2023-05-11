/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 20:44:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

typedef struct s_ChildProcessInfo {
	int	fd[2];
	int	pid;
	int	status;
	int	exit_status;

} ChildProcessInfo;

static bool	execute_fork( ChildProcessInfo& infos)
{
	if (pipe(infos.fd) == -1)
		write_error("Error: Server::handle_GET_requesition: pipe");
	infos.pid = fork();
	if (infos.pid == -1)
		write_error("Error: Server::handle_GET_requesition: fork");
	return(true);
}

/*############################################################################*/
/*                         Executing cgi program                              */
/*############################################################################*/

bool	Server::execute_cgi_in_chuild( ChildProcessInfo& tools_chuild )
{
	if (execute_fork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
	{
		close(tools_chuild.fd[0]);
		dup2(tools_chuild.fd[1], STDOUT_FILENO);
		execute_cgi();
	}
	return (true);
}

void	Server::execute_cgi( void )
{
	char**		argv = new char*[3];
	std::string	path;

	if (!generete_path_to_response(path))
		exit(ERROR404);
	argv[0] = (char *)"/usr/bin/php-cgi";
	argv[1] = (char *)path.c_str();
	argv[2] = NULL;
	if (execve("/usr/bin/php-cgi", argv, NULL) == -1)
		exit(ERROR_SERVE);
	exit(ERROR_SERVE);
}

/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

int	Server::handle_GET_requesition( void )
{
	ChildProcessInfo child_info;

	child_info = (ChildProcessInfo){0, 0, 0, 0, 0}; // initialize struct with 0
	if (_parser_request->set_envs_header() == false)
		return (false);
	if (execute_cgi_in_chuild(child_info) == false)
		return (false);
	response_get(child_info);
	return (true);
}


/*############################################################################*/
/*                         response GET client                             */
/*############################################################################*/

void	Server::response_get( ChildProcessInfo& tools_chuild )
{
	close(tools_chuild.fd[1]);
	waitpid(tools_chuild.pid, &tools_chuild.status, 0);
	tools_chuild.exit_status = WEXITSTATUS(tools_chuild.status);
	write_debug_number("Status: ", tools_chuild.exit_status);
	if (WEXITSTATUS(tools_chuild.status) == 0)
	{
		if (send_response_to_client(tools_chuild.fd[0]) == false)
			send_response_error_to_client( ERROR_SERVE );
	}
	else
		send_response_error_to_client( tools_chuild.exit_status );
}

void	Server::send_response_error_to_client( int status )
{
	std::cout << "Status: " << status << std::endl;
	if (status == ERROR404)
	{
		std::string body = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
		std::string response = "HTTP/1.1 404 Not Found\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Connection: close\r\n\r\n";
		response += body;
		send(_client_fd, response.c_str(), response.size(), 0);
	}
	if (status == ERROR_SERVE)
	{
		std::string _response = "HTTP/1.1 500 Internal Server Error\n";
		send(_client_fd, _response.c_str(), _response.size(), 0);
	}
}
bool	Server::send_response_to_client( int response )
{
	std::string	_response = "HTTP/1.1 200 OK\n";
	char	buffer[4096];
	int 	bytes_read;
	while (true)
	{
		bytes_read = read(response, buffer, 4096);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			write_error("Error: Server::send_response_to_client: 500 Internal Server Error");
		_response += buffer;
	}
	std::cout << "Response: " << _response << std::endl;
	send(_client_fd, _response.c_str(), _response.size(), 0);
	return (true);
}
