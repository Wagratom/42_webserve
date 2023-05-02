/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_request.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:18:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 14:02:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::response_request( void )
{
	std::string tmp = _parser_request->get_metodo();

	if (tmp == "GET")
		GET_requesition();
	if (tmp == "POST")
		std::cout << "Pediu POST" << std::endl;
	if (tmp == "DELETE")
		std::cout << "Pediu DELETE" << std::endl;
	write_debug("\n");
	return (true);
}
