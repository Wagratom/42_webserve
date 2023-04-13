# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 09:48:43 by wwallas-          #+#    #+#              #
#    Updated: 2023/04/12 10:36:54 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserver
INCLUDES	=	-I ./include/

SRCS		=	main.cpp create_server_conf.cpp create_server.cpp configure_server.cpp \
				start_server.cpp handle_new_connections.cpp handle_events.cpp \
				separate_request_child.cpp handle_request.cpp error.cpp fork_status.cpp

OBJS_DIR	=	./objs/
OBJS		=	$(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

CC			=	c++ -g3
CFLAGS		=	-std=c++98 -Wall -Wextra -Werror

VPATH		=	./srcs/ \
				./srcs/ults \
				./srcs/server \
				./srcs/events \
				./srcs/program

$(OBJS_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
