/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 10:07:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

class Parser_configuration;

typedef struct s_dictionary_parser
{
	std::string			key;
	bool				(Parser_configuration::*f)(char*, std::string&);

}	t_dictionary_parser;

typedef struct s_server
{
	int					port;
	std::string			server_name;
	std::string			client_max_body_size;
	std::string			error_page;
}						t_server;

class	Parser_configuration
{
	public:
		Parser_configuration( void );
		~Parser_configuration( void );

		t_dictionary_parser*	create_dictionary_parser( void );
		bool					get_port(char*	line, int& port);
		bool					get_server_name(char* line, std::string& server_name);
		bool					get_client_max_body_size(char* line, std::string& client_max_body_size);
		bool					get_error_page(char* line, std::string& error_page);

	private:
		t_dictionary_parser*	dictionary;
};

bool	write_error(std::string msg);
bool	valid_word(std::string& listen, std::string word);
bool	get_aux_valid(std::string& aux, char *line);
bool	equal_or_err_i(int a, int b, int line);
bool	different_or_err_i(int a, int b, int line);
bool	equal_or_err_s(std::string a, std::string b, int line);
bool	different_or_err_s(std::string a, std::string b, int line);
bool	equal_or_err_b(bool a, bool b, int line);
bool	different_or_err_b(bool a, bool b, int line);
