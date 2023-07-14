/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_except.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:15:41 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 11:17:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	extractLimitExecpttPrefix(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 12);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no limit_except"));
	line = line.substr(pos);
	return (true);
}

static bool	create_MethodsPassed(std::string& line, std::vector<std::string>& words)
{
	std::istringstream iss(line);

	std::string word;
	while (iss >> word) {
		words.push_back(word);
	}
	if (words.size() == 0)
		return (write_error("Error: Invalid line root, no methods"));
	return (true);
}

static bool	myFind(std::string& word, std::vector<std::string>& allowed_methods)
{
	for (size_t i = 0; i < allowed_methods.size(); i++) {
		if (word == allowed_methods[i])
			return (true);
	}
	return (false);
}

static bool	validMethodsPassed(std::vector<std::string>& words, std::vector<std::string>& allowed_methods)
{
	for (size_t i = 0; i < words.size(); i++) {
		if (myFind(words[i], allowed_methods) == false)
			return (write_error("Error: Invalid line root, invalid method"));
	}
	return (true);
}

static bool	validate_limit_except(std::string& line, std::vector<std::string>& words)
{
	std::vector<std::string>	allowed_methods;

	allowed_methods.push_back("GET");
	allowed_methods.push_back("POST");
	allowed_methods.push_back("DELETE");
	if (create_MethodsPassed(line, words) == false)
		return (false);
	if (validMethodsPassed(words, allowed_methods) == false)
		return (false);
	return (true);
}

static bool	save_data(std::vector<std::string>& words, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);

	if (location == NULL)
		return (write_error("Error in cast configuration in get_root"));
	location->set_limit_except(words);
	return (true);
}

bool	Parser_configuration::get_limit_except(std::string& line, aux_configuration* dst)
{
	std::vector<std::string>	words;

	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line root, not ';'"));
	if (startsWithWord(line, "limit_except") == false)
		return (false);
	if (extractLimitExecpttPrefix(line) == false)
		return (false);
	if (validate_limit_except(line, words) == false)
		return (false);
	if (save_data(words, dst) == false)
		return (false);
	return (true);
}
