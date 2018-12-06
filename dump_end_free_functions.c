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

    i = 0;
    while (i < vm->num_of_players)
    {
        free(vm->players[i].exec_code);
        i++;
    }
    while (vm->pc_head)
    {
        tmp = vm->pc_head->next;
        free(vm->pc_head);
        vm->pc_head = tmp;
    }
}

void				end_this_game(t_vm *vm)
{
    int				last_id;
    int				d;
    unsigned char	*s;

    last_id = vm->last_player_alive_id;
    d = vm->players[last_id].player_number * (-1);
    s = vm->players[last_id].name;
    write(1, "Contestant ", ft_strlen("Contestant "));
    write(1, ft_itoa(d), ft_strlen(ft_itoa(d)));
    write(1, ", ", 2);
    write(1, "\"", 1);
    write(1, s, ft_strlen((char *)s));
    write(1, "\"", 1);
    write(1, ", has won !", ft_strlen(", has won !"));
    write(1, "\n", 1);
    free_vm(vm);
    exit(0);
}

void				write_cur_map(t_vm *vm)
{
    unsigned int 	i;

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
}
