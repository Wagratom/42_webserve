/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/18 10:09:16 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

#define BYTES 'K'
#define KILOBYTES 'M'
#define MEGABYTES 'G'

#define maximumSizeAllowed 2000000000

# define ESMERALDA "\033[0;32m"
# define CIANO "\033[0;36m"
# define AZUL "\033[0;34m"

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
		bool					isLineEmpty(std::string& line);
		bool					ParserConfigurationFile( void );
		bool					parserLineServer( std::string& line );
		bool					parserConfigurationServer( void );

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
		bool					get_limit_except(std::string& line, aux_configuration* dst);
		bool					get_cgi(std::string& line, aux_configuration* dst);
		bool					get_timeout( std::string& line );

		bool					parserLocation( void );
		bool					saveLocationInfos(t_location& location);
		bool					handleLineLocation(std::string& line, t_location& dst);
		bool					saveLocationName(std::string& locationName);

		std::vector<Server_configuration*>	get_server_configuration( void );
		// std::map<std::string, t_location*>	get_location_configuration( void );

	private:
		std::map<std::string, directiveNginxUniversal>			_dictionary_universal;
		std::map<std::string, directiveNginxServer>				_dictionary_server;
		std::vector<Server_configuration*>						_server_configurations;
		std::vector<std::string>								_file;
		std::string												_filename;
		size_t													_indexServer;
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

class  Server_configuration : public aux_configuration
{
	public:
		Server_configuration( void );
		~Server_configuration( void );

		std::map<std::string, std::string*>	get_error_page( void );
		std::map<std::string, t_location*>	get_locations( void );
		std::map<std::string, std::string>	get_cgi( void );
		std::string							get_server_name( void );
		std::string							get_root( void );
		std::string							get_index( void );
		std::string							get_return( void );
		bool								get_autoIndex( void );
		int									get_port( void );
		int									get_clientMaxBodySize( void );

		void	set_locations( std::string location_name, t_location* location );
		void	set_error_page( std::string number, std::string error_page );
		void	set_cgi( std::string extension, std::string path );
		void	set_server_name( std::string server_name );
		void	set_client_max_body_size( int size );
		void	set_return( std::string return_ );
		void	set_autoIndex( bool autoIndex );
		void	set_index( std::string index );
		void	set_root( std::string root );
		void	set_port( int port );

	private:
		std::map<std::string, std::string*>	_error_page;
		std::map<std::string, t_location*>	_locations;
		std::map<std::string, std::string>	_cgi;
		std::string							_server_name;
		std::string							_return;
		std::string							_index;
		std::string							_root;
		int									_clientMaxBodySize;
		bool								_autoIndex;
		int									_timeout;
		int									_port;
};

/*############################################################################*/
/*                         Location Configuration                             */
/*############################################################################*/

class Location_configuration : public aux_configuration
{
	public:
		Location_configuration( void );
		~Location_configuration( void );

		std::map<std::string, std::string*>	get_error_page( void );
		std::map<std::string, std::string>	get_cgi( void );
		std::vector<std::string>			get_limit_except( void );
		std::string							get_root( void );
		std::string							get_index( void );
		std::string							get_return( void );
		bool								get_autoIndex( void );
		int									get_clientMaxBodySize( void );


		void	set_error_page( std::string number, std::string error_page );
		void	set_limit_except( std::vector<std::string> method );
		void	set_cgi( std::string extension, std::string path );
		void	set_client_max_body_size( int maxSize );
		void	set_autoIndex( bool autoIndex );
		void	set_return( std::string index );
		void	set_root( std::string root );
		void	set_index( std::string index );


	private:
		std::map<std::string, std::string*>	_error_page;
		std::map<std::string, std::string>	_cgi;
		std::vector<std::string>			_limit_except;
		std::string							_return;
		std::string							_index;
		std::string							_root;
		bool								_autoIndex;
		int									_clientMaxBodySize;
};

/*############################################################################*/
/*                          Universal Functions                               */
/*############################################################################*/

bool	write_error(std::string msg);
bool	write_error_prefixS(std::string prefix, std::string msg);
bool	write_error_prefixI(std::string prefix, int number);
bool	startsWithWord(std::string& listen, std::string word);
bool	has_semicolon_at_end(std::string& line);
bool	extractPrefixWord(std::string& line, size_t lenghtErase);

void	erase_comments(std::string& line);
bool	erase_isspaces(size_t indentation, std::string& line);
bool	removeIndentationAndComments(int indentation, std::string& line);

// bool	equal_or_err_i(int a, int b, int line);
// bool	different_or_err_i(int a, int b, int line);
// bool	equal_or_err_s(std::string a, std::string b, int line);
// bool	different_or_err_s(std::string a, std::string b, int line);
// bool	equal_or_err_b(bool a, bool b, int line);
// bool	different_or_err_b(bool a, bool b, int line);
