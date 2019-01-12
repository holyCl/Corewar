NAME = corewar

ASM_DIR = asm/

VM_DIR = vm/

all: $(NAME)

$(NAME):
	@make -C $(ASM_DIR)
	@make -C $(VM_DIR)
	@echo "$(NAME) compilation is done"
	@echo "usage:"

clean:
	@make clean -C $(ASM_DIR)
	@make clean -C $(VM_DIR)
	@echo "object files have been cleaned"

fclean: clean
	@make fclean -C $(ASM_DIR)
	@make fclean -C $(VM_DIR)
	@echo "$(NAME) has been removed"

re: fclean all
