/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:00:10 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/12 20:00:22 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int					ldi_validation(int *args, unsigned int *tmp_pos)//check it with invalid argument!
{
	int	            i;

	if ((args[0] == REG_CODE || args[0] == DIR_CODE || args[0] == IND_CODE) &&
		(args[1] == REG_CODE || args[1] == DIR_CODE) &&
		args[2] == REG_CODE)
		return (1);
	else
	{
		i = -1;
		while (++i < 3)
		{
			if (args[i] == REG_CODE)
				(*tmp_pos) += 1;
			else if (args[i] == IND_CODE)
				(*tmp_pos) += 2;
			else if (args[i] == DIR_CODE)
				(*tmp_pos) += 2;
		}
		return (0);
	}
}

static void				get_all_arguments_ldi(t_vm *vm, int *args_array,
					unsigned int *args, unsigned int *tmp_pos)
{
	unsigned int	tmp_cur_pos;
	short 			sh;

	if (args_array[0] == DIR_CODE)
		args[0] = get_arguments(vm, tmp_pos, 2);
	else if (args_array[0] == IND_CODE)
	{
		sh = (short)get_arguments(vm, tmp_pos, 2) % IDX_MOD;
        if (sh < 0)
            sh = MEM_SIZE + sh;
		tmp_cur_pos = ((*tmp_pos - 3) + sh) % MEM_SIZE;//was -2 !!!
		args[0] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	else if (args_array[0] == REG_CODE)
		args[0] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[1] == DIR_CODE)
		args[1] = get_arguments(vm, tmp_pos, 2);
	args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
}

void				ldi_op(t_vm *vm, t_pc *process)//mb -1 for load position?  and cast it to (short)???
{
	int				args_array[3];
	unsigned int	args[3];
	unsigned int	tmp_pos;
    int 	tmp_cur_pos;
    unsigned int    position;//was added recently

	tmp_pos = process->cur_pos;
	ft_bzero_int_arr(args_array, 3);
	decodage_opcode(vm->map[++tmp_pos], args_array, 3);
	if (ldi_validation(args_array, &tmp_pos))
	{
		get_all_arguments_ldi(vm, args_array, args, &tmp_pos);
		tmp_cur_pos = 0;
		if (args_array[0] == REG_CODE)
		{
			if (args_array[1] == REG_CODE && args[0] >= 1 && args[0] <= 16 && args[1] >= 1 && args[1] <= 16)
				tmp_cur_pos = ((((int)process->reg[args[0] - 1] + (int)process->reg[args[1] - 1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
			else if (args[1] >= 1 && args[1] <= 16)
				tmp_cur_pos = (((process->reg[args[0] - 1] + (short)args[1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
		}
		else if (args_array[0] == IND_CODE)
		{
			if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
				tmp_cur_pos = ((((int)args[0] + (int)process->reg[args[1] - 1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
			else
				tmp_cur_pos = ((((int)args[0] + (short)args[1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
		}
		else
        {
            if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
                tmp_cur_pos = ((((short)args[0] + (int)process->reg[args[1] - 1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
            else
                tmp_cur_pos = (((short)(args[0] + (short)args[1]) % IDX_MOD) + process->cur_pos) % MEM_SIZE;
        }
        //delme mb?
        tmp_cur_pos -= 1;
        if (tmp_cur_pos < 0)//was added recently
            tmp_cur_pos = (MEM_SIZE + tmp_cur_pos);//was added recently
        position = (unsigned int)tmp_cur_pos;//was added recently
        if (args[2] >=1 && args[2] <= 16)
            process->reg[args[2] -1] = get_arguments(vm, &position, 4);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}

static void				get_all_arguments_lldi(t_vm *vm, int *args_array, 
					unsigned int *args, unsigned int *tmp_pos)
{
	unsigned int tmp_cur_pos;
    short 			sh;

	if (args_array[0] == DIR_CODE)
		args[0] = get_arguments(vm, tmp_pos, 2);
	else if (args_array[0] == IND_CODE)
	{
		sh = (short)get_arguments(vm, tmp_pos, 2) % IDX_MOD;
        if (sh < 0)
            sh = MEM_SIZE + sh;
		tmp_cur_pos = ((*tmp_pos - 3) + sh) % MEM_SIZE;//was -2 !!
		args[0] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	else if (args_array[0] == REG_CODE)
		args[0] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	if (args_array[1] == REG_CODE)
		args[1] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[1] == DIR_CODE)
		args[1] = get_arguments(vm, tmp_pos, 2);
	args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
}

void				lldi_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned int	args[3];
	unsigned int	tmp_pos;
	int 	tmp_cur_pos;
	unsigned int    position;//was added recently

	tmp_pos = process->cur_pos;
	ft_bzero_int_arr(args_array, 3);
	decodage_opcode(vm->map[++tmp_pos], args_array, 3);
	if (ldi_validation(args_array, &tmp_pos))
	{
		get_all_arguments_lldi(vm, args_array, args, &tmp_pos);
//		tmp_cur_pos = (((args[0] + args[1])) + process->cur_pos) % MEM_SIZE;
        if (args_array[0] == REG_CODE && args[0] >= 1 && args[0] <= 16)
        {
            if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
                tmp_cur_pos = ((((int)process->reg[args[0] - 1] + (int)process->reg[args[1] - 1])) + process->cur_pos) % MEM_SIZE;
            else
                tmp_cur_pos = ((((int)process->reg[args[0] - 1] + (short)args[1])) + process->cur_pos) % MEM_SIZE;
        }
        else if (args_array[0] == IND_CODE)
        {
            if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
                tmp_cur_pos = ((((int)args[0] + (int)process->reg[args[1] - 1])) + process->cur_pos) % MEM_SIZE;
            else
                tmp_cur_pos = ((((int)args[0] + (short)args[1])) + process->cur_pos) % MEM_SIZE;
        }
        else
        {
            if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
                tmp_cur_pos = ((((short)args[0] + (int)process->reg[args[1] - 1])) + process->cur_pos) % MEM_SIZE;
            else
                tmp_cur_pos = (((short)(args[0] + (short)args[1])) + process->cur_pos) % MEM_SIZE;
        }
        //delme mb?
        tmp_cur_pos -= 1;
        if (tmp_cur_pos < 0)//was added recently
            tmp_cur_pos = (MEM_SIZE + tmp_cur_pos);//was added recently
        position = (unsigned int)tmp_cur_pos;//was added recently
		if (args[2] >= 1 && args[2] <= 16)
            process->reg[args[2] - 1] = get_arguments(vm, &position, 4);
	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}
