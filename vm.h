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
	//do we need more diff lives ???
}					t_player;

typedef struct		s_pc
{
	unsigned int	carry;
	unsigned int	reg[REG_NUMBER];
	unsigned int	cur_pos;
	unsigned int	player_id;
	unsigned int	command;
	unsigned int	alive;
	int				cycles_to_go;
	struct s_pc		*next;
}					t_pc;

typedef struct		s_vm
{
	unsigned int	num_of_players;
	t_player		players[MAX_PLAYERS];
	// unsigned int	cycle_count;
	unsigned int	dump_flag;
	unsigned int	dump_num;
	t_pc			*pc_head;
	unsigned char	map[MEM_SIZE];
	unsigned int	cycles_to_die;
}					t_vm;

void				parse_all_players(int ac, char **av, t_vm *vm);
void				error_exit(char *str, int fd);
