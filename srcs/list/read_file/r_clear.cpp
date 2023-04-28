/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:55:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:05:46 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	r_ft_lstclear(list_file **lst, void (*del)(void*))
{
	list_file	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		r_ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
