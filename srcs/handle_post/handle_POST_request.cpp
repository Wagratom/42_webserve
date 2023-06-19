/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:52:04 by wwallas-         ###   ########.fr       */
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

static bool	readRequestBody(aux_upload& data)
{
	while (data.body_length < data.content_length)
	{
		data.bytes_read = recv(data.fd, data.buffer, 1024, 0);
		if (data.bytes_read == -1)
			return (write_error("Error reading body request"));
		data.buffer[data.bytes_read] = '\0';
		data.body_length += data.bytes_read;
		data.request += data.buffer;
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
	size_t				endOfHeaderPos =  request.find(endOfHeader);

	if (endOfHeaderPos == std::string::npos)
		return write_error("Error parsing body request: end of header not found");
	request = request.substr(endOfHeaderPos + 4);
	return true;
}

static void	removeDelimiter(std::string& boby)
{
	size_t	pos = boby.find("------WebKitFormBoundary");

	if (pos == std::string::npos)
		return ;
	boby = boby.substr(0, pos);
}

static bool saveFileInServer(const std::string& content, const std::string& filename)
{
	std::string		path = "./upload/" + filename;
	std::ofstream	file(path.c_str(), std::ios::binary);

	if (!file.is_open())
		return false;
	file.write(content.data(), content.size());
	file.close();
	return true;
}

bool	Server::handle_POST_requesition()
{
	// TODO: check if the body is bigger than client_max_body_size
	aux_upload	data;

	data.request = _parser_request->get_request();
	data.body_length = data.request.length();
	data.fd = _client_fd;
	data.content_length = std::strtol(_parser_request->get_envsMap("CONTENT_LENGTH").c_str(), NULL, 10);

	if (_parser_request->get_envsMap("CONTENT_TYPE").find("multipart/form-data"))
		return (sendErrorToClient("./error_pages/400_bad_request.html", &create_header_400));
	if (processFileUpload(data) == false)
		return responseServer("500");
	if (saveFileInServer(data.request, data.filename) == false)
		return responseServer("500");
	return responseServer("200");
}

bool	Server::processFileUpload(aux_upload& data)
{
	std::cout << "processFileUpload" << std::endl;
	if (readRequestBody(data) == false)
		return (false);
	std::cout << "readRequestBody" << data.request << std::endl;
	if (getFileNameBody(data.request, data.filename) == false)
		return (false);
	if (avenceToContentBody(data.request) == false)
		return (false);
	removeDelimiter(data.request);
	return (true);
}

