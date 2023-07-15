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

	write_debug("getContentAllFile");
	write_debug_prefix("File: ", dst.path);
	if (!file.is_open())
		return writeStreerrorPrefix("Error: getContentAllFile: ");
	dst.contentLength = file.tellg();
	file.seekg(0, std::ios::beg);
	dst.content.resize(dst.contentLength);
	if (!file.read(&dst.content[0], dst.contentLength))
		return (file.close(), false);
	generateDynamicHeader(dst, "200");
	dst.content = dst.header + dst.content;
	file.close();
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
