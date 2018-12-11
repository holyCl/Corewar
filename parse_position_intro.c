/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_position_intro.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:25:39 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/05 21:25:53 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			number(char **av, t_vm *vm, int *i, unsigned int *num)
{
	int				pl_num;
	int				j;

	(*i)++;
	pl_num = ft_atoi(av[(*i)]);
	j = -1;
	while (++j < (int)(*num))
	{
		if (vm->pl_numbers[j] == (pl_num * (-1)))
			error_exit("Error!\nSame champ numbers.\n", -1);
	}
	if (ft_strstr(av[(*i) + 1], ".cor"))
	{
		(*num)++;
		if ((*num) <= 4)
		{
			(*i)++;
			parse_pl(av[(*i)], vm, (*num), pl_num);
		}
		else
			error_exit("Too many players\n", -1);
	}
	else
		error_exit("Usage!", -1);
}

static void			check_num(char **av, t_vm *vm, int *i, unsigned int *num)
{
	(*num)++;
	if ((*num) <= 4)
		parse_pl(av[(*i)], vm, (*num), 0);
	else
		error_exit("Too many players\n", -1);
}

static void			dump_helper(char **av, t_vm *vm, int *i)
{
	vm->dump_flag = 1;
	(*i)++;
	vm->dump_num = ft_atoi(av[(*i)]);
}

void				parse_arguments(int ac, char **av, t_vm *vm)
{
	unsigned int	count_players;
	int				i;

	count_players = 0;
	i = 0;
	while (++i < ac)
	{
		if (ft_strstr(av[i], ".cor"))
			check_num(av, vm, &i, &count_players);
		else if (ft_strcmp(av[i], "-dump") == 0 && vm->dump_flag == 0 &&
			vm->visual_flag == 0)
			dump_helper(av, vm, &i);
		else if (ft_strcmp(av[i], "-n") == 0 && av[i + 1] && av[i + 2])
			number(av, vm, &i, &count_players);
		else if (ft_strcmp(av[i], "-visual") == 0 && vm->dump_flag == 0 &&
			vm->visual_flag == 0)
			vm->visual_flag = 1;
		else
			error_exit("Usage!", -1);
	}
	if (count_players > 4)
		error_exit("Too many players\n", -1);
	else
		vm->num_of_players = count_players;
}

void				position_players(t_vm *vm, unsigned int j)
{
	unsigned int	space;
	int				count_players;
	unsigned int	i;
	t_pc			*tmp_head;

	tmp_head = vm->pc_head;
	space = MEM_SIZE / vm->num_of_players;
	count_players = -1;
	i = 0;
	while (++count_players < (int)vm->num_of_players)
	{
		j = 0;
		tmp_head = NULL;
		tmp_head = create_pc(vm, &vm->players[count_players], (i));
		while (j < vm->players[count_players].size)
		{
			vm->map[i] = vm->players[count_players].exec_code[j];
			vm->map_color[i] = tmp_head->color;
			j++;
			i++;
		}
		i = space * (count_players + 1);
	}
}
