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
	wprintw(vm->win, "my_fucking_vm");
	wprintw(vm->sidebar, "simple sidebar");
	cursus_print_map(vm, 0);
	cursus_print_sidebar(vm, 0, 0);
	getch();
}
