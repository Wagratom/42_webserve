/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 21:18:33 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::initializeDefaultErrorPage()
{
	_defaultErrorPage[ERROR404] = "./error_pages/404_lufy_pensativo.html";
	_defaultErrorPage[ERROR400] = "./error_pages/400_bad_request.html";
	_defaultErrorPage[ERROR415] = "./error_pages/415_unsupported_media.html";
	_defaultErrorPage[ERROR500] = "./error_pages/500_internal_server.html";
}

Server::Server(std::string filename)
			: _parserFile(new Parser_configuration(filename))
			, _parserRequest(NULL)
			, _server_fd(-1)
			, _epoll_fd(-1)
			, _number_of_events(-1)
			, _verbs(create_verbs())
{
	initializeDefaultErrorPage();
};

Server::~Server() {
	if (_parserRequest)
		delete _parserRequest;
	delete	_parserFile;
	for (int i = 0; i < 10; i++) {
		delete _verbs[i];
	}
	delete [] _verbs;
};
