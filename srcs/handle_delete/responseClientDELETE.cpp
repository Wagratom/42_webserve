/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientDELETE.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 18:19:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

static bool	callExecuteCgi(ChildProcessData& tools_chuild, std::string listFiles)
{
	char*	argv[3];
	char	*envp[2];

	std::cout <<listFiles << std::endl;
	envp[0] = (char*)listFiles.c_str();
	envp[1] = (char*)NULL;

	argv[0] = (char *)"/usr/bin/php-cgi";
	argv[1] = (char *)"./root/script.html";
	argv[2] = NULL;

	dup2(tools_chuild.fd[1], STDOUT_FILENO);
	close(tools_chuild.fd[0]);
	close(tools_chuild.fd[1]);
	executeCGI(argv, envp);
	return (true);
}

static bool	execute_cgi_listFiles(ChildProcessData& tools_chuild, std::string listFiles)
{
	if (executeFork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
		callExecuteCgi(tools_chuild, listFiles);
	waitpid(tools_chuild.pid, NULL, 0);
	close(tools_chuild.fd[1]);
	return (true);
}

static bool	join_response_cgi(ChildProcessData& tools_chuild, std::string& response)
{
	char		buffer[1024];
	int			bytes_read;

	while (true)
	{
		bytes_read = read(tools_chuild.fd[0], buffer, 1024);
		if (bytes_read == -1)
			return (write_error("Error: handle_delete: read"));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		response += buffer;
	}
	close(tools_chuild.fd[0]);
	return (true);
}

static bool	create_response_to_client(std::string listFiles, std::string& response)
{
	ChildProcessData	tools_chuild;

	response.clear();
	response = "HTTP/1.1 200 OK\r\n";
	if (execute_cgi_listFiles(tools_chuild, listFiles) == false)
		return (false);
	return (join_response_cgi(tools_chuild, response));
}

static void	add_prefix_listFiles(std::string& listFiles)
{
	listFiles = "listFiles=" + listFiles;
}


static bool	open_director_update(DIR*& dir)
{
	const char*		directory = "./upload";

	dir = opendir(directory);
	if (dir == NULL)
		return (false);
	return (true);
}

static bool	create_listfILES(DIR*& dir, std::string& listFiles)
{
	struct dirent	*ent;

	while ((ent = readdir(dir)) != NULL)
	{
		if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
			continue ;
		listFiles += ent->d_name;
		listFiles += "\n";
	}
	return (true);
}

static bool	getListFiles(std::string& listFiles)
{
	DIR	*dir;

	if (open_director_update(dir) == false)
		return (write_error("Error: handle_delete: opening directory"));
	return (create_listfILES(dir, listFiles));
}

bool	Server::responseClientDELETE()
{
	std::string	response;
	std::string listFiles;

	if (getListFiles(listFiles) == false)
		return (false);
	add_prefix_listFiles(listFiles);
	if (create_response_to_client(listFiles, response) == false)
		return (false);
	return (sendResponseClient(response));
}
