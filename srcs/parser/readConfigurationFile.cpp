/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readConfigurationFile.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 21:02:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	Parser_configuration::readConfigurationFile( void )
{
	std::ifstream	file(_filename.c_str());
	std::string		line;

	write_debug_prefix(AZUL, "Opening/Reading file of confinguration...");
	write_debug_prefix("File name: ", _filename.c_str());
	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
	{
		if (isLineEmpty(line) == false)
			_file.push_back(line);
	}
	file.close();
	return (true);
}
