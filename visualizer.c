/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:26:20 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/11 15:26:22 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			attributes_handler(t_vm *vm, int j, int f)
{
	if (vm->map_color[j] == 1)
		f ? wattron(vm->win, COLOR_PAIR(1)) : wattroff(vm->win, COLOR_PAIR(1));
	else if (vm->map_color[j] == 2)
		f ? wattron(vm->win, COLOR_PAIR(2)) : wattroff(vm->win, COLOR_PAIR(2));
	else if (vm->map_color[j] == 3)
		f ? wattron(vm->win, COLOR_PAIR(3)) : wattroff(vm->win, COLOR_PAIR(3));
	else if (vm->map_color[j] == 4)
		f ? wattron(vm->win, COLOR_PAIR(4)) : wattroff(vm->win, COLOR_PAIR(4));
	else if (vm->map_color[j] == 5)
		f ? wattron(vm->win, COLOR_PAIR(5)) : wattroff(vm->win, COLOR_PAIR(5));
	else if (vm->map_color[j] == 6)
		f ? wattron(vm->win, COLOR_PAIR(6)) : wattroff(vm->win, COLOR_PAIR(6));
	else if (vm->map_color[j] == 7)
		f ? wattron(vm->win, COLOR_PAIR(7)) : wattroff(vm->win, COLOR_PAIR(7));
	else if (vm->map_color[j] == 8)
		f ? wattron(vm->win, COLOR_PAIR(8)) : wattroff(vm->win, COLOR_PAIR(8));
	else if (vm->map_color[j] == 9)
		f ? wattron(vm->win, COLOR_PAIR(9)) : wattroff(vm->win, COLOR_PAIR(9));
}

void			cursus_print_map(t_vm *vm, int j)
{
	int			x;
	int			y;
	char		*base;

	x = 2;
	y = 1;
	base = "0123456789abcdef";
	refresh_map_color(vm);
	while (j < MEM_SIZE)
	{
		if (j != 0 && j % 64 == 0)
		{
			x = 2;
			y++;
		}
		attributes_handler(vm, j, 1);
		mvwaddch(vm->win, y, ++x, base[vm->map[j] / 16]);
		mvwaddch(vm->win, y, ++x, base[vm->map[j] % 16]);
		attributes_handler(vm, j, 0);
		j++;
		if (j != 0 && j % 64 != 0)
			mvwaddch(vm->win, y, ++x, ' ');
	}
	wrefresh(vm->win);
}

static void		curses_color_inint(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	init_pair(9, COLOR_BLACK, COLOR_WHITE);
}

void			visualizer(t_vm *vm)
{
	int			win_h;
	int			win_w;
	int			win_start_y;
	int			win_start_x;

	win_h = 66;
	win_w = 66 * 3;
	win_start_x = 0;
	win_start_y = 0;
	initscr();
	noecho();
	raw();
	curses_color_inint();
	vm->win = newwin(win_h, win_w, win_start_y, win_start_x);
	vm->sidebar = newwin(win_h, (win_w / 4), win_start_y, (win_w + 2));
	refresh();
	box(vm->win, 0, 0);
	box(vm->sidebar, 0, 0);
	wprintw(vm->win, "virtual_machine");
	wprintw(vm->sidebar, "simple sidebar");
	cursus_print_map(vm, 0);
	cursus_print_sidebar(vm, 0, 0);
	getch();
}
