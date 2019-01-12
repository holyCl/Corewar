# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 18:35:56 by akorzhak          #+#    #+#              #
#    Updated: 2018/01/13 18:35:58 by akorzhak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

C = gcc

CFLAG = -Wall -Wextra -Werror #-fsanitize=address

INC = -I ./includes -I ./ft_printf/includes

PRINTF_DIR = ft_printf/

PRINTF = $(PRINTF_DIR)libftprintf.a

LIBS = -L ./ft_printf -lftprintf

SRC_DIR = src/

ASM_DIR = $(SRC_DIR)asm/

CONTROLLER_DIR = $(ASM_DIR)controller/

VIEW_DIR = $(ASM_DIR)view/

MODEL_DIR = $(ASM_DIR)model/

OBJ_DIR = obj/

SRC = main.c init.c op.c read.c handle_read_data.c\
	find_labels_addresses.c util.c messages.c\
	validate.c free.c

OBJ = $(SRC:.c=.o)

# Colors constants
include Colors.mk

.PHONY: all clean fclean

%.o: $(CONTROLLER_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(MODEL_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(VIEW_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTF_DIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(GREEN)$(NAME) compilation is done$(RESET)"
	@echo "$(BLUE)usage:$(RESET) ./$(NAME) champ.s"

clean:
	@make clean -C $(PRINTF_DIR)
	@/bin/rm -f $(OBJ) *~
	@echo "$(YELLOW)object files have been cleaned$(RESET)"

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	@/bin/rm -f $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all
