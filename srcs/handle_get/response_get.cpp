/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_get.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 21:50:39 by wwallas-         ###   ########.fr       */
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
	send_response_error_to_client( tools_chuild.exit_status );
}
