/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/27 10:15:45 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_POST_requesition()
{
	aux_upload	dataRequest;
	std::string	contentLength = _parserRequest->get_envsMap("CONTENT_LENGTH");
	int			contentLenght = std::strtol(contentLength.c_str(), NULL, 10);

	std::cout << "handle_POST_requesition" << std::endl;
	if (server()->get_clientMaxBodySize() < contentLenght)
		return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	dataRequest.request = _parserRequest->get_request();
	dataRequest.fd = _client_fd;
	dataRequest.bodySize = dataRequest.request.length();
	dataRequest.contentLength = contentLenght;
	dataRequest.bytes_read = 0;
	return (responseClientPOST(dataRequest));
}
