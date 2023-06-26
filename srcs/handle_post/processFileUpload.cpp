/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processFileUpload.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 12:05:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void	replaceSpacesInFilename(std::string& filename)
{
	std::string::iterator it;

	for (it = filename.begin(); it != filename.end(); ++it)
	{
		char& c = *it;
		if (c == ' ')
			c = '_';
	}
}

static bool extractFileNameFromBody(const std::string& body, std::string& filename)
{
	const std::string	filenameTag = "filename=";
	const std::string	lineBreak = "\r\n";
	size_t				filenameStartPos = body.find(filenameTag);
	size_t				filenameEndPos;

	if (filenameStartPos == std::string::npos)
		return write_error("Error parsing body request: filename not found");
	filenameStartPos += filenameTag.length() + 1;
	filenameEndPos = body.find(lineBreak, filenameStartPos);
	if (filenameEndPos == std::string::npos)
		return write_error("Error parsing body request: filename end not found");
	filename = body.substr(filenameStartPos, filenameEndPos - filenameStartPos - 1);
	return true;
}

static bool	skipToContentBody(std::string& request)
{
	size_t	endOfHeaderPos =  request.find("\r\n\r\n");

	if (endOfHeaderPos == std::string::npos)
		return write_error("Error parsing body request: end of header not found");
	request = request.substr(endOfHeaderPos + 4);
	return true;
}

bool	Server::processFileUpload(aux_upload& data)
{
	if (extractFileNameFromBody(data.request, data.filename) == false)
		return (false);
	if (data.filename.empty())
		return write_error("Error extractFileNameFromBody: filename is empty");
	if (skipToContentBody(data.request) == false)
		return (false);
	replaceSpacesInFilename(data.filename);
	return (true);
}
