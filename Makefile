# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 15:47:23 by wwallas-          #+#    #+#              #
#    Updated: 2023/07/03 19:07:31 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	parser

MAIN		=

INCLUDE		=	-I./includes

SOURCE		=	auxiliares.cpp port.cpp server_name.cpp tester.cpp parser_serve.cpp \
				clientMaxBodySize.cpp error_page.cpp init_Parser_configuration.cpp \
				parser.cpp check_server.cpp index.cpp root.cpp parserLocation.cpp \
				get_location.cpp gets_server_configuration.cpp init_parser_request.cpp \
				create_server_conf.cpp create_server.cpp configure_server.cpp \
				start_server.cpp handleNewConnections.cpp filterEvent.cpp \
				set_fdNotBlock.cpp error.cpp captureNewEvents.cpp \
				debug.cpp create_verbs.cpp handle_client_request.cpp sendResponseClient.cpp \
				set_envs_order_line.cpp gets_Parser_request.cpp set_envs_header.cpp\
				gets_location_configuration.cpp sets_location_configuration.cpp \
				gets_Parser_configuration.cpp sets_server_configuration.cpp \
				read_request.cpp response_request.cpp responseClientGET.cpp \
				handle_GET_requesition.cpp handle_DELETE_requesition.cpp\
				generetePathToResponse.cpp cleanupFd.cpp auxProcess.cpp \
				responseClientError.cpp responseLocation.cpp generateHeaders.cpp \
				handle_POST_request.cpp responseServer.cpp generateResponseCGI.cpp\
				responseFile.cpp responseLocationAux.cpp GetContentFilePhp.cpp \
				getContentFile.cpp responseClientPOST.cpp processFileUpload.cpp \
				responseClientListFiles.cpp generateListFiles.cpp readConfigurationFile.cpp\
				saveLocationInfos.cpp getErrosPage.cpp init_Server.cpp get_return.cpp \
				responseRedirect.cpp get_autoIndex.cpp handleInputGET.cpp \

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
				$(CC) $(CFLAGS) ./srcs/main.cpp $(OBJECTS) -o $@ $(INCLUDE)
# main.cpp/main.cpp
$(OBJECTS_DIR):
				mkdir -p $@

clean:
				$(RM) $(OBJECTS_DIR)

PDF:
	pip install PyPDF2

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
