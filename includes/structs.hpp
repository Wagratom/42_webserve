/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 12:48:10 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class Parser_configuration;

typedef struct s_dictionary_parser
{
	std::string			key;
	bool				(Parser_configuration::*f)(char*, std::string&);

}	t_dictionary_parser;

typedef struct s_lst_file
{
	std::string			line;
	struct s_lst_file	*next;

}	list_file;

typedef struct s_server
{
	int					port;
	std::string			server_name;
	std::string			client_max_body_size;
	std::string			error_page;
}						t_server;
