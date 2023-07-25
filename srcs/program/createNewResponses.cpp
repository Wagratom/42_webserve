/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createNewResponses.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:03:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/25 12:08:07 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createNewResponses(int contentLenght, const std::map<std::string, std::string*>& errorMap)
{
	write_debug("createNewResponses");
	if (_responses.find(_client_fd) != _responses.end())
		return true;
	try {
		_responses.insert(std::pair<int, Response*>(_client_fd, new Response));
		_responses.at(_client_fd)->contentLenght = contentLenght;
		_responses.at(_client_fd)->write = _write;
		_responses.at(_client_fd)->method = getenv("REQUEST_METHOD");
		_responses.at(_client_fd)->port = _port;
		_responses.at(_client_fd)->errorMap = errorMap;
		if (getenv("GET") && getenv("GET")[0] != '\0')
			_responses.at(_client_fd)->_isProcessAutoindex = true;
		return true;
	}
	catch (std::exception& e) {
		write_error("Error: createValidResponse: " + std::string(e.what()));
		return false;
	}

}
