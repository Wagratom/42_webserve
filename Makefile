# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 15:47:23 by wwallas-          #+#    #+#              #
#    Updated: 2023/05/05 10:37:30 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	parser

MAIN		=

INCLUDE		=	-I./includes

SOURCE		=	auxiliares.cpp port.cpp server_name.cpp tester.cpp parser_serve.cpp \
				client_max_body_size.cpp error_page.cpp init_Parser_configuration.cpp \
				parser.cpp check_server.cpp index.cpp root.cpp parser_location.cpp \
				get_location.cpp gets_server_configuration.cpp init_parser_request.cpp \
				r_add_back.cpp r_clear.cpp r_last.cpp r_new.cpp r_size.cpp \
				l_add_back.cpp l_clear.cpp l_last.cpp l_size.cpp closed_fd_epoll.cpp \
				create_server_conf.cpp create_server.cpp configure_server.cpp \
				start_server.cpp handle_new_connections.cpp filter_event.cpp \
				set_client_not_block.cpp error.cpp capture_new_events.cpp \
				sig_closed_server.cpp debug.cpp create_verbs.cpp handle_client_request.cpp \
				set_envs_order_line.cpp gets_Parser_request.cpp set_envs_header.cpp\
				gets_location_configuration.cpp sets_location_configuration.cpp \
				gets_Parser_configuration.cpp sets_server_configuration.cpp \
				read_request.cpp parser_request.cpp response_request.cpp \
				GET_requesition.cpp SET_requesition.cpp DELETE_requesition.cpp \
				generete_path_to_response.cpp clean_request.cpp

OBJECTS		=	$(patsubst %.cpp, $(OBJECTS_DIR)/%.o, $(SOURCE))
OBJECTS_DIR	=	objs

CC 		=	c++ -g3 --std=c++98

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH	=	./srcs \
VPATH	=	./srcs/initialize_class \
			./srcs/events \
			./srcs/list/read_file ./srcs/list/location \
			./srcs/parser ./srcs/parser/server ./srcs/parser/location ./srcs/parser/universal \
			./srcs/program \
			./srcs/request \
			./srcs/server \
			./srcs/ults \

$(OBJECTS_DIR)/%.o:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all:	$(NAME)

$(NAME):	$(OBJECTS_DIR) $(OBJECTS)
				$(CC) $(CFLAGS) ./srcs/main.cpp $(OBJECTS) -o $@ $(INCLUDE)

$(OBJECTS_DIR):
				mkdir -p $@

clean:
				$(RM) $(OBJECTS_DIR)

fclean:		clean
				$(RM) $(NAME)
norm:
	@echo "\n			INCLUDES\n" && norminette include
	@echo "\n			SOURCES\n" && norminette source


re: fclean all

################################################################################
#									TEST
################################################################################

re_mandatory: clean $(OBJECTS_DIR) $(OBJECTS)

TST_PATH		=	./test


FILE_TST		=	$(TST_PATH)/$(t).cpp
OJBS_TST		=	$(patsubst %.cpp, %.out, $(FILE_TST))

FILE_TSTS		=	$(wildcard $(TST_PATH)/*.cpp);
OJBS_TSTS		=	$(patsubst %.cpp, %.out, $(FILE_TSTS))

%.out:	%.cpp
		@$(CC) $(OBJECTS) $< -o teste $(INCLUDE)
		@./teste
		@$(RM) teste

test: re_mandatory $(OJBS_TST)

tests: re_mandatory $(OJBS_TSTS)

################################################################################
#									TESTVG
################################################################################

TST_PATH		=	./test

VG_FILE_TST		=	$(TST_PATH)/$(t).cpp
VG_OJBS_TST		=	$(patsubst %.cpp, %.vg.out, $(VG_FILE_TST))

VG_FILE_TSTS	=	$(wildcard $(TST_PATH)/*.cpp)
VG_OJBS_TSTS	=	$(patsubst %.cpp, %.vg.out, $(VG_FILE_TSTS))

%.vg.out:	%.cpp
		@$(CC) $(OBJECTS) $< $(LIB_FILO) -o vgteste $(INCLUDE)
		@valgrind --leak-check=full ./vgteste
		@$(RM) vgteste

vgtest: re_mandatory $(VG_OJBS_TST)

vgtests: re_mandatory $(VG_OJBS_TSTS)

.PHONY: all clean fclean re
