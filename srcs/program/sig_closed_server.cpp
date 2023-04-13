/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_closed_server.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:23:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 12:19:46 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

void	Server::set_shutdown_server(int sig)
{
	(void)sig;
	std::cout <<"\n\n\n\n\n\n\n peguei" << std::endl;
	exit(EXIT_SUCCESS);
}

void	Server::set_signal( void )
{
	signal(SIGTERM, set_shutdown_server);
}
