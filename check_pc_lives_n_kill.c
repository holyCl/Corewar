/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pc_lives_n_kill.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:42:52 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/06 13:43:15 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					check_players_pc_lives(t_vm *vm)
{
	unsigned int	i;
	t_pc			*temp;

	temp = vm->pc_head;
	i = 0;
	while (temp)
	{
		i += temp->alive_screams;
		if (i >= NBR_LIVE)
		{
			vm->max_checks = 0;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static void			kill_pc_n_del_from_list(t_vm *vm, t_pc *temp)
{
	temp->alive_screams = 0;
	temp->alive_bool = 0;
	if (!vm->pc_head || !temp)
		return ;
	if (temp->prev == NULL)
	{
		vm->pc_head = temp->next;
		if (temp->next)
			temp->next->prev = NULL;
	}
	else
	{
		temp->prev->next = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
	}
	free(temp);
}

void				zero_all_alives_screams(t_vm *vm)
{
	t_pc			*temp;
	t_pc			*del;
	int				i;

	temp = vm->pc_head;
	while (temp)
	{
		if (temp->alive_bool)
		{
			temp->alive_screams = 0;
			temp->alive_bool = 0;
			temp = temp->next;
		}
		else
		{
			del = temp;
			temp = temp->next;
			kill_pc_n_del_from_list(vm, del);
		}
	}
	i = -1;
	while (++i < (int)vm->num_of_players)
		vm->players[i].alives = 0;
}
