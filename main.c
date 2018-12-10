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

/* start visual */


void	finish_curses(t_vm *vm, int d, unsigned char *s)
{
	int c;

	c = getch();
	mvwprintw(vm->sidebar, 35, 3, "Contestant %d, \"%s\", has won !\n", d, s);
	nodelay(stdscr, true);
	if (c == 27)
	{
		delwin(vm->win);
		delwin(vm->sidebar);
		endwin();
		free_vm(vm);
		exit(0);
	}
	else
		usleep(30000);
	
}

static void		attributes_handler(t_vm *vm, int j, int f)
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

void		refresh_map_color(t_vm *vm)
{
	int		i;
	t_pc	*temp;

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

void			cursus_print_map(t_vm *vm, int j)
{
	int			x;
	int			y;
	char		*base;

	x = 2;
	y = 1;
	base  = "0123456789abcdef";
	refresh_map_color(vm);
	while(j < MEM_SIZE)
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

int				cursus_player_introduction(t_vm *vm)//color undone
{
	int			j;
	int			i;

	j = 10;
	i = -1;
	while (++i < (int)vm->num_of_players)
	{
		
		j++;
		wattron(vm->sidebar, COLOR_PAIR(i + 1));
		mvwprintw(vm->sidebar, j, 1, "Player: %d : %s", vm->players[i].player_number, vm->players[i].name);
		j++;
		mvwprintw(vm->sidebar, j, 3, "Last live:               %u", vm->players[i].last_cycle_alive);
		j++;
		mvwprintw(vm->sidebar, j, 3, "Lives in current period: %u", vm->players[i].alives);
		j += 2;
		wattroff(vm->sidebar, COLOR_PAIR(i + 1));
	}
	return (j);
}

void			cursus_print_sidebar(t_vm *vm, unsigned int cycle)
{
	int			j;
	t_pc	*temp = vm->pc_head;
	int i = 0;

	while (temp)
	{
	    i++;
	    temp = temp->next;
	}

	j = 0;
	wattron(vm->sidebar, A_BOLD);
	// mvwaddstr(vm->sidebar, 3, 1, "SPEED:");

	if (vm->pause_flag == 0)
		mvwprintw(vm->sidebar, j += 1, 1, "RUNNING >");
	else
		mvwprintw(vm->sidebar, j += 1, 1, "PAUSED ||");
	mvwprintw(vm->sidebar, j += 2, 1, "SPEED: %d", 100);
	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE: %d", cycle);
	mvwprintw(vm->sidebar, j += 2, 1, "Processes: %d", i);

	j = cursus_player_introduction(vm);

	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE_TO_DIE: %d", vm->cycles_to_die);
	mvwprintw(vm->sidebar, j += 2, 1, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(vm->sidebar, j += 2, 1, "NBR_LIVE: %d", NBR_LIVE);
	mvwprintw(vm->sidebar, j += 2, 1, "MAX_CHECKS: %d", MAX_CHECKS);	

	wattroff(vm->sidebar, A_BOLD);
	wrefresh(vm->sidebar);
}

void   visualizer(t_vm *vm)
{
	int    win_h, win_w, win_start_y, win_start_x;
	win_h = 66;
	win_w = 66 * 3;
	win_start_x = 0;
	win_start_y = 0;


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
		init_pair(5, COLOR_BLACK, COLOR_GREEN);//for 1st champ pc`s
		init_pair(6, COLOR_BLACK, COLOR_BLUE);//for 2nd champ pc`s
		init_pair(7, COLOR_BLACK, COLOR_RED);//for 3rd champ pc`s
		init_pair(8, COLOR_BLACK, COLOR_CYAN);//for 4th champ pc`s
		init_pair(9, COLOR_BLACK, COLOR_WHITE);//for zero position
	// }
	

	vm->win = newwin(win_h, win_w, win_start_y, win_start_x);
	vm->sidebar = newwin(win_h, (win_w / 4), win_start_y, (win_w + 2));//was (win_h / 3)
	refresh();


	box(vm->win, 0, 0);
	box(vm->sidebar, 0, 0);
	wprintw(vm->win, "my_fucking_vm");
	wprintw(vm->sidebar, "simple sidebar");

//prints map
	cursus_print_map(vm, 0);
//prints sidebar
	cursus_print_sidebar(vm, 0);
	getch();
	// usleep(50);
	// endwin();
}

/* *** end visual *** */

void				vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	ft_bzero_int_arr(vm->pl_numbers, 4);
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->pause_flag = 1;
	vm->speed = 1000;
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
	