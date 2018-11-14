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

static int					st_validation(int *args, unsigned int *tmp_pos)//check it with invalid argument!
{
	unsigned int	step;
	unsigned int	i;

	step = 0;
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


void				st_op(t_vm *vm, t_pc *process)//mb need update like in sti_op()
{
	int				args_array[2];
	unsigned int	args[3];
	unsigned int	i;
	unsigned int	tmp_pos;
	unsigned int	array;
	// unsigned int	sum;

	tmp_pos = process->cur_pos;
	// codage = vm->map[++tmp_pos];
	ft_bzero(&args_array, 2);
	decodage_opcode(vm->map[++tmp_pos], args_array, 2);//there was codage instead of 'vm->map[++tmp_pos]' before //mb add this line to sti_validation?
	if (st_validation(args_array, &tmp_pos))
	{
		args[0] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
		if (args_array[1] == REG_CODE)
		{
			args[1] = (unsigned char)get_arguments(vm, &tmp_pos, 1);
			process->reg[args[1] - 1] = process->reg[args[0] - 1];
		}
		else if (args_array[1] == IND_CODE)
		{
			args[1] = (short)get_arguments(vm, &tmp_pos, 2);
			// Значение T_REG (первый аргумент) записывается в ячейку, по адресу (текущая позиция PC плюс (T_IND % IDX_MOD))
			array = process->reg[args[0] - 1];
			args[2] = process->cur_pos + (args[1] % IDX_MOD);
			i = -1;
			while (++i < 4)
				vm->map[ + i] = ((unsigned char *)&array)[3 - i];
		}
		// get_all_arguments_sti(vm, args_array, args, &tmp_pos);
		//get it here instead
		/* first method */
		// sum = ;

		/* shit for sti_op()!!!
		args[3] = (process->cur_pos + ((args[1] + args[2]) % IDX_MOD) % MEM_SIZE);
		array = process->reg[args[0] - 1];
		i = -1;
		while (++i < 4)
		{
			vm->map[args[3] + i] = ((unsigned char *)&array)[3 - i];
		}
		*/
		//this is a test!
		// vm->map[temp + i] = args[1];
		// vm->map[temp + i + 1] = args[2];
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}
