/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 10:03:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

class configuration_server;
class configuration_location;

class	Parser_configuration
{
	public:
		Parser_configuration( void );
		Parser_configuration( Parser_configuration& src );
		Parser_configuration( std::string filename );
		virtual ~Parser_configuration( void );

		t_server_dictionary*	create_server_dictionary( void );
		configuration_server*	create_configuration_server( void );
		t_universal_dictionary*	create_universal_dictionary( void );
		configuration_location*	create_configuration_location( void );

		bool					parser( void );
		bool					read_file( void );
		bool					parser_file( void );
		void					save_valid_line(std::string line);

		bool					check_server( std::string& line );
		bool					handle_server( std::string& line );
		bool					check_in_dict_server(std::string& line);
		bool					check_in_dict_universal(std::string& line);

		bool					get_port( std::string& line );
		bool					get_server_name( std::string& line );

		bool					get_client_max_body_size( std::string& line, Parser_configuration* dst );
		bool					get_root(std::string& line, Parser_configuration* dst);
		bool					get_error_page( std::string& line, Parser_configuration* dst );
		bool					get_index(std::string& line , Parser_configuration* dst);

		bool					parser_location( void );
		bool					handle_location_line(std::string& line);
		bool					get_location(std::string& line);

		configuration_server*	get_server( void );

	private:
		t_server_dictionary*	_dictionary_server;
		t_universal_dictionary*	_dictionary_universal;
		configuration_server*	_server;
		configuration_location*	_location;
		list_file*				_file;
		std::string				_filename;
};

class configuration_server : public Parser_configuration
{
	public:
		configuration_server( void ) : Parser_configuration() {};
		~configuration_server( void ){};

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
		std::string		_client_max_body_size;
		std::string		_error_page;
};

class configuration_location : public Parser_configuration
{
	public:
		configuration_location( void ) :  Parser_configuration() {};
		~configuration_location( void ){};

		std::string	get_location( void );
		std::string	get_root( void );
		std::string	get_index( void );
		std::string	get_error_page( void );
		std::string	get_client_max_body_size( void );

		void	set_location( std::string location );
		void	set_root( std::string root );
		void	set_index( std::string index );
		void	set_error_page( std::string error_page );
		void	set_client_max_body_size( std::string client_max_body_size );

	private:
		std::string	_location;
		std::string	_root;
		std::string	_index;
		std::string	_autoindex;
		std::string	_cgi;
		std::string	_cgi_path;
		std::string	_error_page;
		std::string	_client_max_body_size;
};

bool	write_error(std::string msg);
bool	valid_word(std::string& listen, std::string word);
bool	has_semicolon_at_end(std::string& line);
bool	equal_or_err_i(int a, int b, int line);
bool	different_or_err_i(int a, int b, int line);
bool	equal_or_err_s(std::string a, std::string b, int line);
bool	different_or_err_s(std::string a, std::string b, int line);
bool	equal_or_err_b(bool a, bool b, int line);
bool	different_or_err_b(bool a, bool b, int line);

void		ft_lstadd_back(list_file **lst, list_file *_new);
void		ft_lstclear(list_file **lst, void (*del)(void*));
list_file	*ft_lstlast(list_file *lst);
list_file	*ft_lstnew(std::string content);
int			ft_lstsize(list_file *lst);
void		ft_lstdelone(list_file *lst, void (*del)(void*));
