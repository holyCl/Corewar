/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:29:41 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/11 15:29:51 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				refresh_map_color(t_vm *vm)
{
	int				i;
	t_pc			*temp;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->map_color[i] >= 5 && vm->map_color[i] <= 8)
			vm->map_color[i] -= 4;
		else if (vm->map_color[i] == 9)
			vm->map_color[i] = 0;
		i++;
	}
	temp = vm->pc_head;
	while (temp)
	{
		if (vm->map_color[temp->cur_pos % MEM_SIZE] >= 1 &&
			vm->map_color[temp->cur_pos % MEM_SIZE] <= 4)
			vm->map_color[temp->cur_pos % MEM_SIZE] += 4;
		else if (vm->map_color[temp->cur_pos % MEM_SIZE] == 0)
			vm->map_color[temp->cur_pos % MEM_SIZE] = 9;
		temp = temp->next;
	}
}

int					cursus_player_introduction(t_vm *vm, unsigned int u)
{
	int				j;
	int				i;
	int				d;
	unsigned char	*s;

	j = 10;
	i = -1;
	while (++i < (int)vm->num_of_players)
	{
		j++;
		wattron(vm->sidebar, COLOR_PAIR(i + 1));
		d = vm->players[i].player_number;
		s = vm->players[i].name;
		mvwprintw(vm->sidebar, j, 1, "Player: %d : %s", d, s);
		j++;
		u = vm->players[i].last_cycle_alive;
		mvwprintw(vm->sidebar, j, 3, "Last live:               %u     ", u);
		j++;
		u = vm->players[i].alives;
		mvwprintw(vm->sidebar, j, 3, "Lives in current period: %u     ", u);
		j += 2;
		wattroff(vm->sidebar, COLOR_PAIR(i + 1));
	}
	return (j);
}

static int			count_processes(t_vm *vm)
{
	int				i;
	t_pc			*temp;

	i = 0;
	temp = vm->pc_head;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void				cursus_print_sidebar(t_vm *vm, unsigned int cycle, int i)
{
	int				j;

	i = count_processes(vm);
	j = 0;
	wattron(vm->sidebar, A_BOLD);
	if (vm->pause_flag == 0)
		mvwprintw(vm->sidebar, j += 1, 10, "RUNNING >");
	else
		mvwprintw(vm->sidebar, j += 1, 10, "PAUSED ||");
	mvwprintw(vm->sidebar, j += 2, 1, "SPEED: %d", 100);
	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE: %d", cycle);
	mvwprintw(vm->sidebar, j += 2, 1, "Processes: %d    ", i);
	j = cursus_player_introduction(vm, 0);
	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE_TO_DIE: %d  ", vm->cycles_to_die);
	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE_DELTA: %d ", CYCLE_DELTA);
	mvwprintw(vm->sidebar, j += 2, 1, "NBR_LIVE: %d ", NBR_LIVE);
	mvwprintw(vm->sidebar, j += 2, 1, "MAX_CHECKS: %d ", MAX_CHECKS);
	wattroff(vm->sidebar, A_BOLD);
	mvwprintw(vm->sidebar, 63, 2, "Press 'SPACE' to start/pause");
	mvwprintw(vm->sidebar, 64, 2, "Press 'ESC' to exit.");
	wrefresh(vm->sidebar);
}
