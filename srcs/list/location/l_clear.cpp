/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_clear.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:55:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 12:41:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	l_ft_lstclear(t_location_settings **lst)
{
	t_location_settings	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		delete (*lst)->configuration;
		delete (*lst);
		(*lst) = NULL;
		*lst = tmp;
	}
}
