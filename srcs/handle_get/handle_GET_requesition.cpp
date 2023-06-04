/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 21:00:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

bool	Server::handle_GET_requesition( void )
{
	ChildProcessInfo child_info;

	child_info = (ChildProcessInfo){0, 0, 0, 0, 0}; // initialize struct with 0

	if (execute_cgi_in_chuild(child_info) == false)
		return (false);
	close(child_info.fd[1]);
	waitpid(child_info.pid, &child_info.status, 0);
	response_get(child_info);
	return (true);
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
