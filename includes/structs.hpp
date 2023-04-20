/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 12:07:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class Parser_configuration;

/*############################################################################*/
/*                               File Lines                                   */
/*############################################################################*/

typedef struct s_lst_file
{
	std::string			line;
	struct s_lst_file	*next;

}	list_file;

/*############################################################################*/
/*                            Dictionary Parser                               */
/*############################################################################*/

typedef struct s_dictionary_parser
{
	std::string			key;
	bool				(Parser_configuration::*f)(std::string&);

}	t_dictionary_parser;

/*############################################################################*/
/*                           Configurations server                            */
/*############################################################################*/

typedef struct s_server
{
	int				port;
	std::string		server_name;
	std::string		client_max_body_size;
	std::string		error_page;
	std::string		index;
	std::string		root;

} t_server;

/*############################################################################*/
/*                           Configurations location                          */
/*############################################################################*/

typedef struct s_location
{
	std::string		location;
	std::string		root;
	std::string		index;
	std::string		autoindex;
	std::string		cgi;
	std::string		cgi_path;
	std::string		error_page;
	std::string		client_max_body_size;

} t_location;

