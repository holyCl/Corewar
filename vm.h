/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:30:02 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/17 12:33:16 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

#include <fcntl.h>
#include "op.h"
// #include <>
// #include <>

typedef struct		s_player
{
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned int	size;
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	*exec_code;
	unsigned int	id;
	int				player_number;
	unsigned int	alives;
	unsigned int	last_cycle_alive;
}					t_player;

typedef struct		s_pc
{
	unsigned int	carry;
	unsigned int	reg[REG_NUMBER];
	unsigned int	cur_pos;
	unsigned int	player_id;
	 unsigned int	command;
	unsigned int	alive_bool;
	unsigned int	alive_screams;
	unsigned int	forked;
	int				cycles_to_go;
	unsigned int	pc_number;
	unsigned int    invalid_cm_flag;
	//for color handle
    unsigned char   color;
	struct s_pc		*next;
    struct s_pc		*prev;
}					t_pc;


typedef struct		s_vm
{
	unsigned int	num_of_players;
	t_player		players[MAX_PLAYERS];
	unsigned int	dump_flag;
	unsigned int	dump_num;
	t_pc			*pc_head;
	unsigned char	map[MEM_SIZE];
	unsigned char   map_color[MEM_SIZE];
	int				cycles_to_die;
	unsigned int	max_checks;
	unsigned int	last_player_alive_id;
}					t_vm;

void				parse_all_players(int ac, char **av, t_vm *vm);
void				error_exit(char *str, int fd);
void				st_op(t_vm *vm, t_pc *process);
void				sti_op(t_vm *vm, t_pc *process);
void				add_op(t_vm *vm, t_pc *process);
void				sub_op(t_vm *vm, t_pc *process);
void				and_op(t_vm *vm, t_pc *process);
void				or_op(t_vm *vm, t_pc *process);
void				xor_op(t_vm *vm, t_pc *process);
void				ld_op(t_vm *vm, t_pc *process);
void				lld_op(t_vm *vm, t_pc *process);
void				ldi_op(t_vm *vm, t_pc *process);
void				lldi_op(t_vm *vm, t_pc *process);
void				fork_op(t_vm *vm, t_pc *process);
void				lfork_op(t_vm *vm, t_pc *process);
unsigned int		get_arguments(t_vm *vm, unsigned int *cur_pos, int label);
void				decodage_opcode(unsigned char codage, int *args_array, unsigned int max_args);
void 				ft_bzero_int_arr(int *args_array, const int max);
