/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_clear.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:55:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 22:07:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	l_ft_lstclear(t_location **lst)
{
	t_location	*tmp;

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
