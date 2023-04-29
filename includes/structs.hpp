/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 09:23:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class	Parser_configuration;
class	location_configuration;
class	aux_configuration;
class	server_configuration;
class	Parser_request;


/*############################################################################*/
/*                               File Lines                                   */
/*############################################################################*/

typedef struct s_lst_file
{
	std::string			line;
	struct s_lst_file*	next;

}	list_file;

/*############################################################################*/
/*                           Universal Dictionary                             */
/*############################################################################*/

typedef struct s_universal_dictionary
{
	std::string		key;
	int				length;
	bool			(Parser_configuration::*f)(std::string&, aux_configuration*);

}	t_universal_dictionary;

/*############################################################################*/
/*                           Dictionary Server                                */
/*############################################################################*/

typedef struct s_server_dictionary
{
	std::string		key;
	int				length;
	bool			(Parser_configuration::*f)(std::string&);

} t_server_dictionary;

/*############################################################################*/
/*                           location Gninx                                   */
/*############################################################################*/

typedef struct s_location_settings
{
	std::string					locationName;
	location_configuration*		configuration;
	struct s_location_settings*			next;

} t_location_settings;

