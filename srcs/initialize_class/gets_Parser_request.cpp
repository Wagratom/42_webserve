/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_Parser_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:48:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/03 11:49:21 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <Parser_request.hpp>

std::string	Parser_request::get_request( void )
{
	return ( this->_request );
}
std::string	Parser_request::get_order_request( void )
{
	return ( this->_order_request );
}

std::string	Parser_request::get_metodo( void )
{
	return ( this->_metodo );
}

std::string	Parser_request::get_endPoint( void )
{
	return ( this->_endPoint );
}
