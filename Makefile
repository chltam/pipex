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
BONUS := pipex_bonus
CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDE := ./libft/libft.a
SRCS := pipex.c get_path.c
SRCS_BONUS := pipex_bonus.c get_path.c

$(NAME) : $(SRCS)
	@make -C libft
	@echo "\033[0;92mPipex\033[0;39m"
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE) -o $(NAME)

$(BONUS) : $(SRCS_BONUS)
	@make -C libft
	@echo "\033[0;92mPipex bonus\033[0;39m"
	$(CC) $(SRCS_BONUS) $(INCLUDE) -o $(BONUS)

all: $(NAME)

bonus: $(BONUS)

clean:
	rm -rf $(NAME)

fclean:
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(BONUS)

re:fclean all