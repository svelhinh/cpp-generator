# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/10 15:15:18 by svelhinh          #+#    #+#              #
#    Updated: 2017/04/10 15:16:16 by svelhinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

CFLAGS = -Wall -Wextra -Werror

NAME = cpp-generator

SRC =	cpp-generator.cpp

OBJ = $(SRC:.cpp=.o)

ifneq ($(shell uname), Linux)
SHELL = ZSH
endif

all: $(NAME)
		@echo -n "\033[0m"

$(NAME): $(OBJ)
		@$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

%.o: %.cpp
		@echo -n "\033[32m"
		@echo $<
		@$(CC) -o $@ -c $< $(CFLAGS)

clean:
		@echo "\033[32mObjects deleted\033[0m"
		@rm -f $(OBJ)

fclean: clean
		@echo "\033[32mExecutable deleted\033[0m"
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
