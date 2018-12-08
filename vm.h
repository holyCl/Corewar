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
#include <curses.h>
#include <math.h>


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
	unsigned int	invalid_cm_flag;
	//for color handle
	unsigned char	color;
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
	unsigned char	map_color[MEM_SIZE];
	int				cycles_to_die;
	unsigned int	max_checks;
	unsigned int	last_player_alive_id;
	unsigned int	visual_flag;
	WINDOW			*win;
	WINDOW			*sidebar;
	int				pl_numbers[4];
}					t_vm;

void				parse_pl(char *av, t_vm *vm, unsigned int id, int pl_num);
void				parse_arguments(int ac, char **av, t_vm *vm);
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
void				decodage_opcode(unsigned char codage, int *array, int max);
void 				ft_bzero_int_arr(int *args_array, const int max);
void				live_op(t_vm *vm, t_pc *process, unsigned int cycles_count);
void				zjmp_op(t_vm *vm, t_pc *process);
void				aff_op(t_vm *vm, t_pc *process);
t_pc				*create_pc(t_vm *vm, t_player *player, unsigned int position);
void				position_players(t_vm *vm);
void				players_intro(t_vm *vm);
void				pc_list_checker(t_vm *vm, unsigned int cycles_count);
void				error_exit(char *str, int fd);
void				zero_all_alives_screams(t_vm *vm);
int					check_players_pc_lives(t_vm *vm);
void				free_vm(t_vm *vm);
void				end_this_game(t_vm *vm);
void				write_cur_map(t_vm *vm);
void				are_u_ready_for_rumble(t_vm *vm);

void			cursus_print_map(t_vm *vm);
