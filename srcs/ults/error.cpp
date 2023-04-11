/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 14:01:35 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	write_error_prefix(std::string prefix)
{
	std::cout << prefix << ": ";
	if (errno != 0)
		std::cout << strerror(errno) << std::endl;
	return (false);
}
