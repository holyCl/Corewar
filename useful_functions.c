/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:30:19 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/05 21:30:35 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				parse_exec_code(int fd, t_player *player)
{
	ssize_t			rd;
	unsigned char	check[1];
	int				i;

	i = player->size + 1;
	player->exec_code = (unsigned char *)malloc(sizeof(unsigned char) * (i));
	if (!player->exec_code)
		error_exit("Error while executable code parsing\n", fd);
	rd = read(fd, player->exec_code, player->size);
	if (rd != (ssize_t)player->size)
		error_exit("Error executable reading.\n", fd);
	if (read(fd, &check, 1) != 0)
	{
		printf("player='%s'\n", player->name);
		error_exit("Not null after exec, its not so good mate.", fd);
	}
}

unsigned int		get_arguments(t_vm *vm, unsigned int *pos, int label)
{
	unsigned int	ret;

	ret = 0;
	if (label == 1)
		ret = vm->map[++(*pos) % MEM_SIZE];
	else if (label == 2)
		ret = (vm->map[++(*pos) % MEM_SIZE] << 8) |
		vm->map[++(*pos) % MEM_SIZE];
	else if (label == 4)
	{
		ret = (vm->map[++(*pos) % MEM_SIZE] << 24) |
		(vm->map[++(*pos) % MEM_SIZE] << 16) |
		(vm->map[++(*pos) % MEM_SIZE] << 8) | (vm->map[++(*pos) % MEM_SIZE]);
	}
	return (ret);
}

void				decodage_opcode(unsigned char codage, int *array, int max)
{
	unsigned char	check;
	int				i;

	i = 0;
	while (codage && i < max)
	{
		check = codage & 192;
		if (check == 64)
			array[i] = REG_CODE;
		else if (check == 128)
			array[i] = DIR_CODE;
		else if (check == 192)
			array[i] = IND_CODE;
		else
			array[i] = 0;
		codage <<= 2;
		i++;
	}
}

void				ft_bzero_int_arr(int *args_array, const int max)
{
	int				i;

	i = 0;
	while (i < max)
	{
		args_array[i] = 0;
		i++;
	}
}

t_pc				*create_pc(t_vm *vm, t_player *player, unsigned int pos)
{
	t_pc			*new;

	new = (t_pc *)malloc(sizeof(t_pc));
	if (!new)
		error_exit("Error during creating new process", -1);
	ft_bzero(new, sizeof(t_pc));
	ft_bzero(new->reg, REG_NUMBER);
	new->reg[0] = player->player_number;
	new->player_id = player->id;
	new->cur_pos = pos;
	new->cycles_to_go = -1;
	new->alive_bool = 1;
	new->command = player->exec_code[0];
	new->color = player->id + 1;
	if (vm->pc_head)
	{
		vm->pc_head->prev = new;
		new->next = vm->pc_head;
	}
	vm->pc_head = new;
	new->prev = NULL;
	new->pc_number = (new->next) ? (new->next->pc_number + 1) : 1;
	return (new);
}
