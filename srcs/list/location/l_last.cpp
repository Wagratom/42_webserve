/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_last.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:03:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:32:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

t_location_settings*	l_ft_lstlast(t_location_settings *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
