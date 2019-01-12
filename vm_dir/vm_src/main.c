/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:37:45 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/17 12:38:00 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				error_exit(char *str, int fd)
{
	if (ft_strcmp("Usage!", str) == 0)
	{
		ft_printf("Usage:\n./corewar [-dump nbr_cycles] ");
		ft_printf("[[-n number] champion1.cor] [-visual]...\n");
	}
	else if (ft_strcmp("Too many!", str) == 0)
		ft_printf("Too many players\n");
	else if (str)
		write(1, str, ft_strlen(str));
	if (fd >= 0)
		close(fd);
	exit(0);
}

void				players_intro(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->num_of_players)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				vm->players[i].player_number * (-1), vm->players[i].size,
				vm->players[i].name, vm->players[i].comment);
		i++;
	}
}

void				vm_init(t_vm *vm)
{
	int				i;

	i = 0;
	ft_bzero(vm, sizeof(t_vm));
	ft_bzero_int_arr(vm->pl_numbers, 4);
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->pause_flag = 1;
	vm->speed = 1000;
	while (i < MAX_PLAYERS)
	{
		vm->players_order[i] = i;
		i++;
	}
}

int					main(int ac, char **av)
{
	t_vm			*vm;

	vm = (t_vm *)malloc(sizeof(t_vm));
	vm_init(vm);
	if (ac > 1)
		parse_arguments(ac, av, vm);
	else
	{
		free_vm(vm);
		error_exit("Usage!", -1);
	}
	position_players(vm, 0);
	if (vm->num_of_players > 4)
		vm->visual_flag = 0;
	if (vm->visual_flag)
	{
		visualizer(vm);
		system("afplay vm_dir/vm_src/music/Rumble.mp3");
	}
	else
		players_intro(vm);
	are_u_ready_for_rumble(vm, 0);
	free_vm(vm);
	return (0);
}
