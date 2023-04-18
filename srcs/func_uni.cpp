/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_uni.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:43:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/17 20:49:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	write_error(std::string msg)
{
	std::cout << "\033[1;31mError: " << msg << std::endl;
	std::cout << "\033[1;37m" << std::endl;
	return (false);
}

bool	get_aux(std::string& aux, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	aux = std::string(line);
	return (!aux.empty());
}

bool	valid_word(std::string& line, std::string word)
{
	if (line.compare(0, word.length(), word) != 0)
		return (write_error("Invalid word: not " + word));
	if (line[word.length()] != ' ' && line[word.length()] != '\t')
		return (write_error("Invalid word: no space after " + word));
	return (true);
}
