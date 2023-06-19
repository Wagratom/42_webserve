/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_get.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 19:02:10 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	create_response(int& buffer_html, std::string& response)
{
	char	buffer[4096];
	int		bytes_read = 1;

	while (true)
	{
		bytes_read = read(buffer_html, buffer, 4096);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			write_error("Error: Server::sendresponse_to_client: 500 Internal Server Error");
		buffer[bytes_read] = '\0';
		response += buffer;
	}
	return (true);
}
bool	Server::send_response_to_client( int& buffer_html )
{
	std::string	response;

	response = "HTTP/1.1 200 OK\n";
	if (create_response(buffer_html, response) == false)
		return (false);
	if (send(_client_fd, response.c_str(), response.size(), 0) == false)
		write_error_prefix("Error: Server::sendresponse_to_client: send");
	return (true);
}

void	Server::response_get( ChildProcessInfo& tools_chuild )
{
	tools_chuild.exit_status = WEXITSTATUS(tools_chuild.status);
	if (WEXITSTATUS(tools_chuild.status) == 0)
	{
		if (send_response_to_client(tools_chuild.fd[0]) == true)
			return ;
	}
	sendErrorResponseToClient( tools_chuild.exit_status );
}

bool	Server::sendErrorToClient( std::string path, header function_to_create_header)
{
	std::string		response = (*function_to_create_header)();
	aux_read_file	aux;

	aux.path = path;
	if (!getContentFile(aux))
		return (false);
	response += aux.content;
	if (send(_client_fd, response.c_str(), response.size(), 0) == -1)
		return (write_error("Error: Server::send_error_404: send"));
	return (true);
}

bool	Server::sendErrorResponseToClient( int status )
{
	std::cout << "Status: " << status << std::endl;
	if (status == ERROR404)
		sendErrorToClient("./error_pages/404_lufy_chorando.html", &create_header_404);
	else if (status == ERROR_INTERNAL)
		sendErrorToClient("./error_pages/500_internal_server.html", &create_header_500);
	else if (status == ERROR_BAD_REQUEST)
		sendErrorToClient("./error_pages/400_bad_request.html", &create_header_400);
	return (false);
}
