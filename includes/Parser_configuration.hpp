/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/01 13:21:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

#define BYTES 'K'
#define KILOBYTES 'M'
#define MEGABYTES 'G'

#define maximumSizeAllowed 2000000000

/*############################################################################*/
/*                           Parser_configuration                             */
/*############################################################################*/
typedef bool (Parser_configuration::*directiveNginxServer)(std::string&);
typedef bool (Parser_configuration::*directiveNginxUniversal)(std::string&, aux_configuration*);

class	Parser_configuration
{
	public:
		Parser_configuration( void );
		Parser_configuration( std::string filename );
		virtual ~Parser_configuration( void );

		void					initializeServerDictionary( void );
		void					initializeUniversalDictionary ( void );

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
		bool					get_clientMaxBodySize( std::string& line, aux_configuration* dst );
		bool					get_error_page( std::string& LineErrorPage, aux_configuration* dst );
		bool					get_return( std::string& LineErrorPage, aux_configuration* dst );
		bool					get_autoIndex( std::string& LineErrorPage, aux_configuration* dst );

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
			, _clientMaxBodySize(0)
			, _server_name("")
			, _root("")
			, _index("")
		{};
		~server_configuration( void ){
			std::map<std::string, std::string*>::iterator it = _error_page.begin();
			while (it != _error_page.end())
			{
				delete it->second;
				it++;
			}
		};

		int			get_port( void );
		int			get_clientMaxBodySize( void );
		bool		get_autoIndex( void );
		std::string	get_server_name( void );
		std::string	get_root( void );
		std::string	get_index( void );
		std::string	get_return( void );
		std::map<std::string, std::string*>	get_error_page( void );

		void	set_port( int port );
		void	set_server_name( std::string server_name );
		void	set_root( std::string root );
		void	set_index( std::string index );
		void	set_error_page( std::string number, std::string error_page );
		void	set_client_max_body_size( int size );
		void	set_return( std::string return_ );
		void	set_autoIndex( bool autoIndex );

	private:
		int									_port;
		int									_clientMaxBodySize;
		bool								_autoIndex;
		std::string							_server_name;
		std::string							_root;
		std::string							_index;
		std::string							_return;
		std::map<std::string, std::string*>	_error_page;
};

/*############################################################################*/
/*                         Location Configuration                             */
/*############################################################################*/

class location_configuration : public aux_configuration
{
	public:
		location_configuration( void )
			:  aux_configuration()
			, _root("")
			, _index("")
			, _clientMaxBodySize(0)
			, _autoindex("")
			{};
		~location_configuration( void ){
			std::map<std::string, std::string*>::iterator it = _error_page.begin();
			while (it != _error_page.end())
			{
				delete it->second;
				it++;
			}
		};

		std::string	get_root( void );
		std::string	get_index( void );
		std::string	get_return( void );
		int			get_clientMaxBodySize( void );
		bool		get_autoIndex( void );
		std::map<std::string, std::string*>	get_error_page( void );

		void	set_root( std::string root );
		void	set_index( std::string index );
		void	set_return( std::string index );
		void	set_error_page( std::string number, std::string error_page );
		void	set_client_max_body_size( int maxSize );
		void	set_autoIndex( bool autoIndex );


	private:
		std::string							_root;
		std::string							_index;
		int									_clientMaxBodySize;
		bool								_autoIndex;
		std::string							_autoindex;
		std::string							_return;
		std::map<std::string, std::string*>	_error_page;
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
