NAME = corewar

ASM_NAME = asm

VM_NAME = vm

ASM_DIR = asm_dir/

VM_DIR = vm_dir/

all: $(NAME)

# Colors constants
include Colors.mk 

$(NAME):
	@make -C $(ASM_DIR)
	@make -C $(VM_DIR)
	@echo "$(GREEN)$(NAME) compilation is done$(RESET)"
	@echo "$(BLUE)usage:$(RESET) ./$(NAME) champ.s"

clean:
	@make clean -C $(ASM_DIR)
	@make clean -C $(VM_DIR)
	@echo "$(YELLOW)object files have been cleaned$(RESET)"

fclean: clean
	@make fclean -C $(ASM_DIR)
	@make fclean -C $(VM_DIR)
	@/bin/rm -f $(ASM_NAME) $(VM_NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all
