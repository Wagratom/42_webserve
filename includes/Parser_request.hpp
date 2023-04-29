/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_request.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:39:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

class Parser_request
{
	public:
		Parser_request( std::string& request_client );
		~Parser_request();

		bool	parse_requesition_line( std::string** verbs );

		bool	parse_requisition_line( void );
		bool	get_requesition_line( void );
		bool	get_verb( void );
		bool	valid_verb( std::string** verbs );
		bool	get_recurso( void );
		bool	valid_htpp_version( void );
		bool	write_error_prefix( std::string prefix );
		bool	write_msg_error(std::string message);

		std::string get_request( void );
		std::string get_order_request( void );
		std::string get_metodo( void );
		std::string get_endPoint( void );

	private:
		std::string					_request;
		std::string					_order_request;
		std::string					_metodo;
		std::string					_endPoint;
};
