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
/*
 *
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
*/


void   visualizer(t_vm *vm)
{
    unsigned int    i;
    WINDOW          *win;

    int    height, width, start_y, start_x;
    height = 20;
    width = 20;
    start_x = 10;
    start_y = 10;

    initscr();

    win = newwin(height, width, start_y, start_x);
    refresh();

    box(win, 0, 0);
    wprintw(win, "my_fucking_vm");
    mvwprintw(win, 2, 2, "some_shit");
    wrefresh(win);
    i = 0;
    i = vm->visual_flag;
    // while (i < MEM_SIZE)
    // {
    //     // if (i != 0 && i % 64 == 0)
    //     //     printw("\n", i);
    //     if (vm->map[i] && i != 0 && i % 64 == 0)
    //         printw("%02x\n", vm->map[i]);
    //     else
    //         printw("%02x", vm->map[i]);
    //     i++;
    // }
    // printw("\n");
    getch();
    // usleep(50);
}

void				vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	ft_bzero_int_arr(vm->pl_numbers, 4);
	vm->cycles_to_die = CYCLE_TO_DIE;
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
		error_exit("fucked up! please check your arguments\n", -1);
	}
	position_players(vm);
	players_intro(vm);
	if (vm->visual_flag)
    {
        visualizer(vm);
    }
	are_u_ready_for_rumble(vm);
	free_vm(vm);
	// system("leaks my_vm");
	return (0);
}
