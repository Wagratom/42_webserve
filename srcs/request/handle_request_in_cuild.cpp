/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request_in_cuild.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 15:23:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	error_in_request()
{
	int	i = -1;

	while (++i < 1025)
	{
		close(i);
		i++;
	}
	exit(EXIT_FAILURE);
}

bool	Server::configured_child(epoll_event& event)
{
	int	flags;

	_client_fd = event.data.fd;
	flags = fcntl(event.data.fd, F_GETFL, 0);
	if (flags == -1)
		return (write_error_prefix("Error: configured_child: not get properties"));
	if (fcntl(event.data.fd, F_SETFL, flags | O_NONBLOCK) == -1)
		return (write_error_prefix("Error: configured_child: not set properties"));
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _server_fd, &event) == -1)
		write_error_prefix("Error: configurad_child: not remove server from epoll");
	close(_server_fd);
	return (true);
}

void	reply_to_client(epoll_event& event)
{
	std::cout << "reply_to_client" << std::endl;
	std::string resposta = "HTTP/1.1 200 OK\r\n";
	resposta += "Content-Type: text/html\r\n\r\n";
	resposta += "<html><head><title>Exemplo</title></head><body><h1>Olá, mundo!</h1></body></html>";
	send(event.data.fd, resposta.c_str(), resposta.length(), 0);
}

/*############################################################################*/
/*                        Handle request in chuild                            */
/*############################################################################*/

void	Server::handle_request_in_child(epoll_event& event)
{
	write_debug("\tHandle_request_in_child");
	if (!configured_child(event))
		error_in_request();
	if (!control_chuild(event))
		error_in_request();
	exit(0);
}

bool	Server::control_chuild(epoll_event& event)
{
	std::string	buffer;

	while (true)
	{
		if (read_request(buffer, event) == false)
			return (false);
		if (buffer.empty())
			continue ;
		if (parse_request(buffer) == false)
			return (false);
		// if (cgi_response());
			// return (false);
		if (response_request() == false)
			return (false);
		if (capture_new_events(&event) == false)
			return (false);
		buffer.clear();
	}
	exit(0);
	return (true);
}
