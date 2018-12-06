/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:46:39 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/21 18:46:51 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			aox_op_validation(const int *args, unsigned int *tmp_pos)
{
	unsigned int	step;
	int	i;

	step = 0;
	if ((args[0] == REG_CODE || args[0] == DIR_CODE || args[0] == IND_CODE) &&
		(args[1] == REG_CODE || args[1] == DIR_CODE || args[1] == IND_CODE) &&
		args[2] == REG_CODE)
		return (1);
	else
	{
		i = -1;
		while (++i < 3)
		{
			if (args[i] == REG_CODE)
				step += 1;
			else if (args[i] == DIR_CODE)
				step += 4;
			else if (args[i] == IND_CODE)
				step += 2;
		}
		(*tmp_pos) += step;
		return (0);
	}
}

static void			get_all_arguments_aox(t_vm *vm, const int *args_array,
					unsigned int *args, unsigned int *tmp_pos)
{
	if (args_array[0] == REG_CODE)
		args[0] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[0] == DIR_CODE)
		args[0] = get_arguments(vm, tmp_pos, 4);
	else if (args_array[0] == IND_CODE)
		args[0] = (short)get_arguments(vm, tmp_pos, 2);
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[1] == DIR_CODE)
		args[1] = get_arguments(vm, tmp_pos, 4);
	else if (args_array[1] == IND_CODE)
		args[1] = (short)get_arguments(vm, tmp_pos, 2);
	if (args_array[2] == REG_CODE)
		args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
}

static void			xor_op_helper(const int *args_array, const unsigned int *args, t_pc *process)
{
	if (args_array[0] == REG_CODE && args[2] >= 1 && args[2] <= 16 && args[0] >= 1 && args[0] <= 16)
	{
		if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
			process->reg[args[2] - 1] = process->reg[args[0] - 1] ^ process->reg[args[1] - 1];
		else
			process->reg[args[2] - 1] = process->reg[args[0] - 1] ^ args[1];
	}
	else if (args[2] >= 1 && args[2] <= 16)
	{
		if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
			process->reg[args[2] - 1] = args[0] ^ process->reg[args[1] - 1];
		else
			process->reg[args[2] - 1] = args[0] ^ args[1];
	}
}

void				xor_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos % MEM_SIZE];
	ft_bzero_int_arr(args_array, 3);
	decodage_opcode(codage, args_array, 3);
	if (aox_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_aox(vm, args_array, args, &tmp_pos);
        xor_op_helper(args_array, args, process);
		if (args[2] >= 1 && args[2] <= 16)
		{
			if (process->reg[args[2] - 1] == 0)
				process->carry = 1;
			else
				process->carry = 0;
		}
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}
