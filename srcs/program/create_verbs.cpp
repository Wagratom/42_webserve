/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_verbs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:46:09 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 12:16:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string**	Server::create_verbs( void )
{
	std::string** verbs = new std::string*[10];
	verbs[0] = new std::string("GET");
	verbs[1] = new std::string("POST");
	verbs[2] = new std::string("PUT");
	verbs[3] = new std::string("DELETE");
	verbs[4] = new std::string("PATCH");
	verbs[5] = new std::string("OPTIONS");
	verbs[6] = new std::string("HEAD");
	verbs[7] = new std::string("TRACE");
	verbs[8] = new std::string("CONNECT");
	verbs[9] = NULL;
	return (verbs);
}
