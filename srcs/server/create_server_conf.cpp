/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_serve_conf.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 07:52:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	create_server_configured(server& data)
{
	if (!create_server(data))
		return (false);
	if (!conf_serve_to_read(data))
		return (false);
	return (true);
}
