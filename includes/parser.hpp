/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 15:57:26 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>

class configuration_server;
class configuration_location;



class	Parser_configuration
{


	public:
		Parser_configuration( int a ){
				(void)a;
	}
		Parser_configuration( void ):	_dictionary_server(create_server_dictionary()),
										_dictionary_universal(create_universal_dictionary()),
										_server(create_configuration_server()),
										_location(create_configuration_location()),
										_file(NULL) {};

		virtual ~Parser_configuration( void ) {};

		t_server_dictionary*	create_server_dictionary( void );
		configuration_server*	create_configuration_server( void );
		t_universal_dictionary*	create_universal_dictionary( void );
		configuration_location*	create_configuration_location( void );




		bool					parser( char* filename );
		bool					read_file( char* filename );
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
		bool					handle_line_location(std::string& line);
		bool					get_location(std::string& line);

	private:
		t_server_dictionary*	_dictionary_server;
		t_universal_dictionary*	_dictionary_universal;
		configuration_server*	_server;
		configuration_location*	_location;
		list_file*				_file;
};

class configuration_server : public Parser_configuration
{
	public:
		configuration_server( void ) : Parser_configuration(10) {};
		~configuration_server( void ){};

		int				port;
		std::string		server_name;
		std::string		client_max_body_size;
		std::string		error_page;
		std::string		index;
		std::string		root;
};

class configuration_location : public Parser_configuration
{
	public:
	configuration_location( void ) :  Parser_configuration(10) {};
	~configuration_location( void ){};


		std::string		location;
		std::string		root;
		std::string		index;
		std::string		autoindex;
		std::string		cgi;
		std::string		cgi_path;
		std::string		error_page;
		std::string		client_max_body_size;
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
