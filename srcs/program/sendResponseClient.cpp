/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendResponseClient.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:56:26 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 12:01:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::sendResponseClient(std::string response)
{
	if (_write == true)
		return (send(_client_fd, response.c_str(), response.size(), 0) != -1);
	return (true);
}
