# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazarin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 12:34:25 by inazarin          #+#    #+#              #
#    Updated: 2018/10/17 12:34:30 by inazarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRCS = main.c \
		players_parse.c \
		parse_position_intro.c \
		live_zjmp_aff_operations.c \
		ld_operation.c \
		ldi_operation.c \
		lldi_operation.c \
		sti_operation.c \
		st_operation.c \
		and_operation.c \
		or_operation.c \
		xor_operation.c \
		add_sub_operations.c \
		fork_n_lfork_operations.c \
		useful_functions.c \
		check_n_move.c \
		check_pc_lives_n_kill.c \
		are_u_ready_for_rumble.c \
		dump_end_free_functions.c \
		visualizer.c \
		visualizer_print.c
		

OBJ =	$(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror 

HEADER = vm.h



all: $(NAME)

%.o:%.c
	gcc -I. $(FLAGS) -g -c $< -o $@ 

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	gcc $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -lncurses

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f libft.a
	rm -f $(NAME)

re: fclean all
