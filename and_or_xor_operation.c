/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:36:27 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/06 13:36:29 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			aox_op_validation(int *args, unsigned int *tmp_pos)//or, xor would be quite similar
{
	unsigned int	step;
	unsigned int	i;

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

static void			get_all_arguments_aox(t_vm *vm, int *args_array,
					unsigned int *args, unsigned int *tmp_pos)//was with 't_pc *process' argument
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
}

void				and_op(t_vm *vm, t_pc *process)//if needed could del int cus its in ext pointer
{
	int				args_array[3];//mb 4 of them ???
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(codage, args_array, 3);
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (aox_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_aox(vm, args_array, args, &tmp_pos);
		if (args_array[2] == REG_CODE)
		{
			args[2] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			process->reg[args[2] - 1] = args[0] & args[1];
		}
		if (process->reg[args[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	// printf("carry become=%u\n", process->carry);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;

	// printf("%u\n", );
}

void				or_op(t_vm *vm, t_pc *process)//if needed could del int cus its in ext pointer
{
	int				args_array[3];//mb 4 of them ???
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(codage, args_array, 3);
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (aox_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_aox(vm, args_array, args, &tmp_pos);
		if (args_array[2] == REG_CODE)
		{
			args[2] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			process->reg[args[2] - 1] = args[0] | args[1];
		}
		if (process->reg[args[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	// printf("carry become=%u\n", process->carry);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;

	// printf("%u\n", );
}

void				xor_op(t_vm *vm, t_pc *process)//if needed could del int cus its in ext pointer
{
	int				args_array[3];//mb 4 of them ???
	unsigned char	codage;
	unsigned int	args[3];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(codage, args_array, 3);
	// if (!codage)
	//process->cur_pos += 2;//go to next? or like below?
	if (aox_op_validation(args_array, &tmp_pos))
	{
		get_all_arguments_aox(vm, args_array, args, &tmp_pos);
		if (args_array[2] == REG_CODE)
		{
			args[2] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			process->reg[args[2] - 1] = args[0] ^ args[1];
		}
		if (process->reg[args[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	// printf("carry become=%u\n", process->carry);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;

	// printf("%u\n", );
}
