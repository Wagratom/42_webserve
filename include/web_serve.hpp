/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_serve.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 14:03:06 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/socket.h>
# include <cstdio>
# include <netinet/in.h>
# include <iostream>
# include <cstring>
# include <sys/epoll.h>
# include <errno.h>

bool	create_server(int& socket_dst);
bool	write_error_prefix(std::string prefix);
