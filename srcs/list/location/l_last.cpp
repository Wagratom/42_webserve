/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_last.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:03:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 22:07:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

t_location*	l_ft_lstlast(t_location *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
