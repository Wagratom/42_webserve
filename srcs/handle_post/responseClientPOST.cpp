/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientPOST.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/02 14:42:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	TypeIsFile(std::string content_type)
{
	if (content_type.find("multipart/form-data") == std::string::npos)
		return (write_error("Error: Content-Type is not multipart/form-data"));
	return (true);
}

static bool	saveFileInServer(std::vector<char> content, const std::string& filename)
{
	std::string		path = "./uploads/" + filename;
	std::ofstream file(path.c_str(), std::ios::binary);

	if (!file)
		return (write_error(strerror(errno)));
	file.write(content.data(), content.size());
	file.close();
	if (!file)
		return (write_error(strerror(errno)));
	return true;
}

static bool	skipToContentBody(std::string& request, std::vector<char>& requestChar)
{
	size_t	endOfHeaderPos =  request.find("\r\n\r\n");

	if (endOfHeaderPos == std::string::npos)
		return write_error("Error parsing body request: end of header not found");
	size_t	offset = endOfHeaderPos + 4;
	requestChar.erase(requestChar.begin(), requestChar.begin() + offset);
	request = request.substr(offset);
	return true;
}

bool	readRequestBody(aux_upload& data, std::vector<char>& requestChar)
{
	std::string			existingData	= data.resquestString;
	size_t				existingSize	= existingData.size();
	size_t				remainingSize	= data.contentLength - existingSize;

	std::copy(existingData.begin(), existingData.end(), requestChar.begin());
	int bytesRead = recv(data.fd, requestChar.data() + existingSize, remainingSize, 0);
	if (bytesRead == -1)
		return write_error("Error reading body request");
	data.resquestString = std::string(requestChar.begin(), requestChar.end());
	return true;
}

static void	removeDelimiterBody(std::string& body, std::vector<char>& requestChar)
{
	size_t	pos = body.find("------WebKitFormBoundary");

	if (pos == std::string::npos)
		return ;
	body.erase(pos);
	requestChar.erase(requestChar.begin() + pos, requestChar.end());
}

bool	Server::responseClientPOST(aux_upload& data)
{
	std::vector<char>	requestChar(data.contentLength);

	std::cout << "responseClientPOST" << std::endl;
	if (TypeIsFile(_parserRequest->get_envsMap("CONTENT_TYPE")) == false)
		return (responseClientError(ERROR415, getErrorPageMapServer("415"))); // verificar como vai ficar depois
	if (readRequestBody(data, requestChar) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	if (extractFileNameFromBody(data) == false)
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (skipToContentBody(data.resquestString, requestChar) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	removeDelimiterBody(data.resquestString, requestChar);
	if (saveFileInServer(requestChar, data.filename) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return responseServer("200");
}
