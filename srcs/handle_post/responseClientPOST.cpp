/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientPOST.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/27 09:45:14 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	TypeIsFile(std::string content_type)
{
	if (content_type.find("multipart/form-data") == std::string::npos)
		return (write_error("Error: Content-Type is not multipart/form-data"));
	return (true);
}

static bool	saveFileInServer(const std::string& content, const std::string& filename)
{
	std::string		path = "./upload/" + filename;
	std::ofstream	file(path.c_str(), std::ios::binary);

	if (!file.is_open())
		return (write_error("Error opening file to save in server"));
	file.write(content.data(), content.size());
	file.close();
	return true;
}

static bool	readRequestBody(aux_upload& data)
{
	while (data.bodySize < data.contentLength)
	{
		data.bytes_read = recv(data.fd, data.buffer, 4096, 0);
		if (data.bytes_read == -1)
			return (write_error("Error reading body request"));
		data.buffer[data.bytes_read] = '\0';
		data.bodySize += data.bytes_read;
		data.request += data.buffer;
	}
	return (true);
}

static void	removeDelimiterRequest(std::string& body)
{
	size_t	pos = body.find("------WebKitFormBoundary");

	if (pos == std::string::npos)
		return ;
	body.erase(pos);
}

bool	Server::responseClientPOST(aux_upload& data)
{
	std::cout << "responseClientPOST" << std::endl;
	if (TypeIsFile(_parserRequest->get_envsMap("CONTENT_TYPE")) == false)
		return (responseClientError(ERROR415, getErrorPageMapServer("415"))); // verificar como vai ficar depois
	if (readRequestBody(data) == false)
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (processFileUpload(data) == false)
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	removeDelimiterRequest(data.request);
	if (saveFileInServer(data.request, data.filename) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return responseServer("200");
}
