/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:31:09 by inazarin          #+#    #+#             */
/*   Updated: 2018/11/12 20:31:18 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void         fork_helper(t_vm *vm, t_pc *process, short pos, t_pc *node)
{
    int	i;

    i = -1;
    while (++i <= REG_NUMBER)
        node->reg[i] = process->reg[i];
    node->carry = process->carry;
    node->player_id = process->player_id;
    node->command = process->command;
    node->alive_bool = process->alive_bool;
    node->color = process->color;
    node->cycles_to_go = -1;
    node->forked = 1;
    node->cur_pos = pos;
    node->command = vm->map[pos];
}

t_pc				*fork_process(t_vm *vm, t_pc *process, short position)
{
	t_pc			*new_node;

	new_node = (t_pc *)malloc(sizeof(t_pc));
	(!new_node) ? error_exit("Error during forking new process", -1) : (0);
	ft_bzero(new_node, sizeof(t_pc));
    fork_helper(vm, process, position, new_node);
    if (vm->pc_head)
    {
        vm->pc_head->prev = new_node;
        new_node->next = vm->pc_head;
    }
    new_node->prev = NULL;
	vm->pc_head = new_node;
    if (new_node->next)
    	new_node->pc_number = new_node->next->pc_number + 1;
    else
    	new_node->pc_number = 1;
	return (new_node);
}

void				fork_op(t_vm *vm, t_pc *process)
{
	unsigned int	tmp_pos;
	short	        arg;
	short			new_pc_pos;
	t_pc			*new_node;



	new_node = NULL;
	tmp_pos = process->cur_pos % MEM_SIZE;
	arg = (short)get_arguments(vm, &tmp_pos, 2);
	new_pc_pos = ((arg % IDX_MOD) + process->cur_pos) % MEM_SIZE;
	if (new_pc_pos < 0)
	    new_pc_pos = MEM_SIZE + new_pc_pos;
	new_node = fork_process(vm, process, new_pc_pos);
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

void				lfork_op(t_vm *vm, t_pc *process)
{
	unsigned int	tmp_pos;
    short	        arg;
	short			new_pc_pos;
	t_pc			*new_node;

	tmp_pos = process->cur_pos % MEM_SIZE;
	arg = (short)get_arguments(vm, &tmp_pos, 2);
	new_pc_pos = (arg + process->cur_pos) % MEM_SIZE;
    if (new_pc_pos < 0)
        new_pc_pos = MEM_SIZE + new_pc_pos;
	new_node = fork_process(vm, process, new_pc_pos);
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}
