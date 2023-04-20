/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:06:26 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <structs.hpp>


class	Parser_configuration
{
	public:
		Parser_configuration( void ): dictionary(create_dictionary_parser()), file(NULL) {};
		~Parser_configuration( void ) {};

		t_dictionary_parser*	create_dictionary_parser( void );

		bool					parser( char* filename );
		bool					read_file( char* filename );
		bool					handle_server( std::string line );


		bool					handle_line_server(std::string& line);
		void					save_valid_line(std::string line);

		bool					get_server( std::string& line );
		bool					get_port( std::string& line );
		bool					get_server_name( std::string& line );
		bool					get_client_max_body_size( std::string& line );
		bool					get_root(std::string& line);
		bool					get_error_page( std::string& line );
		bool					get_index(std::string& line);

	private:
		t_dictionary_parser*	dictionary;
		t_server				server;
		list_file*				file;
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
