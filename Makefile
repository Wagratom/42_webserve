# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 15:47:23 by wwallas-          #+#    #+#              #
#    Updated: 2023/04/18 13:09:11 by wwallas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	tester
LIB_FILO	=	philo.a

MAIN		=

INCLUDE		=	-I./includes

SOURCE		=	func_uni.cpp port.cpp server_name.cpp tester.cpp \
				client_max_body_size.cpp

OBJECTS		=	$(patsubst %.cpp, $(OBJECTS_DIR)/%.o, $(SOURCE))
OBJECTS_DIR	=	objects

CC 		=	c++ -g3 --std=c++98

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

VPATH	=	./srcs \

$(OBJECTS_DIR)/%.o:	%.cpp
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all:	$(NAME)

$(NAME):	$(OBJECTS_DIR) $(OBJECTS)
				$(CC) $(CFLAGS) ./srcs/main.cpp $(OBJECTS) -o $@ $(INCLUDE)

$(OBJECTS_DIR):
				mkdir -p $@

clean:
				$(RM) $(OBJECTS_DIR)

fclean:		clean
				$(RM) $(NAME)
				$(RM) $(LIB_FILO)

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

FILE_TSTS		=	$(wildcard $(TST_PATH)/**/*.cpp);
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
