/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/16 17:50:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

static bool	execute_cgi_in_chuild(ChildProcessInfo& tools_chuild, std::string listFiles)
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
	execute_cgi(argv, envp);
	return (true);
}

static bool	execute_cgi_listFiles(ChildProcessInfo& tools_chuild, std::string listFiles)
{
	if (execute_fork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
		execute_cgi_in_chuild(tools_chuild, listFiles);
	waitpid(tools_chuild.pid, NULL, 0);
	close(tools_chuild.fd[1]);
	return (true);
}

static bool	join_response_cgi(ChildProcessInfo& tools_chuild, std::string& response)
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
	ChildProcessInfo	tools_chuild;

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

bool	Server::response_client(std::string response)
{
	if (send(_client_fd, response.c_str(), response.size(), 0) == -1)
		return (write_error("Error: handle_delete: send"));
	return (true);
}

static bool	delete_file_server(std::string fileName)
{
	std::string	pathFile = "./upload/" + fileName;

	if (std::remove(pathFile.c_str()) != 0)
		return (write_error("Error: handle_delete: Not possible to remove file"));
	return (true);
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

static bool	get_ListFiles(std::string& listFiles)
{
	DIR				*dir;

	if (open_director_update(dir) == false)
		return (write_error("Error: handle_delete: opening directory"));
	return (create_listfILES(dir, listFiles));
}

bool	Server::response_client_with_list_files()
{
	std::string	response;
	std::string listFiles;

	if (get_ListFiles(listFiles) == false)
		return (false);
	add_prefix_listFiles(listFiles);
	if (create_response_to_client(listFiles, response) == false)
		return (false);
	return (response_client(response));
}

bool	Server::handle_DELETE_requesition( void )
{
	if (!_parser_request->get_endPoint()[7])
		return (response_client_with_list_files());
	delete_file_server(std::string(_parser_request->get_endPoint(), 8));
	std::cout << "File deleted" << std::endl;
	return (response_client_with_list_files());
}
