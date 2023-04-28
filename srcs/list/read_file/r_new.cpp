/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:46 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:03:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

list_file*	r_ft_lstnew(std::string content)
{
	list_file	*_new = new list_file;

	if (!_new)
		return (NULL);
	_new->line = content;
	_new->next = NULL;
	return (_new);
}
