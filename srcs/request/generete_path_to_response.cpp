/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generete_path_to_response.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:04:00 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 20:44:47 by wwallas-         ###   ########.fr       */
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

static std::string	path_file( std::string root, std::string filename )
{
	if (root[root.size() - 1] == '/')
		return (std::string(root + filename));
	return (std::string("." + root + "/" + filename));
}

bool	get_path(std::string listNames, std::string root, std::string& dst)
{
	size_t	pos;

	while (pos != std::string::npos)
	{
		pos = listNames.find_first_of(" \t");
		if (pos != std::string::npos)
		{
			dst = path_file(root, listNames.substr(0, pos));
			if (open_file_status(dst))
				return (true);
			listNames = listNames.substr((pos + 1));
		}
	}
	if (!open_file_status(path_file(root, listNames)))
		return (false);
	dst = path_file(root, listNames);
	return (true);
}

bool	Server::generete_path_to_response( std::string& dst )
{
	std::string		listNames;
	std::string		root;

	dst.clear();
	listNames = server()->get_index();
	root = server()->get_root();
	std::cout << "root: " << root << std::endl;
	if (listNames.empty() || root.empty())
		return ("");
	return (get_path(listNames, root, dst));
}

