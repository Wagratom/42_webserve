/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_status.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:36:20 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 08:36:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	fork_staus(pid_t& pid)
{
	pid = fork();
	if (pid == -1)
		return (write_error_prefix("fork_status"));
	return (true);
}
