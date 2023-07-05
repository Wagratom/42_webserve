/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/04 17:53:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	isEndHeader(std::vector<char>& header, int index)
{
	if (header[index] == '\n' && header[index - 1] == '\r' && header[index - 2] == '\n' && header[index - 3] == '\r')
		return (true);
	return (false);
}

bool	Server::read_request(std::string& buffer)
{
	std::vector<char>	headerChar(MAXSIZEREQUEST);
	int		bytesRead = 0;
	int		indexArray = 0;
	char	tmp[1];

	while (true)
	{
		bytesRead = recv(_client_fd, tmp, 1, 0);
		if (bytesRead == -1)
			return (write_error("Error: read_request"));
		if (bytesRead == 0)
			break;
		headerChar[indexArray] = tmp[0];
		if (isEndHeader(headerChar, indexArray))
			break;
		indexArray++;
	}
	buffer = std::string(headerChar.begin(), headerChar.end());
	write_debug(buffer);
	return (true);
}
