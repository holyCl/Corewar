/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_end_free_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:54:59 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/06 13:55:18 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				free_vm(t_vm *vm)
{
	unsigned int	i;
	t_pc			*tmp;
	t_pc			*del;

	i = 0;
	if (vm->visual_flag)
	{
		endwin();
	}
	while (i < vm->num_of_players)
	{
		free(vm->players[i].exec_code);
		i++;
	}
	tmp = vm->pc_head;
	while (tmp)
	{
		del = tmp->next;
		free(tmp);
		tmp = del;
	}
}

static void			clear_vis_n_end(t_vm *vm)
{
	delwin(vm->win);
	delwin(vm->sidebar);
	endwin();
	free_vm(vm);
	exit(0);
}

static void			print_winner(t_vm *vm, unsigned char *s)
{
	int				c;

	wattron(vm->sidebar, A_BOLD);
	mvwprintw(vm->sidebar, 45, 1, "The winner is: %s", s);
	wrefresh(vm->sidebar);
	wattroff(vm->sidebar, A_BOLD);
	c = getch();
	nodelay(stdscr, false);
	if (c == 27)
		clear_vis_n_end(vm);
}

void				end_this_game(t_vm *vm)
{
	int				last_id;
	int				d;
	unsigned char	*s;

	last_id = vm->last_player_alive_id;
	d = vm->players[last_id].player_number * (-1);
	s = vm->players[last_id].name;
	if (vm->visual_flag == 1)
		system("afplay vm_dir/vm_scr/music/best.mp3");
	if (vm->visual_flag == 1)
	{
		print_winner(vm, s);
	}
	else
	{
		ft_printf("Contestant %d, \"%s\", has won !\n", d, s);
		free_vm(vm);
		exit(0);
	}
}

void				write_cur_map(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("0x0000 : ");
		if (i != 0 && i % 64 == 0)
			ft_printf("\n0x%04x : ", i);
		if (vm->map[i])
			ft_printf("%02x ", vm->map[i]);
		else
			write(1, "00 ", 3);
		i++;
	}
	write(1, "\n", 1);
	free_vm(vm);
	exit(0);
}
