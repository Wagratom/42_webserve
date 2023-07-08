/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendResponseClient.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:56:26 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 14:09:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::sendResponseClient(std::string response)
{
	std::cout << "sendResponseClient" << std::endl;
	if (_write != true)
		return (true);
	if ((send(_client_fd, response.c_str(), response.size(), 0) < 0))
		return (write_error("Server::sendResponseClient: send"));
	return (true);
}
