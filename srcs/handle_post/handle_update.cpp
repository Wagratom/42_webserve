/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_update.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/13 17:20:36 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

struct aux_upload{
	std::string	request;
	std::string	filename;
	int			body_length;
	char		buffer[1024];
	int			bytes_read;
	int			fd;
	int			content_length;
};

static bool	readRequestBody_aux(aux_upload& data)
{
	data.bytes_read = recv(data.fd, data.buffer, 1024, 0);
	if (data.bytes_read == -1)
		return (write_error("Error reading body request"));
	data.buffer[data.bytes_read] = '\0';
	data.body_length += data.bytes_read;
	data.request += data.buffer;
	return (true);
}

static bool	readRequestBody(aux_upload& data)
{
	while (true)
	{
		if (data.body_length >= data.content_length)
			break ;
		if (readRequestBody_aux(data) == false)
			return (false);
	}
	return (true);
}

static void	removingSpacesFilename(std::string& filename)
{
	std::string::iterator it;

	for (it = filename.begin(); it != filename.end(); ++it)
	{
		char& c = *it;
		if (c == ' ')
			c = '_';
	}
}

static bool getFileNameBody(const std::string& body, std::string& filename)
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
	removingSpacesFilename(filename);
	return true;
}

static bool	avenceToContentBody(std::string& request)
{
	const std::string	endOfHeader = "\r\n\r\n";
	size_t				endOfHeaderPos;

	endOfHeaderPos = request.find(endOfHeader);
	if (endOfHeaderPos == std::string::npos)
		return write_error("Error parsing body request: end of header not found");
	request = request.substr(endOfHeaderPos + 4);
	return true;
}

static bool saveFileInServer(const std::string& content, const std::string& filename)
{
	std::string path = "./upload/" + filename;
	std::ofstream file(path.c_str(), std::ios::binary);

	std::cout << "path: " << path << std::endl;
	std::cout << "content: " << content << std::endl;
	if (!file.is_open())
		return false;
	file.write(content.data(), content.size());
	file.close();
	return true;
}

static void	removeDelimiter(std::string& boby)
{
	size_t pos = boby.find("------WebKitFormBoundary");
	if (pos == std::string::npos)
		return ;
	boby = boby.substr(0, pos);
}


bool	Server::handle_update()
{
	// TODO: check if the body is bigger than client_max_body_size
	aux_upload	data;

	data.request = _parser_request->get_request();
	data.body_length = data.request.length();
	data.fd = _client_fd;
	data.content_length = std::strtol(_parser_request->get_envsMap("CONTENT_LENGTH").c_str(), NULL, 10);
	if (processFileUpload(data) == false)
		return response_server("500");
	if (saveFileInServer(data.request, data.filename) == false)
		return response_server("500");
	return response_server("200");
}

bool	Server::processFileUpload(aux_upload& data)
{
	if (readRequestBody(data) == false)
		return (false);
	if (getFileNameBody(data.request, data.filename) == false)
		return (false);
	if (avenceToContentBody(data.request) == false)
		return (false);
	removeDelimiter(data.request);
	return (true);
}

