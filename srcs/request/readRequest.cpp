/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 12:58:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	isEndHeader(std::vector<char>& header, int index)
{
	if (header[index] == '\n' && header[index - 1] == '\r' && header[index - 2] == '\n' && header[index - 3] == '\r')
		return (true);
	return (false);
}

bool	Server::readRequest(std::string& buffer)
{
	std::vector<char>	headerChar(MAXSIZEREQUEST);
	char				tmp[1];
	int					bytesRead = 0;
	int					indexArray = 0;

	while (true)
	{
		bytesRead = recv(_client_fd, tmp, 1, 0);
		if (bytesRead == -1)
			return (write_error("Error: readRequest"));
		if (bytesRead == 0)
			break;
		headerChar[indexArray] = tmp[0];
		if (isEndHeader(headerChar, indexArray))
			break;
		indexArray++;
	}
	buffer = std::string(headerChar.begin(), headerChar.end());
	return (true);
}
