/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_closed_server.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:23:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:15:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::set_shutdown_server(int sig)
{
	(void)sig;
	std::cout <<"\n\n\n\n\n\n\n peguei" << std::endl;
}

void	Server::set_signal( void )
{
	signal(SIGINT, set_shutdown_server);
}
