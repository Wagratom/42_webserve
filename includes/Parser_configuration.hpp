/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 19:52:34 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

/*############################################################################*/
/*                           Parser_configuration                             */
/*############################################################################*/
typedef bool (Parser_configuration::*directiveNginxServer)(std::string&);
typedef bool (Parser_configuration::*directiveNginxUniversal)(std::string&, aux_configuration*);

class	Parser_configuration
{
	public:
		Parser_configuration( void );
		Parser_configuration( Parser_configuration& src );
		Parser_configuration( std::string filename );
		virtual ~Parser_configuration( void );

		server_configuration*	create_configuration_server( void );
		void	initializeServerDictionary( void );
		void	initializeUniversalDictionary ( void );

		bool					controlParserConfiguration( void );
		bool					readConfigurationFile( void );
		bool					parserLineServer( std::string& line );
		bool					parserRestFile( void );

		bool					handle_server( std::string& line );
		bool					checkDirectiveServer(std::string& line);
		bool					checkDirectiveUniversal(std::string& line);

		bool					get_port( std::string& line );
		bool					get_server_name( std::string& line );

		bool					get_root(std::string& line, aux_configuration* dst);
		bool					get_index(std::string& line , aux_configuration* dst);
		bool					get_client_max_body_size( std::string& line, aux_configuration* dst );
		bool					get_error_page( std::string& line, aux_configuration* dst );

		bool					parserLocation( void );
		bool					saveLocationInfos(t_location& location);
		bool					handleLineLocation(std::string& line, t_location& dst);
		bool					saveLocationName(std::string& locationName);

		server_configuration*				get_server_configuration( void );
		std::map<std::string, t_location*>	get_location_configuration( void );

	private:
		std::map<std::string, directiveNginxServer>				_dictionary_server;
		std::map<std::string, directiveNginxUniversal>			_dictionary_universal;

		server_configuration*				_server_configuration;
		std::map<std::string, t_location*>	_locations;
		std::vector<std::string>			_file;
		std::string							_filename;
};

/*############################################################################*/
/*                         Server Configuration                               */
/*############################################################################*/

class aux_configuration
{
	public:
		aux_configuration( void ) {} ;
		virtual ~aux_configuration( void ){} ;
};

class server_configuration : public aux_configuration
{
	public:
		server_configuration( void )
			: aux_configuration()
			, _port(-1)
		{};
		~server_configuration( void ){};

		int			get_port( void );
		std::string	get_server_name( void );
		std::string	get_root( void );
		std::string	get_index( void );
		std::string	get_error_page( void );
		std::string	get_client_max_body_size( void );

		void	set_port( int port );
		void	set_server_name( std::string server_name );
		void	set_root( std::string root );
		void	set_index( std::string index );
		void	set_error_page( std::string error_page );
		void	set_client_max_body_size( std::string client_max_body_size );

	private:
		int				_port;
		std::string		_server_name;
		std::string		_root;
		std::string		_index;
		std::string		_error_page;
		std::string		_client_max_body_size;
};

/*############################################################################*/
/*                         Location Configuration                             */
/*############################################################################*/

class location_configuration : public aux_configuration
{
	public:
		location_configuration( void ) :  aux_configuration() {};
		~location_configuration( void ){};

		std::string	get_root( void );
		std::string	get_index( void );
		std::string	get_error_page( void );
		std::string	get_client_max_body_size( void );

		void	set_root( std::string root );
		void	set_index( std::string index );
		void	set_error_page( std::string error_page );
		void	set_client_max_body_size( std::string client_max_body_size );

		void	print_data( void ) {
			std::cout << "root: " << _root << std::endl;
			std::cout << "index: " << _index << std::endl;
			std::cout << "error_page: " << _error_page << std::endl;
			std::cout << "client_max_body_size: " << _client_max_body_size << std::endl;
		}

	private:
		std::string	_root;
		std::string	_index;
		std::string	_error_page;
		std::string	_client_max_body_size;
		std::string	_autoindex;
		std::string	_cgi;
		std::string	_cgi_path;
};

/*############################################################################*/
/*                          Universal Functions                               */
/*############################################################################*/

bool	write_error(std::string msg);
bool	startsWithWord(std::string& listen, std::string word);
bool	has_semicolon_at_end(std::string& line);
bool	equal_or_err_i(int a, int b, int line);
void	erase_comments(std::string& line);
bool	erase_isspaces(size_t indentation, std::string& line);
bool	removeIndentationAndComments(int indentation, std::string& line);

bool	different_or_err_i(int a, int b, int line);
bool	equal_or_err_s(std::string a, std::string b, int line);
bool	different_or_err_s(std::string a, std::string b, int line);
bool	equal_or_err_b(bool a, bool b, int line);
bool	different_or_err_b(bool a, bool b, int line);
