# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 15:47:23 by wwallas-          #+#    #+#              #
#    Updated: 2023/04/26 19:27:18 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	parser

MAIN		=

INCLUDE		=	-I./includes

SOURCE		=	func_uni.cpp port.cpp server_name.cpp tester.cpp parser_serve.cpp\
				client_max_body_size.cpp error_page.cpp parser_initialize.cpp \
				parser.cpp check_server.cpp index.cpp root.cpp parser_location.cpp\
				get_location.cpp get_server.cpp\
				r_add_back.cpp r_clear.cpp r_last.cpp r_new.cpp r_size.cpp r_delone.cpp \
				l_add_back.cpp l_clear.cpp l_last.cpp l_size.cpp l_delone.cpp \
				create_server_conf.cpp create_server.cpp configure_server.cpp \
				start_server.cpp handle_new_connections.cpp handle_events.cpp \
				handle_request.cpp error.cpp fork_status.cpp \
				sig_closed_server.cpp debug.cpp create_verbs.cpp parser_request.cpp \
				parse_requesition_line.cpp \
				gets_configuration_server.cpp sets_configuration_server.cpp \
				gets_configuration_location.cpp sets_configuration_location.cpp \

OBJECTS		=	$(patsubst %.cpp, $(OBJECTS_DIR)/%.o, $(SOURCE))
OBJECTS_DIR	=	objs

CC 		=	c++ -g3 --std=c++98

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH	=	./srcs \
VPATH	=	./srcs/initialize_class \
			./srcs/events \
			./srcs/list/read_file \
			./srcs/list/location \
			./srcs/parser ./srcs/parser/server ./srcs/parser/location \
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

VG_FILE_TST		=	$(TST_PATH)/$(t).c
VG_OJBS_TST		=	$(patsubst %.c, %.vg.out, $(VG_FILE_TST))

VG_FILE_TSTS	=	$(wildcard $(TST_PATH)/**/*.c)
VG_OJBS_TSTS	=	$(patsubst %.c, %.vg.out, $(VG_FILE_TSTS))

%.vg.out:	%.c
		@$(CC) $< $(LIB_FILO) -o $@ $(INCLUDE)
		@valgrind --leak-check=full ./$@
		@$(RM) $@

vgtest: re_mandatory $(VG_OJBS_TST)

vgtests: re_mandatory $(VG_OJBS_TSTS)

.PHONY: all clean fclean re
