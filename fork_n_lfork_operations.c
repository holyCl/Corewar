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

t_pc				*fork_process(t_vm *vm, t_pc *process, unsigned int position)
{
	t_pc			*new_node;
	int	i;

	new_node = (t_pc *)malloc(sizeof(t_pc));
	if (!new_node)
		error_exit("Error during forking new process", -1);
	ft_bzero(new_node, sizeof(t_pc));
	i = -1;
	while (++i <= REG_NUMBER)
		new_node->reg[i] = process->reg[i];
	new_node->carry = process->carry;
	new_node->player_id = process->player_id;
	new_node->command = process->command;
	new_node->alive_bool = process->alive_bool;
	new_node->cycles_to_go = -1;
	new_node->cur_pos = position;
	if (vm->pc_head)
		new_node->next = vm->pc_head;
	vm->pc_head = new_node;
	return (new_node);
}

void				fork_op(t_vm *vm, t_pc *process)
{
	unsigned int	tmp_pos;
	unsigned int	arg;
	short			new_pc_pos;
	t_pc			*new_node;

	new_node = NULL;
	tmp_pos = process->cur_pos;
	arg = (short)get_arguments(vm, &tmp_pos, 2);
	new_pc_pos = ((arg % IDX_MOD) + process->cur_pos) % MEM_SIZE;
	new_node = fork_process(vm, process, new_pc_pos);
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}

void				lfork_op(t_vm *vm, t_pc *process)
{
	unsigned int	tmp_pos;
	unsigned int	arg;
	short			new_pc_pos;
	t_pc			*new_node;

	tmp_pos = process->cur_pos;
	arg = (short)get_arguments(vm, &tmp_pos, 2);
	new_pc_pos = (arg + process->cur_pos) % MEM_SIZE;
	new_node = fork_process(vm, process, new_pc_pos);
	process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
	process->cycles_to_go = -1;
}
