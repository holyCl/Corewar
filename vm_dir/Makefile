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

NAME = vm

SRCS = vm_src/main.c \
		vm_src/players_parse.c \
		vm_src/parse_position_intro.c \
		vm_src/live_zjmp_aff_operations.c \
		vm_src/ld_operation.c \
		vm_src/ldi_operation.c \
		vm_src/lldi_operation.c \
		vm_src/sti_operation.c \
		vm_src/st_operation.c \
		vm_src/and_operation.c \
		vm_src/or_operation.c \
		vm_src/xor_operation.c \
		vm_src/add_sub_operations.c \
		vm_src/fork_n_lfork_operations.c \
		vm_src/useful_functions.c \
		vm_src/check_n_move.c \
		vm_src/check_pc_lives_n_kill.c \
		vm_src/are_u_ready_for_rumble.c \
		vm_src/dump_end_free_functions.c \
		vm_src/visualizer.c \
		vm_src/visualizer_print.c
		

OBJ =	$(SRCS:%.c=%.o)

CORE_DIR = ../

FLAGS = -Wall -Wextra -Werror 

HEADER = vm.h

# Colors constants
include ../Colors.mk

all: $(NAME)

%.o:%.c
	@gcc -I. $(FLAGS) -g -c $< -o $@ 

$(NAME): $(OBJ) $(HEADER)
	@make -C libft
	@gcc $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -lncurses
	@cp $(NAME) $(CORE_DIR)
	@echo "$(GREEN)$(NAME) compilation is done$(RESET)"

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -f libft.a
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all
