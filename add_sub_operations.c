/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:31:06 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/07 14:31:27 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int 			add_sub_op_validation(int *args, unsigned int *tmp_pos)
{
	unsigned int	step;

	step = 0;
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE)
		return (1);
	else
	{
		step = 3;
		(*tmp_pos) += step;
		return (0);
	}
}

static void			get_all_arguments_add_sub(t_vm *vm, int *args_array,
					unsigned int *args, unsigned int *tmp_pos)
{
	if (args_array[0] == REG_CODE && args_array[1] == REG_CODE &&
		args_array[2] == REG_CODE)
	{
		args[0] = (unsigned char)get_arguments(vm, tmp_pos, 1);
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
		args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	}
	else
		(*tmp_pos) = ((*tmp_pos) + 3) % MEM_SIZE;
}

void				add_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(codage, args_array, 3);
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (add_sub_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_add_sub(vm, args_array, args, &tmp_pos);
		process->reg[args[2] - 1] = args[0] + args[1];
		if (process->reg[args[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

void				sub_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(codage, args_array, 3);
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (add_sub_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_add_sub(vm, args_array, args, &tmp_pos);
		process->reg[args[2] - 1] = args[0] - args[1];
		if (process->reg[args[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

