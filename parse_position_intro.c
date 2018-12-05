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

void				parse_arguments(int ac, char **av, t_vm *vm)
{
    unsigned int	count_players;
    int	pl_num;
    int			i;

    count_players = 0;
    i = 0;
    while (++i < ac)
    {
        if (ft_strstr(av[i], ".cor"))
        {
            count_players++;
            if (count_players <= 4)
                parse_pl(av[i], vm, count_players, 0);
            else
                error_exit("Too many players\n", -1);
        }
        else if (ft_strcmp(av[i], "-dump") == 0 && vm->dump_flag == 0 && vm->visual_flag == 0)
        {
            vm->dump_flag = 1;
            vm->dump_num = ft_atoi(av[++i]);
        }
        else if (ft_strcmp(av[i], "-n") == 0 && av[i + 1] && av[i + 2])
        {
            pl_num = ft_atoi(av[++i]);
            if (ft_strstr(av[i + 1], ".cor"))
            {
                count_players++;
                if (count_players <= 4)
                    parse_pl(av[++i], vm, count_players, pl_num);
                else
                    error_exit("Too many players\n", -1);
            }
            else
                error_exit("Usage!", -1);
        }
        else if (ft_strcmp(av[i], "-v") == 0 && vm->dump_flag == 0 && vm->visual_flag == 0)
        {
            vm->visual_flag = 1;
        }
        else
            error_exit("Usage!", -1);
    }
    if (count_players > 4)
        error_exit("Too many players\n", -1);
    else
        vm->num_of_players = count_players;
}

void				position_players(t_vm *vm)
{
    unsigned int	space;
    int	count_players;
    unsigned int	i;
    unsigned int	j;
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
            //color handle
            vm->map_color[i] = tmp_head->color;
            j++;
            i++;
        }

        i = space * (count_players + 1);
    }
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
