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
        args[1] = get_arguments(vm, tmp_pos, 2);
	else if (args_array[1] == IND_CODE)
	{
		tmp_cur_pos = (short)get_arguments(vm, tmp_pos, 2);
		tmp_cur_pos %= IDX_MOD;
		args[1] = get_arguments(vm, &(tmp_cur_pos), 4);
	}
	if (args_array[2] == REG_CODE)
		args[2] = (unsigned char)get_arguments(vm, tmp_pos, 1);
	else if (args_array[2] == DIR_CODE)
		args[2] = get_arguments(vm, tmp_pos, 2);
}

static void         store_value(t_vm *vm, unsigned int array, int position, unsigned char color)
{
    unsigned int	i;

    i = 0;

    //delete me!
//    if (!array)
//        array = 4294967295;
    while (i < 4)
    {
        vm->map[(position + i) % MEM_SIZE] = ((unsigned char *)&array)[3 - i];
        vm->map_color[(position + i) % MEM_SIZE] = color;
        i++;
    }

}

static int          calculate_position(t_pc *process, int *args_array, unsigned int *args)
{
    int             position;

    position = 0;
    if (args_array[1] == REG_CODE && args[1] >= 1 && args[1] <= 16)
    {
        if (args_array[2] == REG_CODE && args[2] >= 1 && args[2] <= 16)
            position = ((int)process->reg[args[1] - 1] + (int)process->reg[args[2] - 1]) % IDX_MOD;
        else
            position = ((int)process->reg[args[1] - 1] + (short)args[2]) % IDX_MOD;//check if its ok with double cast!?
    }
    else if (args_array[1] == IND_CODE)
    {
        if (args_array[2] == REG_CODE && args[2] >= 1 && args[2] <= 16)
            position = ((int)args[1] + (int)process->reg[args[2] - 1]) % IDX_MOD;
        else
            position = ((int)args[1] + (int)args[2]) % IDX_MOD;
    }
    else
    {
        if (args_array[2] == REG_CODE && args[2] >= 1 && args[2] <= 16)
            position = ((short)args[1] + (int)process->reg[args[2] - 1]) % IDX_MOD;
        else
            position = ((short)args[1] + (short)args[2]) % IDX_MOD;
    }
    return (position);
}

void				sti_op(t_vm *vm, t_pc *process)
{
	int				args_array[3];
	unsigned int	args[3];
	unsigned int	tmp_pos;
	int             position;

	tmp_pos = process->cur_pos;
	ft_bzero_int_arr(args_array, 3);
	decodage_opcode(vm->map[++tmp_pos % MEM_SIZE], args_array, 3);//there was codage instead of 'vm->map[++tmp_pos]' before //mb add this line to sti_validation?
	if (sti_validation(args_array, &tmp_pos))
	{
		get_all_arguments_sti(vm, args_array, args, &tmp_pos);
		position = (process->cur_pos + calculate_position(process, args_array, args));
		if (position < 0)
		    position = MEM_SIZE + (position % MEM_SIZE);
		else
		    position %= MEM_SIZE;


//		if (args_array[1] == IND_CODE)
//            args[3] = ((process->cur_pos + (((int)args[1] + (int)args[2]) % IDX_MOD)) % MEM_SIZE);
//		else
//		    args[3] = ((process->cur_pos + (((short)args[1] + (short)args[2]) % IDX_MOD)) % MEM_SIZE);

    if (args[0] >= 1 && args[0] <= 16)
        store_value(vm, process->reg[args[0] - 1], position, process->color);

	}
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;//mb need to add 1 if second arg is T_IND ?
	process->cycles_to_go = -1;
}
