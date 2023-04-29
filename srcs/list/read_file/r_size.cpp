/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_size.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:05:48 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:14 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

int	r_ft_lstsize(list_file *lst)
{
	int	count;

	count = 0;
	while (lst && count++ >= 0)
		lst = lst->next;
	return (count);
}
