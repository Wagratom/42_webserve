/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs_header.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/04 18:57:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


bool	request_host(std::string& host, std::map<std::string, std::string>& data_request)
{
	size_t pos;

	std::cout << "host: " << host << std::endl;
	pos = host.find(":");
	if (pos == std::string::npos)
		return (write_error("400 Bad Request"));
	host = host.substr(pos + 2);
	pos = host.find(":");
	if (pos == std::string::npos)
		return (write_error("400 Bad Request"));
	data_request.find("server_name")->second = host.substr(0, pos);
	data_request.find("server_port")->second = host.substr(pos  + 1);
	return (true);
}

bool	get_data_pos_double_point(std::string& line, std::map<std::string, std::string>& data_request)
{
	size_t	pos = line.find(":");

	if (pos == std::string::npos)
		return (write_error("400 Bad Request"));
	line = line.substr(pos + 2);
	return (true);
}
/*
 std::string request_method = "GET";
    std::string request_uri = "/wagratom";
    std::string http_version = "HTTP/1.1";
    std::string server_name = "localhost";
    std::string server_port = "8080";
    std::string http_host = "localhost:8080";
    std::string http_connection = "keep-alive";
    std::string http_cache_control = "max-age=0";
    std::string http_sec_ch_ua = "\"Chromium\";v=\"112\", \"Microsoft Edge\";v=\"112\", \"Not:A-Brand\";v=\"99\"";
    std::string http_sec_ch_ua_mobile = "?0";
    std::string http_sec_ch_ua_platform = "\"Windows\"";
    std::string http_upgrade_insecure_requests = "1";
    std::string http_user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36 Edg/112.0.1722.39";
    std::string http_accept = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,
    std::string http
*/

static void	fill_map_envs(std::map<std::string, std::string>& data_request)
{
	data_request["server_name"] = "";
	data_request["server_port"] = "";
	data_request["http_host"] = "";
	data_request["http_connection"] = "";
	data_request["http_cache_control"] = "";
	data_request["http_sec_ch_ua"] = "";
	data_request["http_sec_ch_ua_mobile"] = "";
	data_request["http_sec_ch_ua_platform"] = "";
	data_request["http_upgrade_insecure_requests"] = "";
	data_request["http_user_agent"] = "";
	data_request["http_accept"] = ""; 
}

typedef bool (*p_functions)(std::string&, std::map<std::string, std::string>&);

static void	fill_map_functions(std::map<std::string, p_functions>& functions)
{
	functions["Host"] = &request_host;
	functions["Connection"] = NULL;
	functions["Cache-Control:"] = NULL;
	functions["sec-ch-ua"] = NULL;
	functions["sec-ch-ua-mobile:"] = NULL;
	functions["sec-ch-ua-platform:"] = NULL;
	functions["Upgrade-Insecure-Requests:"] = NULL;
	functions["User-Agent:"] = NULL;
	functions["Accept:"] = NULL;
	functions["Accept-Encoding:"] = NULL;
	functions["Accept-Language:"] = NULL;
	functions["Cookie:"] = NULL;
}

bool	get_line_request(std::string& dst, std::string request)
{
	size_t	pos = request.find("\r\n");
	if (pos == std::string::npos)
		return (false);
	dst = request.substr(0, pos);
	return (true);
}


bool Parser_request::set_envs_header(void)
{
	std::map<std::string, std::string> value_envs;
	std::map<std::string, p_functions> functions;
	std::string line;

	fill_map_envs(value_envs);
	fill_map_functions(functions);
	get_line_request(line, _request);
	return (true);
	for (typename std::map<std::string, std::string>::iterator it = value_envs.begin(); it != value_envs.end(); it++)
	{
		std::string chave = it->first;
		std::string valor = it->second;
	}
	return true;
}
