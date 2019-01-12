# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazarin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 17:03:30 by inazarin          #+#    #+#              #
#    Updated: 2017/11/11 21:23:51 by inazarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putchar.c ft_strlen.c ft_strcmp.c ft_strdup.c \
	   ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
	   ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	   ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
	   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_toupper.c ft_tolower.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	   ft_memcmp.c ft_memalloc.c ft_memdel.c ft_strnew.c \
	   ft_itoa.c ft_strdel.c ft_strclr.c ft_striter.c \
	   ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	   ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	   ft_strsplit.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	   ft_putnbr_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	   ft_lstiter.c ft_lstmap.c ft_swap.c ft_isupper.c \
	   ft_islower.c ft_isws.c ft_isgraph.c \
	   get_next_line.c \
	   ft_d_write.c \
	   ft_h_big_write.c \
	   ft_h_write.c \
	   ft_handle_func.c \
	   ft_handlers.c \
	   ft_hh_write.c \
	   ft_itoas.c \
	   ft_itoa4.c \
	   ft_itoas2.c \
	   ft_itoas3.c \
	   ft_l_write.c \
	   ft_ll_write.c \
	   ft_long_handlers.c \
	   ft_parser.c \
	   ft_precision.c \
	   ft_printf.c \
	   ft_sc_write.c \
	   ft_uni_write.c \
	   ft_unistr.c \
	   ft_width.c \
	   ft_x_o_write.c \
	   ft_z_write.c \
	   write_helpers.c \



OBJ =	$(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c libft.h
	@gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) libft.h
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
