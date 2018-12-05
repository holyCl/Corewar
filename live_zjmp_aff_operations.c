/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_aff_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:50:01 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/05 20:50:03 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				live_op(t_vm *vm, t_pc *process, unsigned int cycles_count)//“A process shows that player X (champion_name) is alive"
{
    unsigned int	tmp_pos;
    unsigned int	temp;
    unsigned int	check_int;

//printf("live_op(%u). at pos=%u;\n", cycles_count, process->cur_pos);

    tmp_pos = process->cur_pos;
    // decode_args(args_array, codage, max_args);
    if (process->alive_bool == 0)
        process->alive_bool = 1;
    process->alive_screams++;
    check_int = vm->players[process->player_id].player_number;
    temp = get_arguments(vm, &tmp_pos, 4);
    // printf("live arg=%u\n", temp);
    if (check_int == temp)
    {

//    //delete me!
//         ft_printf("A process shows that player %d (%s) is alive\n",
//         	vm->players[process->player_id].id, vm->players[process->player_id].name);

        vm->players[process->player_id].alives++;
        vm->players[process->player_id].last_cycle_alive = cycles_count;
        vm->last_player_alive_id = process->player_id;


//printf("ALive(%u) at %u cycle\n", vm->players[process->player_id].alives, cycles_count);
    }
    process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
    process->cycles_to_go = -1;
}

void				zjmp_op(t_vm *vm, t_pc *process)
{
    unsigned int	tmp_pos;
    short			check_int;

    tmp_pos = process->cur_pos;
    check_int = (short)tmp_pos;
    check_int += ((short)get_arguments(vm, &tmp_pos, 2) % IDX_MOD);
    if (process->carry == 1)
    {
        if (check_int < 0)
        {
            check_int = MEM_SIZE + check_int;
            process->cur_pos = ((check_int) % MEM_SIZE);
        }
        else
            process->cur_pos = ((check_int) % MEM_SIZE); //was + tmp_pos
    }
    else
        process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
    process->cycles_to_go = -1;
}

void				aff_op(t_vm *vm, t_pc *process)
{
    unsigned int	tmp_pos;
    int				opcode;
    unsigned char	ret;

    tmp_pos = process->cur_pos;
    opcode = 0;
    decodage_opcode(vm->map[++tmp_pos], &opcode, 1);
    if (opcode == REG_CODE)
    {
        ret = (unsigned char)get_arguments(vm, &tmp_pos, 1);
        if (ret >= 1 && ret <= 16)
            ret = process->reg[ret - 1] % 256;
        if (vm->dump_flag == 0 && ret >= 1 && ret <= 16) //&& no visualization
            ft_printf("%c\n");
    }
    process->cur_pos = (tmp_pos + 1) % MEM_SIZE;
    process->cycles_to_go = -1;
}
