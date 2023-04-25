/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/24 14:07:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	Parser_configuration::save_valid_line(std::string line)
{

	if (line.length() == 0)
		return ;
	if (line[0] == '#' || line[0] == '\n')
		return ;
	ft_lstadd_back(&(this->file), ft_lstnew(line));
}

bool	Parser_configuration::read_file(char* filename)
{
	std::ifstream	file(filename);
	std::string		line;

	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
		save_valid_line(line);
	file.close();
	return (true);
}

bool	is_location(std::string& line)
{
	if (line.find("location") != std::string::npos)
		return (true);
	return (false);
}

bool	Parser_configuration::parser(char* filename)
{
	if (read_file(filename) == false)
		return (false);
	if (check_server(this->file->line) == false)
		return (false);
	while (this->file->next != NULL)
	{
		this->file = this->file->next;
		if (is_location(this->file->line))
		{
			if (parser_location(this->file->line) == false)
				return (false);
		}
		else
		{
			if (handle_server(this->file->line) == false)
				return (false);
		}
	}
	std::cout << std::endl;
	std::cout << "Port: " << this->server.port << std::endl;
	std::cout << "Server name: " << this->server.server_name << std::endl;
	std::cout << "Client max body size: " << this->server.client_max_body_size << std::endl;
	std::cout << "Error page: " << this->server.error_page << std::endl;
	std::cout << "Index: " << this->server.index << std::endl;
	std::cout << "Root: " << this->server.root << std::endl;
	return (true);
}

