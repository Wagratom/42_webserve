/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_last.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:03:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

list_file*	r_ft_lstlast(list_file *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
