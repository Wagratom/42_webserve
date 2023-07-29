/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/29 10:20:50 by wwallas-         ###   ########.fr       */
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
# include <vector>

class	Parser_configuration;
class	Location_configuration;
class	aux_configuration;
class	Server_configuration;
class	Parser_request;

/*############################################################################*/
/*                           location Gninx                                   */
/*############################################################################*/

typedef struct s_location
{
	std::string					endPoint;
	Location_configuration*		configuration;
	struct s_location*			next;

} t_location;

typedef struct s_aux_read_file
{
	std::string			header;
	std::string			content;
	std::string			path;
	int					contentLength;
	bool				notPermmision;
} auxReadFiles;

typedef struct s_ChildProcessInfo {
	int		fd[2];
	pid_t	pid;
	int		status;

} ChildProcessData;

void	write_debug_number(std::string message, int number);
void	write_debug_prefix(std::string prefix, std::string message);
bool	writeStreerrorPrefix( std::string prefix );
bool	write_debug(std::string message);
