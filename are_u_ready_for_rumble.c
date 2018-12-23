/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_u_ready_for_rumble.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:52:55 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/06 13:53:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			clear_vis_n_end(t_vm *vm)
{
	delwin(vm->win);
	delwin(vm->sidebar);
	endwin();
	free_vm(vm);
	exit(0);
}

static void			rumble_visual_handler(t_vm *vm, unsigned int cycles)
{
	int				c;

	c = getch();
	if (c == 32)
	{
		if (vm->pause_flag)
		{
			vm->pause_flag = 0;
			nodelay(stdscr, true);
		}
		else
		{
			vm->pause_flag = 1;
			nodelay(stdscr, false);
		}
	}
	else if (c == 27)
	{
		clear_vis_n_end(vm);
	}
	cursus_print_map(vm, 0);
	cursus_print_sidebar(vm, cycles, 0);
	usleep(vm->speed);
}

static void			game_checker(t_vm *vm, unsigned int *cycle_to_check)
{
	if (check_players_pc_lives(vm))
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		zero_all_alives_screams(vm);
		vm->max_checks = 0;
		(*cycle_to_check) += vm->cycles_to_die;
	}
	else if (vm->max_checks == 10)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		zero_all_alives_screams(vm);
		vm->max_checks = 0;
		(*cycle_to_check) += vm->cycles_to_die;
	}
	else
	{
		vm->max_checks++;
		zero_all_alives_screams(vm);
		(*cycle_to_check) += vm->cycles_to_die;
	}
}

void				are_u_ready_for_rumble(t_vm *vm, unsigned int cur_cycle)
{
	unsigned int	cycle_to_check;

	cycle_to_check = vm->cycles_to_die;
	while (1)
	{
		if ((vm->cycles_to_die <= 0) || vm->pc_head == NULL)
			end_this_game(vm);
		pc_list_checker(vm, cur_cycle);
		if (cur_cycle == cycle_to_check)
			game_checker(vm, &cycle_to_check);
		if (vm->dump_flag == 1 && vm->dump_num <= cur_cycle)
			write_cur_map(vm);
		if (vm->visual_flag == 1)
			rumble_visual_handler(vm, cur_cycle);
		cur_cycle++;
	}
}
