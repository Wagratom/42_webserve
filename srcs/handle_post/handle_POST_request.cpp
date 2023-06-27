/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 20:18:30 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_POST_requesition()
{
	// TODO: check if the body is bigger than client_max_body_size
	aux_upload	data;

	std::cout << server()->get_client_max_body_size() << std::endl;
	data.request = _parserRequest->get_request();
	data.body_length = data.request.length();
	data.fd = _client_fd;
	data.content_length = std::strtol(_parserRequest->get_envsMap("CONTENT_LENGTH").c_str(), NULL, 10);
	data.bytes_read = 0;

	return (responseClientPOST(data));
}
