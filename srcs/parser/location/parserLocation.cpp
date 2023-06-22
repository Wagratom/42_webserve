/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:31:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 15:14:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <Parser_configuration.hpp>

static bool	alloc_location(t_location **location)
{
	*location = new t_location();

	if (*location == NULL)
		return (write_error("Error: Memory allocation failed"));

	(*location)->configuration = new location_configuration();
	if ((*location)->configuration == NULL)
		return (write_error("Error: Memory allocation failed"));

	(*location)->next = NULL;
	return (true);
}

static bool	delete_location(t_location *location)
{
	if (location == NULL)
		return false;
	if (location->configuration != NULL)
		delete location->configuration;
	delete location;
	return false;
}
/*############################################################################*/
/*                             INITIALIZE PARSER                              */
/*############################################################################*/

bool	Parser_configuration::parserLocation( void )
{
	t_location*	location = NULL;

	if (alloc_location(&location) == false)
		return (false);
	if (saveLocationName(location->endPoint) == false)
		return (delete_location(location));
	if (saveLocationInfos(*location) == false)
		return (delete_location(location));
	_locations[location->endPoint] = location;
	return (true);
}
