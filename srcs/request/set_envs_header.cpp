/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs_header.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/04 20:32:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

//					iterator mapa
typedef	std::map<std::string, std::string>::iterator iterator_map;
typedef	std::map<std::string, iterator_map>::iterator iterator_head;

//					pointer para funcao
// typedef	bool (*p_functions)(std::string&, iterator_map&);

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
	data_request.find("http_host")->second = host;
	data_request.find("server_name")->second = host.substr(0, pos);
	data_request.find("server_port")->second = host.substr(pos  + 1);
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

static void	fill_maps(std::map<std::string, std::string>& envs, std::map<std::string, iterator_map>& key_value)
{
	envs["server_name"] = "";
	envs["server_port"] = "";
	envs["http_host"] = "";
	envs["http_connection"] = "";
	envs["http_cache_control"] = "";
	envs["http_sec_ch_ua"] = "";
	envs["http_sec_ch_ua_mobile"] = "";
	envs["http_sec_ch_ua_platform"] = "";
	envs["http_upgrade_insecure_requests"] = "";
	envs["http_user_agent"] = "";
	envs["http_accept"] = "";
	envs["http_accept_encoding"] = "";
	envs["http_accept_language"] = "";
	envs["http_cookie"] = "";

	key_value["Connection"] = envs.find("http_connection");
	key_value["Cache-Control:"] = envs.find("http_cache_control");
	key_value["sec-ch-ua"] = envs.find("http_sec_ch_ua");
	key_value["sec-ch-ua-mobile:"] = envs.find("http_sec_ch_ua_mobile");
	key_value["sec-ch-ua-platform:"] = envs.find("http_sec_ch_ua_platform");
	key_value["Upgrade-Insecure-Requests:"] = envs.find("http_upgrade_insecure_requests");
	key_value["User-Agent:"] = envs.find("http_user_agent");
	key_value["Accept:"] = envs.find("http_accept");
	key_value["Accept-Encoding:"] = envs.find("http_accept_encoding");
	key_value["Accept-Language:"] = envs.find("http_accept_language");
	key_value["Cookie:"] = envs.find("http_cookie");
}

static bool	get_line_request(std::string& dst, std::string& request)
{
	size_t	pos;

	if (!request.empty())
	{
		pos = request.find("\r\n");
		if (pos == std::string::npos)
			pos =  request.length();
		dst = request.substr(0, pos);
		request = request.substr(pos + 2);
	}
	else
		return (false);
	return (true);
}

bool Parser_request::set_envs_header(void)
{
	std::map<std::string, std::string> envs;
	std::map<std::string, iterator_map> key_value;
	std::string line;
	std::string tmp;

	fill_maps(envs, key_value);

	std::cout << std::endl;
	while (get_line_request(line, _request))
	{
		if (line.compare(0, 4, "Host") == 0)
		{
			if (!request_host(line, envs))
				return (false);
			continue;
		}
		for (iterator_head it = key_value.begin(); it != key_value.end(); it++)
		{
			if (line.compare(0, it->first.length(), it->first) == 0)
			{
				tmp = get_data_pos_double_point(line);
				if (tmp.empty())
					return (write_error("400 Bad Request: Header"));
				std::cout << "tmp: " << tmp << std::endl << std::endl;
				it->second->second = tmp;
				break ;
			}
		}
	}

	for (iterator_map it = envs.begin(); it != envs.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}

	return true;
}


