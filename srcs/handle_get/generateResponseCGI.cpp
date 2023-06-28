/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/28 11:29:21 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

static bool	callExecuteCgi(ChildProcessData& tools_chuild, std::string listFiles)
{
	char*	argv[3];
	char	*envp[2];

	envp[0] = (char*)listFiles.c_str();
	envp[1] = (char*)NULL;

	std::cout << "PATHFILE: " << getenv("PATHFILE") << std::endl;
	argv[0] = (char *)"/usr/bin/php-cgi";
	argv[1] = (char *)getenv("PATHFILE");
	argv[2] = NULL;

	dup2(tools_chuild.fd[1], STDOUT_FILENO);
	close(tools_chuild.fd[0]);
	close(tools_chuild.fd[1]);
	executeCGI(argv, envp);
	return (true);
}

static bool	executeCGI_ListFiles(ChildProcessData& tools_chuild, std::string listFiles)
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

bool	generateResponse(std::string listFiles, std::string& response)
{
	ChildProcessData	tools_chuild;

	response.clear();

	std::cout << "generateResponse" << std::endl;
	response = "HTTP/1.1 200 OK\r\n";
	if (executeCGI_ListFiles(tools_chuild, listFiles) == false)
		return (false);
	return (join_response_cgi(tools_chuild, response));
}
