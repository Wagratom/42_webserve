/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delone.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:13:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 19:03:22 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	r_ft_lstdelone(list_file *lst, void (*del)(void*))
{
	del = del;
	free(lst);
	lst = NULL;
}
