/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:24 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/21 10:13:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_request.hpp>

Parser_request::Parser_request( std::string& request_client)
	: _request(request_client)
	, _order_request("")
	, _method("")
	, _endPoint("")
	, _versionHTTP("")
	, need_cgi(false)
{};

Parser_request::~Parser_request() {
}
