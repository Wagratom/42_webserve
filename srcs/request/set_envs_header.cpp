/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs_header.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/03 11:50:21 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

typedef	std::map<std::string, std::string>::iterator iterator_map;
typedef	std::map<std::string, iterator_map>::iterator iterator_head;

/*############################################################################*/
/*                       functions to get the value                           */
/*############################################################################*/

static bool	request_host(std::string& host, std::map<std::string, std::string>& data_request)
{
	size_t pos;

	pos = host.find(":");
	if (pos == std::string::npos)
		return (write_error("400 Bad Request: Host"));
	host = host.substr(pos + 2);
	pos = host.find(":");
	if (pos == std::string::npos)
		return (write_error("400 Bad Request: Host"));
	data_request.find("HTTP_HOST")->second = host;
	data_request.find("SERVER_PORT")->second = host.substr(pos  + 1);
	return (true);
}

static std::string	get_data_pos_double_point(std::string& line)
{
	size_t	pos;

	pos = line.find(":");
	if (pos == std::string::npos)
		return ("");
	return (line.substr(pos + 2));
}

/*############################################################################*/
/*                          auxiliary functions                               */
/*############################################################################*/

static void	fill_maps(std::map<std::string, std::string>& envs, std::map<std::string, iterator_map>& key_value)
{
	envs["SERVER_PORT"] = "";
	envs["HTTP_HOST"] = "";
	envs["HTTP_USER_AGENT"] = "";
	envs["HTTP_ACCEPT"] = "";
	envs["HTTP_ACCEPT_ENCODING"] = "";
	envs["HTTP_ACCEPT_LANGUAGE"] = "";
	envs["HTTP_COOKIE"] = "";
	envs["CONTENT_LENGTH"] = "";
	envs["CONTENT_TYPE"]= "";
	envs["HTTP_CONNECTION"]= "";

	key_value["Connection:"] = envs.find("HTTP_CONNECTION");
	key_value["User-Agent:"] = envs.find("HTTP_USER_AGENT");
	key_value["Accept:"] = envs.find("HTTP_ACCEPT");
	key_value["Accept-Encoding:"] = envs.find("HTTP_ACCEPT_ENCODING");
	key_value["Accept-Language:"] = envs.find("HTTP_ACCEPT_LANGUAGE");
	key_value["Cookie:"] = envs.find("HTTP_COOKIE");
	key_value["Content-Length:"] = envs.find("CONTENT_LENGTH");
	key_value["Content-Type:"] = envs.find("CONTENT_TYPE");
}

static bool	get_line_request(std::string& dst, std::string& request)
{
	size_t	pos;

	if (!request.length())
		return (false);
	else
	{
		pos = request.find("\r\n");
		if (pos == std::string::npos)
			return (false);
		dst = request.substr(0, pos);
		request = request.substr(pos + 2);
	}
	if (dst.empty() || dst == "\r\n\r\n")
		return (false);
	return (true);
}

/*############################################################################*/
/*                              SET ENVS HEADER                               */
/*############################################################################*/

static bool	handle_line(std::string line, std::map<std::string, iterator_map>& key_value);

void Parser_request::set_envs(std::map<std::string, std::string>& envs)
{
	iterator_map	it = envs.begin();

	while (it != envs.end())
	{
		if (it->second.empty())
			it->second = "null";
		setenv(it->first.c_str(), it->second.c_str(), 1);
		it++;
	}
}

bool Parser_request::set_envs_header(void)
{
	std::map<std::string, std::string> envs;
	std::map<std::string, iterator_map> key_value;
	std::string line;

	fill_maps(envs, key_value);
	while (get_line_request(line, _request))
	{
		if (line.compare(0, 4, "Host") == 0)
		{
			if (!request_host(line, envs))
				return (false);
		}
		else
			handle_line(line, key_value);
	}
	set_envs(envs);
	std::cout << "Dados Extraidos: " << std::endl;
	return (true);
}

static bool handle_line(std::string line, std::map<std::string, iterator_map>& key_value)
{
	std::string tmp;
	iterator_head it;

	it = key_value.begin();
	while (it != key_value.end())
	{
		if (line.compare(0, it->first.length(), it->first) == 0)
		{
			tmp = get_data_pos_double_point(line);
			if (tmp.empty())
				return (write_error("400 Bad Request: Header"));
			it->second->second = tmp;
			return (true);
		}
		it++;
	}
	return (false);
}
