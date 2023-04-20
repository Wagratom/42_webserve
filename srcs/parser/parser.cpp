/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 21:05:37 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	save_valid_line(std::string line, std::string& aux)
{
	
	if (line.length() == 0)
		return ;
	return (true);
}

bool	Parser_configuration::read_file(char* filename)
{
	std::ifstream	file(filename);
	std::string		line;

	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
	{
		if (line[0] == '#' || line[0] == '\n')
			continue ;
		if (line[])
		ft_lstadd_back(&(this->file), ft_lstnew(line));
	}
	file.close();
	return (true);
}

bool	Parser_configuration::handle_line(std::string line)
{
	size_t	i = 0;
	int		end = 0;

	line = line.substr(line.find_first_not_of(" \t"));
	while (dictionary[i].f)
	{
		if (line.compare(0, dictionary[i].key.size(), dictionary[i].key) == 0)
			return ((this->*dictionary[i].f)(line));
		i++;
	}
	if (line[0] == '}' && line[1] == '\0' && end++ == 0)
		return (true);
	std::cout << "Error: Invalid key: " << line << std::endl;
	return (false);
}

bool	Parser_configuration::parser_server( void )
{
	if (get_server(this->file->line) == false)
		return (false);
	while (this->file->next != NULL)
	{
		this->file = this->file->next;
		if (handle_line(this->file->line) == false)
			return (false);
	}
	return (true);
}

bool	Parser_configuration::parser(char* filename)
{
	if (read_file(filename) == false)
		return (false);
	if (parser_server() == false)
		return (false);
	std::cout << "Port: " << this->server.port << std::endl;
	std::cout << "Server name: " << this->server.server_name << std::endl;
	std::cout << "Client max body size: " << this->server.client_max_body_size << std::endl;
	std::cout << "Error page: " << this->server.error_page << std::endl;
	return (true);
}

