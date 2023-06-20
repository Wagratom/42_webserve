/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 10:53:53 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <fstream>
# include <cstdlib>
# include <string>
# include <cstdio>
# include <netinet/in.h>
# include <iostream>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <cstring>
# include <map>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sstream>

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
	std::string					locationName; // key
	location_configuration*		configuration;
	struct s_location_settings*			next;

} t_location_settings;

typedef struct s_aux_read_file
{
	std::string			content;
	std::string			path;
	std::streamsize		size;
	std::ostringstream	oss;
	std::string			header;
} auxReadFiles;

struct aux_upload{
	std::string	request;
	std::string	filename;
	int			body_length;
	char		buffer[1024];
	int			bytes_read;
	int			fd;
	int			content_length;
};

void	write_debug_number(std::string message, int number);
void	write_debug_prefix(std::string prefix, std::string message);
bool	write_debug(std::string message);
void	write_type_event_debug(epoll_event& event);
