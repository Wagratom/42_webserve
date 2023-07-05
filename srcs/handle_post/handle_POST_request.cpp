/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/04 19:50:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_POST_requesition()
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	int			contentLenght = std::strtol(contentLength.c_str(), NULL, 10);

	std::cout << "handle_POST_requesition" << std::endl;
	if (server()->get_clientMaxBodySize() < contentLenght)
		return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	if (_parserRequest->get_request()[0])
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (redirectBodyCGI() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (responseServer("200"));
}

bool	Server::redirectBodyCGI( void )
{
	ChildProcessData	auxProcess;

	if (executeFork(auxProcess) == false)
		return (write_error("Error: redirectBodyCGI: executing fork"));
	std::cout << "\n\n";
	if (auxProcess.pid == CHILD_PROCESS)
	{
		dup2(_client_fd, STDIN_FILENO);
		setenv("REDIRECT_STATUS", "200", 1);
		setenv("SCRIPT_FILENAME", "./root/handlePOST.php", 1);
		setenv("PATH_DIR", PATH_UPLOAD, 1);
		setenv("DOCUMENT_ROOT", "/home/wallas/42_webserve/", 1);
		execlp("./root/handlePOST.php", "./root/handlePOST.php", NULL);
	}
	return true;
}
