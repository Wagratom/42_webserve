/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_uni.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:43:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:28:29 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	write_error(std::string msg)
{
	std::cout << "\033[1;31mError: " << msg << std::endl;
	std::cout << "\033[1;37m" << std::endl;
	return (false);
}

bool	has_semicolon_at_end(std::string& line)
{
	size_t	end = line.length() - 1;

	if (end == 0)
		return (false);
	if (line[end] != ';')
		return (false);
	if (line[end -1] == ' ' || line[end - 1] == '\t')
		return (false);
	line.erase(end);
	return (true);
}

bool	valid_word(std::string& line, std::string word)
{
	if (line.compare(0, word.length(), word) != 0)
		return (write_error("Invalid word: not " + word));
	if (line[word.length()] != ' ' && line[word.length()] != '\t')
		return (write_error("Invalid word: no space after " + word));
	return (true);
}
