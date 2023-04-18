/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/17 21:33:46 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

bool	write_error(std::string msg);
bool	valid_word(std::string& listen, std::string word);
bool	get_aux(std::string& aux, char *line);

bool	get_port(char*	line, int& port);
bool	get_server_name(char* line, std::string& server_name);

bool	equal_or_err_i(int a, int b, int line);
bool	different_or_err_i(int a, int b, int line);
bool	equal_or_err_s(std::string a, std::string b, int line);
bool	different_or_err_s(std::string a, std::string b, int line);
bool	equal_or_err_b(bool a, bool b, int line);
bool	different_or_err_b(bool a, bool b, int line);
