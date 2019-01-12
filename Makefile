NAME = core

ASM_NAME = asm

VM_NAME = corewar

ASM_DIR = asm_dir/

VM_DIR = vm_dir/

all: $(NAME)

# Colors constants
include Colors.mk 

$(NAME):
	@make -C $(ASM_DIR)
	@make -C $(VM_DIR)
	@echo "$(BLUE)usage:$(RESET) ./$(ASM_NAME) champs/[champ_name].s"
	@echo "       ./$(VM_NAME) champs/[champ_name].cor"

clean:
	@make clean -C $(ASM_DIR)
	@make clean -C $(VM_DIR)
	@echo "$(YELLOW)object files have been cleaned$(RESET)"

fclean: clean
	@make fclean -C $(ASM_DIR)
	@make fclean -C $(VM_DIR)
	@/bin/rm -f $(ASM_NAME) $(VM_NAME)

re: fclean all
