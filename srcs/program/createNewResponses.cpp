/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createNewResponses.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:03:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/20 11:01:53 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createNewResponses(int contentLenght)
{
	if (_responses.find(_client_fd) != _responses.end())
		return true;
	try {
		_responses.insert(std::pair<int, Response*>(_client_fd, new Response));
		_responses.at(_client_fd)->contentLenght = contentLenght;
		_responses.at(_client_fd)->write = _write;
		_responses.at(_client_fd)->method = getenv("REQUEST_METHOD");
		_responses.at(_client_fd)->port = _port;
		bzero(&_responses.at(_client_fd)->process, sizeof(ChildProcessData));
		return true;
	}
	catch (std::exception& e) {
		write_error("createValidResponse: " + std::string(e.what()));
		return false;
	}

}
