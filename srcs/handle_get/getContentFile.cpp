/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseLocation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	getContentAllFile(auxReadFiles& dst)
{
	std::ifstream	file(dst.path.c_str(), std::ios::ate);
	std::streamsize	size;

	std::cout << "getContentAllFile" << std::endl;
	std::cout << "dst.path: " << dst.path << std::endl;
	if (!file.is_open())
		return (perror("Error: getContentAllFile: file.is_open()"), false);
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	dst.content.resize(size);
	if (!file.read(&dst.content[0], size))
		return (false);
	return (true);
}

bool	getContentFile(auxReadFiles& dst)
{
	if (dst.path.find(".php") != std::string::npos)
		return (getContentFilePHP(dst));
	if (dst.path.find(".") != std::string::npos)
		return (getContentAllFile(dst));
	return (false);
}
