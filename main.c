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

#include <sys/types.h>
#include <sys/uio.h>

void	error_exit(char *str, int fd)
{
	//print msg here!
	if (str)
		write(1, str, ft_strlen(str));
	// ft_printf("%s\n", "Error occured.");
	//free everything here!
	if (fd >= 0)
		close(fd);
	exit(0);
}

//undone must be more strict for arguments!
void			parse_arguments(int ac, char **av, t_vm *vm)
{
	int			count_players;
	int			i;

	count_players = 0;
	i = 0;
	while (++i < ac)
	{
		if (ft_strstr(av[i], ".cor"))//&& ft_strstr(argv[i], ".cor")
			count_players++;
		else if (ft_strcmp(av[i], "-dump") == 0)
		{
			vm->dump_flag = 1;
			vm->dump_num = ft_atoi(av[i + 1]);
		}
		else if (ft_strcmp(av[i], "-n") == 0)
			;
		// if (argv[i] == "-n")
		// 	//sturct vm flag for ncurses = 1;
	}
	vm->num_of_players = count_players;
}

t_pc				*create_new_pc(t_vm *vm, t_player *player, unsigned int position)
{
	t_pc			*new_node;

	new_node = (t_pc *)malloc(sizeof(t_pc));
	if (!new_node)
		error_exit("Error during creating new process", -1);
	ft_bzero(new_node, sizeof(t_pc));
	ft_bzero(new_node->reg, REG_NUMBER);
	new_node->reg[0] = player->player_number;
	new_node->player_id = player->id;
	new_node->cur_pos = position;
	new_node->cycles_to_go = -1;
	new_node->alive_bool = 1;
	if (vm->pc_head)
		new_node->next = vm->pc_head;
	vm->pc_head = new_node;
	return (new_node);
}

void				position_players(t_vm *vm)
{
	unsigned int	space;
	unsigned int	count_players;
	unsigned int	i;
	unsigned int	j;
	t_pc			*tmp_head;
	// t_pc			*new_pc;

	tmp_head = vm->pc_head;
	// new_pc = vm->pc_head;
	space = MEM_SIZE / vm->num_of_players;
	count_players = -1;
	i = -1;
	while (++count_players < vm->num_of_players)
	{
		j = -1;
		tmp_head = NULL;
		tmp_head = create_new_pc(vm, &vm->players[count_players], (i + 1));

		//was before --- with reverse order
		// if (new_pc == NULL)
		// 	new_pc = create_new_pc(vm, vm->players[count_players].id, (i + 1));
		// else
		// {
		// 	new_pc->next = create_new_pc(vm, vm->players[count_players].id, (i + 1));
		// 	new_pc = new_pc->next;
		// }
		while (++j < vm->players[count_players].size)
			vm->map[++i] = vm->players[count_players].exec_code[j];
		i += space;
	}
}

void				free_vm(t_vm *vm)
{
	unsigned int	i;
	t_pc			*tmp;

	i = 0;
	while (i < vm->num_of_players)//vm->players[i] && 
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

void				vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
}

unsigned int		get_arguments(t_vm *vm, unsigned int *cur_pos, int label)
{
	unsigned int	ret;

	ret = 0;
	if (label == 1)
		ret = vm->map[++(*cur_pos) % MEM_SIZE];
	else if (label == 2)
		ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 8) | vm->map[++(*cur_pos) % MEM_SIZE];
	else if (label == 4)
	{
		ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 24) | (vm->map[++(*cur_pos) % MEM_SIZE] << 16) | 
		(vm->map[++(*cur_pos) % MEM_SIZE] << 8) | (vm->map[++(*cur_pos) % MEM_SIZE]);
	}
	return (ret);
}

void				decodage_opcode(unsigned char codage, int *args_array, unsigned int max_args)
{
	unsigned char	check;
	unsigned int	i;

	i = 0;
	while (codage && i < max_args)
	{
		check = codage & 192;
		if (check == 64)
			args_array[i] = REG_CODE;
		else if (check == 128)
			args_array[i] = DIR_CODE;
		else if (check == 192)
			args_array[i] = IND_CODE;
		codage <<= 2;
		i++;
	}
	// printf("%d\n", args_array[0]);
	// printf("%d\n", args_array[1]);
	// printf("%d\n", args_array[2]);
}

void				live_op(t_vm *vm, t_pc *process, unsigned int cycles_count)//“A process shows that player X (champion_name) is alive"
{
	unsigned int	tmp_pos;
	unsigned int	temp;
	unsigned int	check_int;


	tmp_pos = process->cur_pos;
	// decode_args(args_array, codage, max_args);
	process->alive_screams++;
	check_int = vm->players[process->player_id].player_number;
	temp = get_arguments(vm, &tmp_pos, 4);
	// printf("live arg=%u\n", temp);
	if (check_int == temp)
	{

		
		// ft_printf("A process shows that player %d (%s) is alive\n", 
		// 	vm->players[process->player_id].id, vm->players[process->player_id].name);
		vm->players[process->player_id].alives++;
		vm->players[process->player_id].last_cycle_alive = cycles_count;
		vm->last_player_alive_id = process->player_id;


printf("ALive(%u) at %u cycle\n", vm->players[process->player_id].alives, cycles_count);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

void				zjmp_op(t_vm *vm, t_pc *process)
{
	// char			args_array[1];//mb 4 of them ??? or 1
	// unsigned char	codage;
	// unsigned char	check;
	unsigned int	tmp_pos;
	short			check_int;

	tmp_pos = process->cur_pos;
	/****/ 
	//handle cur_pos step!
	// codage = vm->map[++(*cur_pos)];
	// ft_bzero(&args_array, 3);
	// decode_args(args_array, codage, max_args);
	// if (codage)//do we need nulls in other 6 bits?
	// {
	// 	check = codage & 192;
	// 	if (check == 128)
	// 		args_array[0] = DIR_CODE;
	// 	else
	// 		error_exit("Invalid argument type in `zjmp`.\n", -1);
	// }
	// else
	// 	error_exit("Error with codage in zjmp_op\n", -1);
	check_int = (short)get_arguments(vm, &tmp_pos, 2);
	if (process->carry == 1)
	{
		process->cur_pos = (((process->cur_pos + (int)check_int) % MEM_SIZE) % IDX_MOD); //was + tmp_pos
	}
	else
		process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	//what if carry doesnt == 1 - what should we do?
	
	process->cycles_to_go = -1;
}

void				aff_op(t_vm *vm, t_pc *process)
{
	unsigned int	tmp_pos;
	int				opcode;
	unsigned char	ret;

	tmp_pos = process->cur_pos;
	opcode = 0;
	decodage_opcode(vm->map[++tmp_pos], &opcode, 1);
	if (opcode == REG_CODE)
	{
		ret = (unsigned char)get_arguments(vm, &tmp_pos, 1);
		ret = process->reg[ret - 1] % 256;
		if (vm->dump_flag == 0 && ret >= 1 && ret <= 16) //&& no visualization
			ft_printf("%c\n");
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

void				feel_n_fill_pc(t_vm *vm, t_pc *process, unsigned int cycles_count)//just 'zork.cor' for now
{	
	unsigned char	tmp;
	unsigned int	a;

	a = 0;
	tmp = 0;
	tmp = vm->map[process->cur_pos % MEM_SIZE];
	a = tmp;
	if (a == 1)
		live_op(vm, process, cycles_count);
	else if (a == 2)
		ld_op(vm, process);
	else if (a == 3)
		st_op(vm, process);
	else if (a == 4)
		add_op(vm, process);
	else if (a == 5)
		sub_op(vm, process);
	else if (a == 6)
		and_op(vm, process);
	else if (a == 7)
		or_op(vm, process);
	else if (a == 8)
		xor_op(vm, process);
	else if (a == 9)
		zjmp_op(vm,  process);
	else if (a == 10)
		ldi_op(vm, process);
	else if (a == 11)
		sti_op(vm, process);
	else if (a == 12)
		fork_op(vm, process);
	else if (a == 13)
		lld_op(vm, process);
	else if (a == 14)
		lldi_op(vm, process);
	else if (a == 15)
		lfork_op(vm, process);
	else if (a == 16)
		aff_op(vm, process);

	//here would be new get_cycles_to_go() funcrion use!!!!

}

int					get_cycles_to_go(t_vm *vm, t_pc *process)
{
	int				check;
	unsigned char	temp;
	int				ret;

	temp = vm->map[process->cur_pos % MEM_SIZE];
	check = temp;

// printf("check=%u, ", check);

	if (check == 1 || check == 4 || check == 5 || check == 13)
		ret = 10;
	else if (check == 2 || check == 3)
		ret = 5;
	else if (check == 6 || check == 7 || check == 8)
		ret = 6;
	else if (check == 9)
		ret = 20;
	else if (check == 10 || check == 11)
		ret = 25;
	else if (check == 12)
		ret = 800;
	else if (check == 14)
		ret = 50;
	else if (check == 15)
		ret = 1000;
	else if (check == 16)
		ret = 2;
	else
	{
		ret = 0;
		process->cur_pos = (process->cur_pos + 1) % MEM_SIZE;
	}

// printf("will wait=%d\n", ret);

	return (ret - 1);
}

void				pc_list_checker(t_vm *vm, unsigned int cycles_count)
{
	t_pc			*pointer;

	pointer = vm->pc_head;
	while (pointer)
	{
		if (pointer->alive_bool == 1)
		{
			if (pointer->cycles_to_go < 0)
				pointer->cycles_to_go = get_cycles_to_go(vm, pointer);
			else if (pointer->cycles_to_go > 0)
				pointer->cycles_to_go--;
			else if (pointer->cycles_to_go == 0)//was else if
			{
				feel_n_fill_pc(vm, pointer, cycles_count);
				pointer->cycles_to_go = get_cycles_to_go(vm, pointer);
			}
		}
		//its realy tricky
		pointer = pointer->next;
	}
}

int					check_process_lives(t_pc *pc_head)
{
	t_pc			*temp;

	temp = pc_head;
	while (temp != NULL)
	{
		if (temp->alive_bool)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int					check_players_pc_lives(t_vm *vm)
{
	unsigned int 	i;

	i = 0;
	while (i < vm->num_of_players)
	{
		if (vm->players[i].alives >= NBR_LIVE)
		{
			vm->max_checks = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
void				check_pc_to_die(t_vm *vm)//check it, please cus I changed removing node to flag changing
{
	t_pc			*temp;
	t_pc			*prev;

	temp = vm->pc_head;
	prev = NULL;
	while (temp)
	{
		if (temp->alive == 0)
		{
			if (prev == NULL)
			{
				free(temp);
				temp = temp->next;
				vm->pc_head = temp;
			}
			else
			{
				prev->next = temp->next;
				free(temp);
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}
*/

void				zero_all_alives_screams(t_vm *vm)
{
	t_pc			*temp;
	unsigned int 	i;

	temp = vm->pc_head;
	while (temp)
	{
		//here we make it either new (ready) to go || kill it with 0 flag
		if (temp->alive_screams)
			temp->alive_screams = 0;
		else
			temp->alive_bool = 0;
		temp = temp->next;
	}
	i = -1;
	while (++i < vm->num_of_players)
	{
		vm->players[i].alives = 0;
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
		if (i != 0 && i % 32 == 0)
			write(1, "\n", 1);
		if (vm->map[i])
			ft_printf("%02x ", vm->map[i]);
		else
			write(1, "00 ", 3);
		i++;
	}
	write(1, "\n", 1);
}

void				are_u_ready_for_rumble(t_vm *vm)
{
	unsigned int	cycles_count;
	unsigned int	general_cycles_count;

	cycles_count = 0;
	general_cycles_count = vm->cycles_to_die;
	while (1)
	{

// printf("CUR_cycle=%u\n", cycles_count);

//for debuging purposes
  // if (cycles_count == 25)
  //   printf("NOW!\n");

		if (vm->dump_flag == 1 && vm->dump_num <= cycles_count)
		{
			
			//delete this! number of pc`s count
			
			write_cur_map(vm);

			t_pc	*temp = vm->pc_head;
			int i = 0;
			printf("\n>>>processes:\n");
			while (temp)
			{
				i++;
				ft_printf("%dpc= %02x, alive= %d; | pos=%u, before=%02x, after=%02x\n", 
					i, vm->map[temp->cur_pos], temp->alive_bool, temp->cur_pos, vm->map[temp->cur_pos - 1], vm->map[temp->cur_pos + 1]);
				temp = temp->next;
			}
			printf("pc_sum==%d,\n", i);


			// write_cur_map(vm);
			free_vm(vm);
			exit(0);
			// error_exit("\nDUMP IN DA HOUSE!\n", -1);
		}
		else if ((vm->cycles_to_die <= 0))//|| check_process_lives(vm->pc_head) == 0)// || function to check pcs lives!!!
		{
	// printf("end cycle1=%u\n", cycles_count);
			// error_exit("THE END1!\n", -1);//need good 'end_and_exit'!  aka "Player X (champion_name) won"
			end_this_game(vm);
		}
		else if (check_process_lives(vm->pc_head) == 0)// || function to check pcs lives!!!
		{
	// printf("end cycle2=%u\n", cycles_count);
			// error_exit("THE END2!\n", -1);//need good 'end_and_exit'!  aka "Player X (champion_name) won"
			end_this_game(vm);
		}
//something wrong with cycle chechink - it supposed to decrement it properly


// printf("CUR_cycle=%u\n", cycles_count);
		pc_list_checker(vm, cycles_count);
		/* cycle_to_die decrease */
		if (cycles_count == general_cycles_count)//was 'cycles_count % vm->cycles_to_die <= 0 && cycles_count > 0'// what if its less than 50?
		{
// printf("\n>>ONECHECK!, cycles_to_die=%u\n", vm->cycles_to_die);
			if (check_players_pc_lives(vm))
			{
				
				vm->cycles_to_die -= CYCLE_DELTA;

// printf("decrease 21! cycle_to_die==%u,   on cycle=%u\n", vm->cycles_to_die, cycles_count);

				zero_all_alives_screams(vm);
				vm->max_checks = 0;
				general_cycles_count += vm->cycles_to_die;
			}
			else if (vm->max_checks == 9)
			{

				vm->cycles_to_die -= CYCLE_DELTA;
			
// printf("decrease MAX! cycle_to_die==%u,  on cycle=%u\n", vm->cycles_to_die, cycles_count);

				//check_pc_to_die(vm);//for list deleting
				zero_all_alives_screams(vm);//for changing flag
				vm->max_checks = 0;
				general_cycles_count += vm->cycles_to_die;
			}
			else
			{
// printf("ONE!, (%u)\n", vm->max_checks);
	
				vm->max_checks++;
				zero_all_alives_screams(vm);
				general_cycles_count += vm->cycles_to_die;
			}
		}
		cycles_count++;
	}
}

int					main(int ac, char **av)
{
	t_vm			*vm;

	vm = (t_vm *)malloc(sizeof(t_vm));
	
	vm_init(vm);
// write(1, vm->map, 20);
	//checking map
	// printf("dump_flag=%d, dump_num=%d\nMAPA:\n%s\n", vm->dump_flag, vm->dump_num, vm->map);
	
	if (ac > 1) //&& ac <= (MAX_ARGS_NUMBER + 1))
	{
		parse_arguments(ac, av, vm);
		parse_all_players(ac, av, vm);
	}
	else
		write(1, "fucked up! please check your arguments\n", ft_strlen("fucked up! please check your arguments\n"));
	position_players(vm);
	players_intro(vm);

	// //check pc list construction
	// t_pc	*temp = vm->pc_head;
	// int i = 0;
	// while (temp)
	// {
	// 	i++;
	// 	printf("%s`s pc! sum =%d\n", vm->players[temp->player_id].name, i);
	// 	temp = temp->next;
	// }
	// exit(0);

	are_u_ready_for_rumble(vm);

	//check pc list construction
	// t_pc *temp;
	// temp = vm->pc_head;
	// // t_pc *temp2 = vm->pc_head->next;
	// // printf("PC List Here:\n");
	// while (temp != NULL)
	// {
	// 	// printf("id=%d, pos=%d\n", temp->player_id, temp->cur_pos);
	// 	write(1, &vm->map[temp->cur_pos], 1);
	// 	temp = temp->next;
	// }

	// //testing map via hexdump
	// write(1, vm->map, MEM_SIZE);

	free_vm(vm);
	// system("leaks my_vm");
	return (0);
}
