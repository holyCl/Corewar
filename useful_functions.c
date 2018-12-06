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

void	error_exit(char *str, int fd)
{
    if (ft_strcmp("Usage!", str) == 0)
    {
        ft_printf("Usage:\n./corewar [-dump nbr_cycles] ");
        ft_printf("[[-n number] champion1.cor] ...\n");
    }
    else if (str)
        write(1, str, ft_strlen(str));
    if (fd >= 0)
        close(fd);
    exit(0);
}

unsigned int		get_arguments(t_vm *vm, unsigned int *cur_pos, int label)
{
    unsigned int	ret;

    ret = 0;
    if (label == 1)
        ret = vm->map[++(*cur_pos) % MEM_SIZE];
    else if (label == 2)
        ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 8) | vm->map[++(*cur_pos) % MEM_SIZE];
    else if (label == 4)
    {
        ret = (vm->map[++(*cur_pos) % MEM_SIZE] << 24) | (vm->map[++(*cur_pos) % MEM_SIZE] << 16) |
              (vm->map[++(*cur_pos) % MEM_SIZE] << 8) | (vm->map[++(*cur_pos) % MEM_SIZE]);
    }
    return (ret);
}

void				decodage_opcode(unsigned char codage, int *array, int max)
{
    unsigned char	check;
    int	            i;

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
    // printf("%d\n", array[0]);
    // printf("%d\n", array[1]);
    // printf("%d\n", array[2]);
}

void 				ft_bzero_int_arr(int *args_array, const int max)
{
    int 			i;

    i = 0;
    while (i < max)
    {
        args_array[i] = 0;
        i++;
    }
}

t_pc				*create_pc(t_vm *vm, t_player *player, unsigned int position)
{
    t_pc			*new_node;

    new_node = (t_pc *)malloc(sizeof(t_pc));
    if (!new_node)
        error_exit("Error during creating new process", -1);
    ft_bzero(new_node, sizeof(t_pc));
    ft_bzero(new_node->reg, REG_NUMBER);
    new_node->reg[0] = player->player_number;
    new_node->player_id = player->id;
    new_node->cur_pos = position;
    new_node->cycles_to_go = -1;
    new_node->alive_bool = 1;
    new_node->command = player->exec_code[0];
    //color here! need to change it!
    new_node->color = player->id + 1;
    if (vm->pc_head)
    {
        vm->pc_head->prev = new_node;
        new_node->next = vm->pc_head;
    }
    vm->pc_head = new_node;
    new_node->prev = NULL;
    new_node->pc_number = (new_node->next) ? (new_node->next->pc_number + 1) : 1;
    return (new_node);
}

