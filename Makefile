# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 15:47:23 by wwallas-          #+#    #+#              #
#    Updated: 2023/07/15 11:31:06 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	parser

MAIN		=

INCLUDE		=	-I./includes

SOURCE		=	auxiliares.cpp port.cpp server_name.cpp parser_serve.cpp \
				clientMaxBodySize.cpp error_page.cpp init_Parser_configuration.cpp \
				parser.cpp check_server.cpp index.cpp root.cpp parserLocation.cpp \
				get_location.cpp gets_server_configuration.cpp init_parser_request.cpp \
				createServerConfigured.cpp create_server.cpp configure_server.cpp \
				startServer.cpp handleNewConnections.cpp filterEvent.cpp handleKeepAlive.cpp \
				set_fdNotBlock.cpp error.cpp captureNewEvents.cpp handlePostBody.cpp \
				debug.cpp handleClientRequest.cpp sendResponseClient.cpp \
				set_envs_order_line.cpp gets_Parser_request.cpp set_envs_header.cpp\
				gets_location_configuration.cpp sets_location_configuration.cpp \
				gets_Parser_configuration.cpp sets_server_configuration.cpp \
				readRequest.cpp responseRequest.cpp responseClientGET.cpp \
				handle_GET_requesition.cpp handle_DELETE_requesition.cpp\
				generetePathToResponse.cpp cleanupFd.cpp auxProcess.cpp createEpoll.cpp \
				responseClientError.cpp responseLocation.cpp generateHeaders.cpp \
				handlePostRequest.cpp responseServer.cpp generateResponseCGI.cpp\
				responseFileServer.cpp responseLocationAux.cpp GetContentFilePhp.cpp \
				getContentFile.cpp readOuputFormatedCGI.cpp createProcessResponse.cpp\
				responseClientListFiles.cpp readConfigurationFile.cpp cgi.cpp\
				saveLocationInfos.cpp getErrosPage.cpp init_Server.cpp return.cpp \
				responseRedirect.cpp autoIndex.cpp responseInputGET.cpp handleEvents.cpp \
				init_Server_configuration.cpp main.cpp limit_except.cpp get_timeout.cpp \
				init_Location_configuration.cpp

OBJECTS		=	$(patsubst %.cpp, $(OBJECTS_DIR)/%.o, $(SOURCE))
OBJECTS_DIR	=	objs

CC 		=	c++ -g3 --std=c++98

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH	=	./srcs \
			./srcs/initialize_class \
			./srcs/list/read_file ./srcs/list/location \
			./srcs/parser ./srcs/parser/server ./srcs/parser/location ./srcs/parser/universal \
			./srcs/program \
			./srcs/request \
			./srcs/server \
			./srcs/ults \
			./srcs/handle_get \
			./srcs/handle_post \
			./srcs/handle_delete \

$(OBJECTS_DIR)/%.o:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all:	$(NAME)

$(NAME):	$(OBJECTS_DIR) $(OBJECTS)
				$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(INCLUDE)
# main.cpp/main.cpp
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
