/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_server.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:48:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::response_server(std::string status_code)
{
	aux_read_file tmp;

	if (!generete_path_to_response(tmp.path, server()->get_root(), server()->get_index()))
		return (false);
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, status_code);
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
