/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendResponseClient.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:56:26 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 12:57:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::sendResponseClient(std::string response)
{
	if (_write == false)
		return true;
	if (send(_client_fd, response.c_str(), response.size(), 0) == -1)
		return (write_error("Error: handle_delete: send"));
	return (true);
}
