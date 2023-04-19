/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_uni.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:43:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 09:38:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	write_error(std::string msg)
{
	std::cout << "\033[1;31mError: " << msg << std::endl;
	std::cout << "\033[1;37m" << std::endl;
	return (false);
}

bool	get_aux_valid(std::string& aux, char *line)
{
	size_t	end;

	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (write_error("Invalid line: empty line"));
	aux = std::string(line);
	end = aux.length() - 1;
	if (aux[end] != ';')
		return (write_error("Invalid line: no ';' at the end"));
	aux.erase(end);
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
