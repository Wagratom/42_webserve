/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_clear.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:55:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	r_ft_lstclear(list_file **lst)
{
	list_file	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		delete (*lst);
		*lst = tmp;
	}
}
