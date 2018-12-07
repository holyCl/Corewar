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

void 	attributes_handler(t_vm *vm, int j, WINDOW *win, int flag)
{
	if (vm->map_color[j] == 1)
	{
		if (flag == 1)
			wattron(win, COLOR_PAIR(1));
		else if (flag == 0)
			wattroff(win, COLOR_PAIR(1));
	}
	else if (vm->map_color[j] == 2)
	{
		flag ? wattron(win, COLOR_PAIR(2)) : wattroff(win, COLOR_PAIR(2));
	}
	else if (vm->map_color[j] == 3)
	{
		flag ? wattron(win, COLOR_PAIR(3)) : wattroff(win, COLOR_PAIR(3));
	}
	else if (vm->map_color[j] == 4)
	{
		if (flag == 1)
			wattron(win, COLOR_PAIR(4));
		else if (flag == 0)
			wattroff(win, COLOR_PAIR(4));
	}
}
void		print_map(t_vm *vm, WINDOW *win)
{
	int		j;
	int		x;
	int		y;
	char	*base;

	j = 0;
	x = 2;
	y = 1;
	base  = "0123456789abcdef";
	while(j < MEM_SIZE)
	{
		if (j != 0 && j % 64 == 0)
		{
			x = 2;
			y++;
		}
		attributes_handler(vm, j, win, 1);
		mvwaddch(win, y, ++x, base[vm->map[j] / 16]);
		mvwaddch(win, y, ++x, base[vm->map[j] % 16]);
		attributes_handler(vm, j, win, 0);
		j++;
		if (j != 0 && j % 64 != 0)
			mvwaddch(win, y, ++x, ' ');
	}
}

void   visualizer(t_vm *vm)
{
	unsigned int    i;
	WINDOW          *win;

	int    height, width, start_y, start_x;
	height = 66;
	width = 66 * 3;
	start_x = 0;
	start_y = 0;

	initscr();
	// cbreak();
	noecho();
	raw();//or cbreak() ?
	//colors 1 == COLOR_GREEN, 2 == COLOR_BLUE, 3 == COLOR_RED, 4 == COLOR_CYAN ?
	// if (has_colors())
	// {
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);//for 1st champ
		init_pair(2, COLOR_BLUE, COLOR_BLACK);//for 2nd champ
		init_pair(3, COLOR_RED, COLOR_BLACK);//for 3rd champ
		init_pair(4, COLOR_CYAN, COLOR_BLACK);//for 4th champ
	// }
	


	win = newwin(height, width, start_y, start_x);
	refresh();


	box(win, 0, 0);
	wprintw(win, "my_fucking_vm");


	// if (has_colors())
		// wattron(win, COLOR_PAIR(1));
//print map  without colors!
	print_map(vm, win);
	// int j = 0;
	// int x = 3;
	// int y = 1;
	// char	*base = "0123456789abcdef";

	// while(j < MEM_SIZE)
	// {
	// 	if (j != 0 && j % 64 == 0)
	// 	{
	// 		x = 3;
	// 		y++;
	// 	}
	// 	attributes_handler(vm, j, win, 1);
	// 	mvwaddch(win, y, x, base[vm->map[j] / 16]);
	// 	x++;
	// 	mvwaddch(win, y, x, base[vm->map[j] % 16]);
	// 	x++;
	// 	attributes_handler(vm, j, win, 0);
		
	// 	j++;
	// 	if (j != 0 && j % 64 != 0)
	// 	{
	// 		mvwaddch(win, y, x, ' ');
	// 		x++;
	// 	}
	// }

	// // mvwprintw(win, 1, 1, "some_shit");
	// // mvwprintw(win, 2, 2, (char)vm->map[0]);
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
	endwin();
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
