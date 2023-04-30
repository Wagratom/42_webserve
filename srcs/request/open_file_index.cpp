/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_index.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:35:31 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/30 17:40:24 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	open_file_status(std::string path, std::ifstream& file)
{
	file.open(path.c_str());

	std::cout << "path: " << path << std::endl;
	if (!file.is_open())
		return (false);
	return (true);
}

static std::string	path_file(std::string endPoint, std::string filename)
{
	if (endPoint == "/")
		return (std::string("./" + filename));
	return (std::string("." + endPoint + "/" + filename));
}

bool	Server::open_file_index( std::ifstream& file )
{
	size_t			pos;
	std::string		listNames;
	std::string		endPoint;

	pos = 0;
	listNames = server()->get_index();
	endPoint = _parser_request->get_endPoint();
	while (pos != std::string::npos)
	{
		pos = listNames.find_first_of(" \t");
		if (pos == std::string::npos)
			return (open_file_status(path_file(endPoint, listNames), file));
		if (open_file_status(path_file(endPoint, listNames.substr(0, pos)), file))
			return (true);
		listNames = listNames.substr((pos + 1));
	}
	return (false);
}

