/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readConfigurationFile.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:46:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	isUsefuLine(std::string line)
{
	if (line.length() == 0)
		return false;
	if (line[0] == '#' || line[0] == '\n')
		return false;
	return true;
}

bool	Parser_configuration::readConfigurationFile( void )
{
	std::ifstream	file(_filename.c_str());
	std::string		line;

	std::cout << "_filename: " << _filename.c_str() << std::endl;
	write_debug("Opening/Reading file of confinguration...");
	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
	{
		if (isUsefuLine(line))
			_file.push_back(line);
	}
	file.close();
	return (true);
}
