/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:55:34 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/05 21:55:50 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void				choose_helper(t_vm *vm, t_pc *process, unsigned int a)
{
	if (a == 9)
		zjmp_op(vm, process);
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
}

static void				choose_pc(t_vm *vm, t_pc *process, unsigned int cycles)
{
	unsigned int	a;

	a = 0;
	a = process->command;

//printf("!!>>feel_n_fill(%u). cm=%u, pl_num=%u; forked_flag==%u\n", cycles_count, a, process->pc_number, process->forked);

	if (a == 1)
		live_op(vm, process, cycles);
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
	else if (a >= 9 && a <= 16)
		choose_helper(vm, process, a);
	// else if (a == 9)
	// 	zjmp_op(vm, process);
	// else if (a == 10)
	// 	ldi_op(vm, process);
	// else if (a == 11)
	// 	sti_op(vm, process);
	// else if (a == 12)
	// 	fork_op(vm, process);
	// else if (a == 13)
	// 	lld_op(vm, process);
	// else if (a == 14)
	// 	lldi_op(vm, process);
	// else if (a == 15)
	// 	lfork_op(vm, process);
	// else if (a == 16)
	// 	aff_op(vm, process);
}

static int					get_ret(const int check)
{
	int						ret;

	ret = 0;
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
	return (ret);
}

static int					get_cycles_to_go(t_vm *vm, t_pc *process, int flag)
{
	int				check;
	int				ret;

	ret = 0;
	check = process->command;
	if (check == 1 || check == 2 || check == 3 || check == 4 || check == 5 || 
		check == 6 || check == 7 || check == 8 || check == 9 || check == 10 ||
		check == 11 || check == 12 || check == 13 || check == 14 || 
		check == 15 || check == 16)
		ret = get_ret(check);
	else
	{
		ret = 0;
		if (flag)
		{
			process->cur_pos = (process->cur_pos + 1) % MEM_SIZE;
			process->command = vm->map[process->cur_pos];
			if (process->command >= 1 && process->command <= 16)
				ret = get_cycles_to_go(vm, process, 0) + 1;
		}
	}
	if (process->forked)
	{
		ret -= 1;
		process->forked = 0;
	}
	return (ret - 1);
}

void				pc_list_checker(t_vm *vm, unsigned int cycles_count)
{
	t_pc			*pointer;

	pointer = vm->pc_head;
	while (pointer)
	{
		if (pointer->cycles_to_go < 0)
		{
			pointer->command = vm->map[pointer->cur_pos];
			pointer->cycles_to_go = get_cycles_to_go(vm, pointer, 1);
		}
		else if (pointer->cycles_to_go > 0)
			pointer->cycles_to_go--;
		else if (pointer->cycles_to_go == 0)
		{
			if (pointer->command == 0 || pointer->command > 16)
				pointer->command = vm->map[pointer->cur_pos];
			choose_pc(vm, pointer, cycles_count);
			pointer->command = vm->map[pointer->cur_pos];
			pointer->cycles_to_go = get_cycles_to_go(vm, pointer, 0);
		}
		pointer = pointer->next;
	}
}
