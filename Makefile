# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 04:27:00 by mmousson          #+#    #+#              #
#    Updated: 2018/12/11 05:05:20 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC 			?= gcc
CFLAGS		?= -Wall -Wextra -Werror
CPPFLAGS	= -I./includes -I./libftprintf/includes -I./libftprintf/libft/includes

SRCS =	./src/ft_ls.c \
		./src/get_files.c \
		./src/get_options.c \
		./src/main.c \
		./src/annex.c \
		./src/ft_nblen.c \
		./src/ft_strmode.c \
		./src/print_long_format.c \
		./src/ft_reverse.c \
		./src/ft_swap.c \
		./src/sorting.c \
		./src/fill_max.c \
		./src/miscellaneous.c

LIBFTPRINTF_PATH = libftprintf/libftprintf.a

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libftprintf/
	$(CC) $(OBJ) -o $(NAME) $(LIBFTPRINTF_PATH)
	
%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	@$(MAKE) -C libftprintf clean
	rm -rf $(OBJ)

fclean: clean
	@$(MAKE) -C libftprintf fclean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS = -g
debug: re

.PHONY: all clean fclean re
