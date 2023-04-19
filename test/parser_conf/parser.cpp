/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:09:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 10:40:07 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	teste1()
{
	std::string buffer;

	buffer = "server {\n\tlisten 8080; # Porta em que o servidor irá escutar\n\tserver_name example.com www.example.com; # Nomes de servidor aceitos \n\terror_page 404 /404.html; # Página de erro para erro 404  \n\tclient_max_body_size 10M; # Tamanho máximo do corpo da requisição em bytes";
	return (true);
}

int main ( void )
{

}
