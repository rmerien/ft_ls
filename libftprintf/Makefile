# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/05 17:26:49 by mmousson          #+#    #+#              #
#    Updated: 2018/12/09 11:21:47 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftprintf.a
CFLAGS = -Wextra -Wall -Werror -I./includes -I./libft/includes

SRC_LIBFT =	./libft/ft_memset.c \
			./libft/ft_bzero.c \
			./libft/ft_memcpy.c \
			./libft/ft_memccpy.c \
			./libft/ft_strlen.c \
			./libft/ft_memchr.c \
			./libft/ft_memcmp.c \
			./libft/ft_memmove.c \
			./libft/ft_strdup.c \
			./libft/ft_strcpy.c \
			./libft/ft_strncpy.c \
			./libft/ft_strcat.c \
			./libft/ft_strncat.c \
			./libft/ft_strlcat.c \
			./libft/ft_strchr.c \
			./libft/ft_strrchr.c \
			./libft/ft_strstr.c \
			./libft/ft_strrstr.c \
			./libft/ft_strnstr.c \
			./libft/ft_strcmp.c \
			./libft/ft_strncmp.c \
			./libft/ft_atoi.c \
			./libft/ft_isalpha.c \
			./libft/ft_isdigit.c \
			./libft/ft_isalnum.c \
			./libft/ft_isascii.c \
			./libft/ft_isprint.c \
			./libft/ft_putchar.c \
			./libft/ft_toupper.c \
			./libft/ft_tolower.c \
			./libft/ft_putstr.c \
			./libft/ft_putendl.c \
			./libft/ft_putnbr.c \
			./libft/ft_memalloc.c \
			./libft/ft_memdel.c \
			./libft/ft_strnew.c \
			./libft/ft_strdel.c \
			./libft/ft_strclr.c \
			./libft/ft_striter.c \
			./libft/ft_striteri.c \
			./libft/ft_strmap.c \
			./libft/ft_strmapi.c \
			./libft/ft_strequ.c \
			./libft/ft_strnequ.c \
			./libft/ft_strsub.c \
			./libft/ft_strjoin.c \
			./libft/ft_strtrim.c \
			./libft/ft_strsplit.c \
			./libft/ft_itoa.c \
			./libft/ft_putchar_fd.c \
			./libft/ft_putstr_fd.c \
			./libft/ft_putendl_fd.c \
			./libft/ft_putnbr_fd.c \
			./libft/ft_lstnew.c \
			./libft/ft_lstdelone.c \
			./libft/ft_lstdel.c \
			./libft/ft_lstadd.c \
			./libft/ft_lstiter.c \
			./libft/ft_lstmap.c \
			./libft/ft_rotate_left.c \
			./libft/ft_stradd.c \
			./libft/ft_strmultiply.c \
			./libft/ft_putllong.c \
			./libft/ft_putfloat.c \
			./libft/ft_min.c \
			./libft/ft_max.c \
			./libft/ft_abs.c \
			./libft/ft_clamp.c \
			./libft/ft_strdivide_two.c

SRCS =		./src/attributes.c \
			./src/dispatcher.c \
			./src/flags_conversions.c \
			./src/ft_int_aux.c \
			./src/ft_int.c \
			./src/ft_octal.c \
			./src/ft_octal_aux.c \
			./src/ft_printf.c \
			./src/ft_put_pointer.c \
			./src/put_hexa_aux.c \
			./src/put_hexa.c \
			./src/putchar.c \
			./src/putfloat.c \
			./src/putfloat_aux.c \
			./src/putfloat_main.c \
			./src/putstr.c \
			./src/unsigned_int_aux.c \
			./src/unsigned_int.c \
			./src/magnitude.c

OBJS = $(SRCS:.c=.o)
OBJS_LIBFT = $(SRC_LIBFT:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(OBJS_LIBFT)
	ar rc $(NAME) $(OBJS) $(OBJS_LIBFT)
	ranlib $(NAME)

clean :
	rm -rf $(OBJS) $(OBJS_LIBFT)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
