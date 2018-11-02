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


//
/*
unsigned int		reverse_bytes(unsigned int data, char bytes)
{
	unsigned int	res;

	res = data;
	if (bytes == 4)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[3];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[2];
		((unsigned char *)&res)[2] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[3] = ((unsigned char *)&data)[0];
	}
	else if (bytes == 2)
	{
		((unsigned char *)&res)[0] = ((unsigned char *)&data)[1];
		((unsigned char *)&res)[1] = ((unsigned char *)&data)[0];
	}
	return (res);
}

*
** This function gets a value of some sequence of bytes
** size of which specified in arg_size and returns reversed value.
*

unsigned int		get_arg(unsigned int i, char arg_size)
{
	unsigned int	arg;
	unsigned char	str[4];
	unsigned char	j;

	j = 0;
	arg = 0;
	ft_bzero(str, 4);
	while (j < arg_size)
	{
		(i >= MEM_SIZE) ? (i = 0) : 0;
		str[j] = g_map[i];
		j++;
		i++;
	}
	((unsigned char *)&arg)[0] = ((unsigned char *)&str)[0];
	((unsigned char *)&arg)[1] = ((unsigned char *)&str)[1];
	((unsigned char *)&arg)[2] = ((unsigned char *)&str)[2];
	((unsigned char *)&arg)[3] = ((unsigned char *)&str)[3];
	return (reverse_bytes(arg, arg_size));
}

*/

//opavliuk`s and co function!
/*
void				decode_args(char *arg_array, unsigned char codage,
							unsigned int max_args_num)
{
	unsigned char	check;
	unsigned int	i;

	i = 0;
	while (codage && i < max_args_num)
	{
		check = codage & 192;
		// if (check == 64)
		// 	arg_array[i] = REG_CODE;
		// else if (check == 128)
		// 	arg_array[i] = DIR_CODE;
		// else if (check = 192)
		// 	arg_array[i] = IND_CODE;
		// codage <<= 2;
		i++;
	}
}*/

//atlekbai function
/*

unsigned int	ft_args_get(int64_t *i, int label, t_byte *map)
{
	unsigned int	arg;

	arg = 0;
	if (label == 1)
		arg = map[++(*i) % MEM_SIZE];
	else if (label == 2)
		arg = (map[++(*i) % MEM_SIZE] << 8) | map[++(*i) % MEM_SIZE];
	else if (label == 3)
		arg = (map[++(*i) % MEM_SIZE] << 16) | (map[++(*i) % MEM_SIZE] << 8)
		| map[++(*i) % MEM_SIZE];
	else if (label == 4)
		arg = (map[++(*i) % MEM_SIZE] << 24) | (map[++(*i) % MEM_SIZE] << 16)
		| (map[++(*i) % MEM_SIZE] << 8) | map[++(*i) % MEM_SIZE];
	return (arg);
}

*/

unsigned int		get_arguments(t_vm *vm, unsigned int *cur_pos, int label)
{
	unsigned int	ret;

	ret = 0;
	if (label == 1)
		ret = vm->map[++(*cur_pos) % MEM_SIZE];
	else if (label == 2)
		ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 8) | (vm->map[++(*cur_pos) % MEM_SIZE]);
	else if (label == 4)
	{
		ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 24) | (vm->map[++(*cur_pos) % MEM_SIZE] << 16) | 
		(vm->map[++(*cur_pos) % MEM_SIZE] << 8) | (vm->map[++(*cur_pos) % MEM_SIZE]);
	}
	else//mb error?
		ret = 0;
	return (ret);
}

void				live_op(t_vm *vm, t_pc *process)
{
	// unsigned int 	dir_arg[4];
	char			args_array[1];//mb 4 of them ??? or 1 
	unsigned int	max_args;
	unsigned char	codage;
	unsigned char	check;
	unsigned int 	tmp_pos;
	unsigned int	temp;
	unsigned int	check_int;

	max_args = 1;//mb del it and put value right to the function ???
	process->cycles_to_go = 10;
	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	// decode_args(args_array, codage, max_args);
	if (codage)//do we need nulls in other 6 bits?
	{
		check = codage & 192;
		if (check == 128)
			args_array[0] = DIR_CODE;
		else
			error_exit("Invalid argument type in `live`.\n", -1);
	}
	else
		error_exit("Error with codage in live_op\n", -1);
	process->alive = 1;
	check_int = vm->players[process->player_id].player_number;
	temp = get_arguments(vm, &tmp_pos, 4);
	if (check_int == temp)
		vm->players[process->player_id].alives++;
	process->cycles_to_go = -1;
	process->cur_pos = tmp_pos + 1;
}

void				and_op(t_vm *vm, t_pc *process)//if needed could del int cus its in ext pointer
{
	char			args_array[3];//mb 4 of them ???
	unsigned int	max_args;
	unsigned char	codage;
	unsigned char	check;
	// unsigned int	temp;
	unsigned int 	args[2];
	unsigned int 	i;
		unsigned int 	tmp_pos;

	max_args = 3;//mb del it and put value right to the function ???
	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	// decode_args(args_array, codage, max_args);
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
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (!args_array[0] || !args_array[1] || args_array[2] != REG_CODE)
		tmp_pos += 5;
	else//there would be code so mb make it another func? || piece of code above?
	{
		if (args_array[0] == REG_CODE)
		{
			args[0] = get_arguments(vm, &tmp_pos, 1);
			process->reg[0] = args[0];
		}
		else if (args_array[0] == DIR_CODE)
			args[0] = get_arguments(vm, &tmp_pos, 4);
		else if (args_array[0] == IND_CODE)
			args[0] = get_arguments(vm, &tmp_pos, 2);
		if (args_array[1] == REG_CODE)
		{
			process->reg[1] = get_arguments(vm, &tmp_pos, 1);
			args[1] = process->reg[1];
		}
		else if (args_array[1] == DIR_CODE)
			args[1] = get_arguments(vm, &tmp_pos, 4);
		else if (args_array[1] == IND_CODE)
			args[1] = get_arguments(vm, &tmp_pos, 2);
		if (args_array[2] == REG_CODE)
			process->reg[2] = args[0] & args[1];
		if (process->reg[2] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->cycles_to_go = -1;
	process->cur_pos = tmp_pos + 1;
}

void				zjmp_op(t_vm *vm, t_pc *process)
{
	// char			args_array[1];//mb 4 of them ??? or 1
	// unsigned char	codage;
	// unsigned char	check;
	unsigned int 	tmp_pos;
	unsigned int	check_int;

	process->cycles_to_go = 10;
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
	if (process->carry == 1)
	{
		check_int = get_arguments(vm, &tmp_pos, 2);
		tmp_pos += (check_int % IDX_MOD);
	}
	//what if carry doesnt == 1 - what should we do?
	process->cycles_to_go = -1;
	process->cur_pos = tmp_pos + 1;
}

// undone fucking fuck !
void				sti_op(t_vm *vm, t_pc *process)
{
	char			args_array[3];//mb 4 of them ???
	unsigned int	max_args;
	unsigned char	codage;
	unsigned char	check;
	unsigned int	temp;
	unsigned int	args[3];
	// short			short_args[3];
	unsigned int	i;

	unsigned int	tmp_cur_pos;
	unsigned int	tmp_pos;
	int				sum;


	max_args = 3;//mb del it and put value right to the function ???
	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];	
	ft_bzero(&args_array, 3);
	// decode_args(args_array, codage, max_args);
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
	//check if we need this if   (IMHO we need new func to move our procces cur_pos correctly)
	if (!args_array[2] || !args_array[1] || args_array[0] != REG_CODE)//imho - invalid
		tmp_pos += 5;
	else
	{
		if (args_array[0] == REG_CODE)
		{
			args[0] = (unsigned char)get_arguments(vm, &tmp_pos, 1);	
		}
		if (args_array[1] == REG_CODE)
		{
			process->reg[1] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			args[1] = process->reg[1];
		}
		else if (args_array[1] == DIR_CODE)
			args[1] = (short)get_arguments(vm, &tmp_pos, 2);
		else if (args_array[1] == IND_CODE)//almost sure something wrong with it!
		{
			//по карте перемещаемся на позицию ... и берем там аргумент
			tmp_cur_pos = (short)get_arguments(vm, &tmp_pos, 2);
			tmp_cur_pos %= IDX_MOD;
			args[1] = get_arguments(vm, &(tmp_cur_pos), 4);
		}
		if (args_array[2] == REG_CODE)
		{
			process->reg[2] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			args[2] = process->reg[2];
		}
		else if (args_array[2] == DIR_CODE)
			args[2] = (short)get_arguments(vm, &tmp_pos, 2);
	
		// if (args_array[1] == IND_CODE)
		// 	vm->map[cur_pos + ((args[1] + args[2]) % IDX_MOD)] = process->reg[0];
		// else
		/*was like this */
		// vm->map[(*cur_pos) + ((args[1] + args[2]) % IDX_MOD)] = process->reg[0];


		/* first method */
		sum = (args[1] + args[2]);
		temp = (process->cur_pos + (sum % IDX_MOD) % MEM_SIZE);
		unsigned int array = process->reg[args[0] - 1];
		i = 0;
		while (i < 4)
		{
			vm->map[temp + i] = ((unsigned char *)&array)[3 - i];
			i++;
		}
		//this is a test!
		// vm->map[temp + i] = args[1];
		// vm->map[temp + i + 1] = args[2];
	}
	process->cur_pos = tmp_pos + 1;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}

void				feel_n_fill_pc(t_vm *vm, t_pc *process)//just 'zork.cor' for now
{
	unsigned char	tmp;
	unsigned int	a;

	a = 0;
	tmp = 0;
	tmp = vm->map[process->cur_pos];
	a = tmp;
	if (a == 1)
		live_op(vm, process);
	// else if (a == 2)
	// 	ld_op(vm, process->cur_pos, process);
	// else if (a == 3)
	// 	st_op(vm, process->cur_pos, process);
	// else if (a == 4)
	// 	add_op(vm, process->cur_pos, process);
	// else if (a == 5)
	// 	sub_op(vm, process->cur_pos), process;
	else if (a == 6)
		and_op(vm, process);
	// else if (a == 7)
	// 	or_op(vm, process->cur_pos, process);
	// else if (a == 8)
	// 	xor_op(vm, process->cur_pos, process);
	else if (a == 9)
		zjmp_op(vm,  process);
	// else if (a == 10)
	// 	ldi_op(vm, process->cur_pos, process);
	else if (a == 11)
		sti_op(vm, process);
// 	else if (a == 12)
// 		fork_op(vm, process->cur_pos, process);
// 	else if (a == 13)
// 		lld_op(vm, process->cur_pos, process);
// 	else if (a == 14)
// 		lldi_op(vm, process->cur_pos, process);
// 	else if (a == 15)
// 		lfork_op(vm, process->cur_pos, process);
// 	else if (a == 16)
// 		aff_op(vm, process->cur_pos, process);

	//here would be new get_cycles_to_go() funcrion use!!!!
}

int					get_cycles_to_go(t_vm *vm, t_pc *process)
{
	int				check;
	unsigned char	temp;
	int 			ret;

	temp = vm->map[process->cur_pos];
	check = temp;
	if (check == 1)
		ret = 10;
	else if (check == 2)
		ret = 5;
	else if (check == 3)
		ret = 5;
	else if (check == 4)
		ret = 10;
	else if (check == 5)
		ret = 10;
	else if (check == 6)
		ret = 6;
	else if (check == 7)
		ret = 6;
	else if (check == 8)
		ret = 6;
	else if (check == 9)
		ret = 20;
	else if (check == 10)
		ret = 25;
	else if (check == 11)
		ret = 25;
	else if (check == 12)
		ret = 800;
	else if (check == 13)
		ret = 10;
	else if (check == 14)
		ret = 50;
	else if (check == 15)
		ret = 1000;
	else if (check == 16)
		ret = 2;
	else//mb an error?
		ret = 0;
	return (ret);
}

void				pc_list_checker(t_vm *vm)
{
	t_pc			*pointer;

	pointer = vm->pc_head;
	while (pointer)
	{
		if (pointer->cycles_to_go < 0)
			pointer->cycles_to_go = get_cycles_to_go(vm, pointer);
		else if (pointer->cycles_to_go > 0)
			pointer->cycles_to_go--;
		else if (pointer->cycles_to_go == 0)
			feel_n_fill_pc(vm, pointer);

		pointer = pointer->next;
	}
}

void				are_u_ready_for_rumble(t_vm *vm)
{
	unsigned int	cycles_count = 0;
	while (1)//while originaly
	{

		if (vm->dump_flag == 1 && vm->dump_num <= cycles_count)
		{
			write(1, vm->map, MEM_SIZE);
			exit(0);
			// error_exit("\nDUMP IN DA HOUSE!\n", -1);
		}
		else if ((vm->cycles_to_die <= 0))// || function to check pcs alive!!!
			error_exit("THE END!\n", -1);

		pc_list_checker(vm);
		/***
			here would be functions that checks whether we need or not decrease cycle_to_die

			1) Если процессы зародившиеся от одного игрока в сумме скажут, что они живы более 21 раз, то cycle_to_die уменьшается на CYCLE_DELTA
			2) Если в течение MAX_CHECKS раз проверок Cycle_to_die не уменьшался, то cycle_to_die уменьшается на CYCLE_DELTA 
		***/


		/***
			add here cycle_to_die decreasing!
		***/

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

	are_u_ready_for_rumble(vm);

	//check pc list
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
