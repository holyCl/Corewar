/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:26:07 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/12 18:26:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			st_validation(int *args, unsigned int *tmp_pos)
{
	int				i;

	if (args[0] == REG_CODE && (args[1] == REG_CODE || args[1] == IND_CODE))
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

static void			st_op_ind_helper(t_vm *vm, t_pc *process, short *args)
{
	int				pos;
	int				i;
	unsigned int	value;

	if (args[0] >= 1 && args[0] <= 16)
	{
		value = process->reg[args[0] - 1];
		pos = process->cur_pos + (args[1] % IDX_MOD);
		if (pos < 0)
			pos = MEM_SIZE + pos;
		i = -1;
		while (++i < 4)
		{
			vm->map[(pos + i) % MEM_SIZE] = ((unsigned char *)&value)[3 - i];
			vm->map_color[(pos + i) % MEM_SIZE] = process->color;
		}
	}
}

void				st_op(t_vm *vm, t_pc *process)
{
	int				args_array[2];
	short			args[2];
	unsigned int	tmp_pos;

	tmp_pos = process->cur_pos;
	ft_bzero_int_arr(args_array, 2);
	decodage_opcode(vm->map[++tmp_pos % MEM_SIZE], args_array, 2);
	if (st_validation(args_array, &tmp_pos))
	{
		args[0] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
		if (args_array[1] == REG_CODE)
		{
			args[1] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			if ((args[0] >= 1 && args[0] <= 16) &&
				(args[1] >= 1 && args[1] <= 16))
				process->reg[args[1] - 1] = process->reg[args[0] - 1];
		}
		else if (args_array[1] == IND_CODE)
		{
			args[1] = (short)get_arguments(vm, &tmp_pos, 2);
			st_op_ind_helper(vm, process, args);
		}
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}
