/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 22:14:45 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/05 22:14:48 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int					sti_validation(int *args, unsigned int *tmp_pos)//check it with invalid argument!
{
	unsigned int	step;
	unsigned int	i;

	step = 0;
	if (args[0] == REG_CODE && 
		(args[1] == REG_CODE || args[1] == DIR_CODE || args[1] == IND_CODE) &&
		(args[2] == REG_CODE || args[2] == DIR_CODE))
		return (1);
	else
	{
		i = 0;
		while (i < 3)
		{
			if (args[i] == REG_CODE)
				step += 1;
			else if (args[i] == DIR_CODE || args[i] == IND_CODE)
				step += 2;
			i++;
		}
		(*tmp_pos) += step;
		return (0);
	}
}

static void				get_all_arguments_sti(t_vm *vm, int *args_array, unsigned int *args, unsigned int *tmp_pos)
{
	unsigned int tmp_cur_pos;

	if (args_array[0] == REG_CODE)
		args[0] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[1] == DIR_CODE)
		args[1] = (short)get_arguments(vm, tmp_pos, 2);
	else if (args_array[1] == IND_CODE)//almost sure something wrong with it!
	{
		//по карте перемещаемся на позицию ... и берем там аргумент
		tmp_cur_pos = (short)get_arguments(vm, tmp_pos, 2);
		tmp_cur_pos %= IDX_MOD;
		args[1] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	if (args_array[2] == REG_CODE)
		args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[2] == DIR_CODE)
		args[2] = (short)get_arguments(vm, tmp_pos, 2);
}

void				sti_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned int	args[4];
	unsigned int	i;
	unsigned int	tmp_pos;
	unsigned int	array;

	tmp_pos = process->cur_pos;
	// codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 3);
	decodage_opcode(vm->map[++tmp_pos], args_array, 3);//there was codage instead of 'vm->map[++tmp_pos]' before //mb add this line to sti_validation?
	if (sti_validation(args_array, &tmp_pos))
	{
		get_all_arguments_sti(vm, args_array, args, &tmp_pos);
		/* first method */
		// sum = ;
		// args[1] = 65462;
		args[3] = (process->cur_pos + (((int)args[1] + (int)args[2]) % IDX_MOD) % MEM_SIZE);
		array = process->reg[args[0] - 1];
		i = 0;
		while (i < 4)
		{
			vm->map[args[3] + i] = ((unsigned char *)&array)[3 - i];
			i++;
		}
		//this is a test!
		// vm->map[temp + i] = args[1];
		// vm->map[temp + i + 1] = args[2];
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}
