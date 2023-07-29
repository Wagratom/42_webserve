/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_request.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/29 10:17:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

class	Parser_request
{
	public:
		Parser_request( std::string& request_client );
		~Parser_request();

		bool	set_envs_order_line( std::string** verbs );

		bool	save_requesition_line( void );
		bool	valid_requestion_line( std::string** verbs );

		bool	set_envs_header( void );
		void	set_envs(std::map<std::string, std::string>& envs);

		std::string	get_request( void );
		std::string	get_order_request( void );
		std::string	get_metodo( void );
		std::string	get_endPoint( void );
		int			get_index_envs( void );

	private:
		std::string&	_request;
		std::string		_order_request;
		std::string		_method;
		std::string		_endPoint;
		std::string		_versionHTTP;
		bool			need_cgi;
};
