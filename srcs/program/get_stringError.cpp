/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stringError.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:50:59 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/16 14:52:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

std::string	get_stringError(int error)
{
	if (error == ERROR400) // Bad Request
		return ("400");
	if (error == ERROR403) // Forbidden
		return ("403");
	if (error == ERROR404) // Not Found
		return ("404");
	if (error == ERROR405) // Method Not Allowed
		return ("405");
	if (error == ERROR413) // Request Entity Too Large
		return ("413");
	if (error == ERROR500) // Internal Server Error
		return ("500");
	// if (error == ERROR501) // Not Implemented
		// return ("501")
	// if (error == ERROR505) // HTTP Version Not Supported
		// return ("505")
	return ("");
}
