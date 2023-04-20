/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:41:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 11:56:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../auxiliares.hpp"

bool	test_valid_location()
{
	if (aux_location("location / {", true, __LINE__) == false)
		return (false);
	if (aux_location("location /{", true, __LINE__) == false)
		return (false);
	if (aux_location("location / \t\t{", true, __LINE__) == false)
		return (false);
	if (aux_location("location /        {", true, __LINE__) == false)
		return (false);
	return (true);
}

bool	test_invalid_locarion()
{
	if (aux_location("location /", false, __LINE__) == false)
		return (false);
	if (aux_location("location a/ {", false, __LINE__) == false)
		return (false);
	if (aux_location("location /a {", false, __LINE__) == false)
		return (false);
	if (aux_location("location /a{", false, __LINE__) == false)
		return (false);
	if (aux_location("location /a\t\t{", false, __LINE__) == false)
		return (false);
	if (aux_location("location /a        {", false, __LINE__) == false)
		return (false);
	if (aux_location("location /        {a", false, __LINE__) == false)
		return (false);
	if (aux_location("location /        {{", false, __LINE__) == false)
		return (false);
	return (true);
}
int main( void )
{
	if (test_valid_location() == false)
		return (1);
	if (test_invalid_locarion() == false)
		return (1);
	std::cout << "Suscess!" << std::endl;
	return (0);
}
