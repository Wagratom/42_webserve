/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/15 18:37:26 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

bool	Server::handle_POST_requesition( void )
{
	if (_parser_request->get_endPoint() == "/upload")
		return (handle_update());
	if (_parser_request->get_endPoint().compare(0, 7, "/delete") == 0)
		return (handle_delete());
	return (true);
}

static bool	get_ListFiles(std::string& listFiles)
{
	DIR				*dir;
	struct dirent	*ent;
	const char*		directory = "./upload";

	listFiles.clear();
	if ((dir = opendir(directory)) == NULL)
		return (write_error("Error: handle_delete: opening directory"));
	while ((ent = readdir(dir)) != NULL)
	{
		if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..") {
			listFiles += ent->d_name;
			listFiles += "\n";
		}
	}
	return (true);
}

static bool	execute_cgi_listFiles(ChildProcessInfo& tools_chuild, std::string listFiles)
{
	if (execute_fork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
	{
		char*	argv[3];
		char	*envp[2];

		envp[0] = (char*)listFiles.c_str();
		envp[1] = (char*)NULL;

		argv[0] = (char *)"/usr/bin/php-cgi";
		argv[1] = (char *)"./root/script.html";
		argv[2] = NULL;

		dup2(tools_chuild.fd[1], STDOUT_FILENO);
		close(tools_chuild.fd[0]);
		close(tools_chuild.fd[1]);
		execute_cgi(argv, envp);
	}
	waitpid(tools_chuild.pid, NULL, 0);
	close(tools_chuild.fd[1]);
	return (true);
}

static bool	read_response_cgi(ChildProcessInfo& tools_chuild, std::string& response)
{
	char		buffer[1024];
	int			bytes_read;

	response.clear();
	response = "HTTP/1.1 200 OK\r\n";
	while ((bytes_read = read(tools_chuild.fd[0], buffer, 1024)) > 0)
	{
		buffer[bytes_read] = '\0';
		response += buffer;
	}
	close(tools_chuild.fd[0]);
	return (true);
}

static bool	create_response_to_client(std::string listFiles, std::string& response)
{
	ChildProcessInfo	tools_chuild;

	if (execute_cgi_listFiles(tools_chuild, listFiles) == false)
		return (false);
	if (read_response_cgi(tools_chuild, response) == false)
		return (false);
	return (true);
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

bool	Server::response_client_with_list_files()
{
	std::string	response;
	std::string listFiles;

	if (get_ListFiles(listFiles) == false)
		return (false);
	add_prefix_listFiles(response);
	if (create_response_to_client(listFiles, response) == false)
		return (false);
	return (response_client(response));
}

static bool	delete_file_server(std::string fileName)
{
	std::string	pathFile = "./upload/" + fileName;

	if (std::remove(pathFile.c_str()) != 0)
		return (write_error("Error: handle_delete: Not possible to remove file"));
	return (true);
}

bool	Server::handle_delete( void )
{

	if (!_parser_request->get_endPoint()[7])
		return (response_client_with_list_files());
	return (delete_file_server(std::string(_parser_request->get_endPoint(), 8)));
}
