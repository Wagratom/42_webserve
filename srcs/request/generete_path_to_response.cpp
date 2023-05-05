/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generete_path_to_response.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:04:00 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 13:16:01 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	open_file_status( std::string path )
{
	std::ifstream	file(path.c_str());

	if (!file.is_open())
		return (false);
	write_debug_prefix("File opening: ", path);
	return (true);
}

static std::string	path_file( std::string endPoint, std::string filename )
{
	if (endPoint == "/")
		return (std::string("./" + filename));
	return (std::string("." + endPoint + "/" + filename));
}

bool	get_path(std::string listNames, std::string endPoint, std::string& dst)
{
	size_t	pos;

	while (pos != std::string::npos)
	{
		pos = listNames.find_first_of(" \t");
		if (pos != std::string::npos)
		{
			dst = path_file(endPoint, listNames.substr(0, pos));
			if (open_file_status(dst))
				return (true);
			listNames = listNames.substr((pos + 1));
		}
	}
	if (!open_file_status(path_file(endPoint, listNames)))
		return (false);
	dst = path_file(endPoint, listNames);
	return (true);
}

bool	Server::generete_path_to_response( std::string& dst )
{
	std::string		listNames;
	std::string		endPoint;

	listNames = server()->get_index();
	endPoint = _parser_request->get_endPoint();
	if (listNames.empty() || endPoint.empty())
		return ("");
	return (get_path(listNames, endPoint, dst));
}

