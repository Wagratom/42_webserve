/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_size.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:05:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:44 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

int	l_ft_lstsize(t_location_settings *lst)
{
	int	count;

	count = 0;
	while (lst && count++ >= 0)
		lst = lst->next;
	return (count);
}
