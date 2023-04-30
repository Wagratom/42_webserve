/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_add_back.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:00:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	l_ft_lstadd_back(t_location_settings **lst, t_location_settings *_new)
{
	t_location_settings	*end;

	if (lst == NULL)
		return ;
	if (*lst == 0)
		(*lst) = _new;
	else
	{
		end = l_ft_lstlast(*lst);
		end->next = _new;
	}
}
