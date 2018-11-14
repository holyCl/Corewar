/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:32:13 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/12 18:32:25 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int					ld_validation(int *args, unsigned int *tmp_pos)//check it with invalid argument!
{
	unsigned int	step;
	unsigned int	i;

	step = 0;
	if (args[1] == REG_CODE && (args[0] == DIR_CODE || args[0] == IND_CODE))
		return (1);
	else
	{
		i = -1;
		while (++i < 2)
		{
			if (args[i] == REG_CODE)
				(*tmp_pos) += 1;
			else if (args[i] == IND_CODE)
				(*tmp_pos) += 2;
			else if (args[i] == DIR_CODE)
				(*tmp_pos) += 4;
		}
		return (0);
	}
}

//check it carefully!
static void				get_all_arguments_ld(t_vm *vm, int *args_array, 
					unsigned int *args, unsigned int *tmp_pos)
{
	unsigned int tmp_cur_pos;

	if (args_array[0] == DIR_CODE)
	{
		args[0] = get_arguments(vm, tmp_pos, 4);
	}
	else if (args_array[0] == IND_CODE)
	{
		args[0] = (short)get_arguments(vm, tmp_pos, 2) % IDX_MOD;
		tmp_cur_pos = ((*tmp_pos - 2) + args[0]) % MEM_SIZE;//here might be problem with steping backwards
		args[0] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
}

void				ld_op(t_vm *vm, t_pc *process)
{
	int				args_array[2];
	unsigned int	args[2];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	ft_bzero(&args_array, 2);
	decodage_opcode(vm->map[++tmp_pos], args_array, 2);//there was codage instead of 'vm->map[++tmp_pos]' before //mb add this line to sti_validation?
	if (ld_validation(args_array, &tmp_pos))
	{
		get_all_arguments_ld(vm, args_array, args, &tmp_pos);
		process->reg[args[1] - 1] = args[0];
		if (process->reg[args[1] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}

static void				get_all_arguments_lld(t_vm *vm, int *args_array, 
					unsigned int *args, unsigned int *tmp_pos)
{
	unsigned int tmp_cur_pos;

	if (args_array[0] == DIR_CODE)
	{
		args[0] = get_arguments(vm, tmp_pos, 4);
	}
	else if (args_array[0] == IND_CODE)
	{
		args[0] = (short)get_arguments(vm, tmp_pos, 2);
		tmp_cur_pos = ((*tmp_pos - 2) + args[0]) % MEM_SIZE;
		args[0] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
}

void				lld_op(t_vm *vm, t_pc *process)
{
	int				args_array[2];
	unsigned int	args[2];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	ft_bzero(&args_array, 2);
	decodage_opcode(vm->map[++tmp_pos], args_array, 2);//there was codage instead of 'vm->map[++tmp_pos]' before //mb add this line to sti_validation?
	if (ld_validation(args_array, &tmp_pos))
	{
		get_all_arguments_lld(vm, args_array, args, &tmp_pos);
		process->reg[args[1] - 1] = args[0];
		if (process->reg[args[1] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}