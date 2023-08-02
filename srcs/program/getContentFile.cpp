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

static bool	checkAcess(std::string path, auxReadFiles& dst)
{
	if (access(path.c_str(), R_OK) == 0)
		return (true);
	dst.notPermmision = true;
	return (writeStreerrorPrefix("Error: getContentFilePHP: "));
}

static bool	getContentAllFile(auxReadFiles& dst, std::string statusHeader)
{
	write_debug_prefix("getContentAllFile: ", dst.path);
	if (checkAcess(dst.path, dst) == false)
		return (false);
	try {
		std::ifstream	file(dst.path.c_str(), std::ios::ate);

		if (!file.is_open())
			return writeStreerrorPrefix("Error: getContentAllFile: ");
		dst.contentLength = file.tellg();
		file.seekg(0, std::ios::beg);
		dst.content.resize(dst.contentLength);
		if (!file.read(&dst.content[0], dst.contentLength))
			return (file.close(), false);
		generateHeaderDynamicStatus(dst, statusHeader);
		dst.content = dst.header + dst.content;
		file.close();
		return (true);
	}
	catch (std::exception& e) {
		write_debug("getContentAllFile: catch");
		return (write_error_prefixS("Error: ", e.what()));
	}
}

bool	Server::getContentFile(auxReadFiles& dst, const std::map<std::string, std::string>& cgi, std::string statusHeader)
{
	try {
		std::string	extension = dst.path.substr(dst.path.find_last_of("."));
		if (cgi.find(extension) != cgi.end())
			return (getContentFilePHP(dst));
		return (getContentAllFile(dst, statusHeader));
	}
	catch (std::exception& e) {
		return write_error_prefixS("getContentFile: catch", e.what());
	}
}

bool	Server::responseClient(auxReadFiles& tmp, const std::map<std::string, std::string>& cgi, std::string statusHeader)
{
	write_debug_prefix("responseClient: file: ", tmp.path);
	if (getContentFile(tmp, cgi, statusHeader) == false)
	{
		if (tmp.notPermmision == true)
			return (responseClientError(ERROR403, _response->root, getErrorPageMap(_response->errorPage, "403")));
		return (responseClientError(ERROR500, _response->root, getErrorPageMap(_response->errorPage, "500")));
	}
	if (_response->hasProcess == true)
		return (true);
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, _response->root, getErrorPageMap(_response->errorPage, "500")));
	return true;
}
