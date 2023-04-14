/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_closed_server.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:23:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 20:35:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

void	Server::set_shutdown_server(int sig)
{
	(void)sig;
	std::cout <<"\n\n\n\n\n\n\n peguei" << std::endl;
}

void	Server::set_signal( void )
{
	signal(SIGINT, set_shutdown_server);
}
