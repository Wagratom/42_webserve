/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/18 11:21:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	get_error_page(char* line, std::string& error_page)
{
	std::string	aux;

	if (get_aux(line, aux) == false)
		return (false);
	if (valid_word(aux, "error_page") == false)
		return (false);
	if ()
}
