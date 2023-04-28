/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_clear.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:55:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:32:24 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	l_ft_lstclear(t_location_settings **lst, void (*del)(void*))
{
	t_location_settings	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		l_ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
