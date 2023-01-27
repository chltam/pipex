# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htam <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 21:22:32 by htam              #+#    #+#              #
#    Updated: 2023/01/26 21:22:34 by htam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDE := ./libft/libft.a
SRCS := pipex.c

$(NAME) : $(SRCS)
	make -C libft
	$(CC) $(SRCS) $(INCLUDE) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(NAME)

fclean:
	make fclean -C libft
	rm -rf $(NAME)

re:fclean all