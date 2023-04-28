/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:00:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:06:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	r_ft_lstadd_back(list_file **lst, list_file *_new)
{
	list_file	*end;

	if (lst == NULL)
		return ;
	if (*lst == 0)
		(*lst) = _new;
	else
	{
		end = r_ft_lstlast(*lst);
		end->next = _new;
	}
}
