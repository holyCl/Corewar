/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_u_ready_for_rumble.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:52:55 by inazarin          #+#    #+#             */
/*   Updated: 2018/12/06 13:53:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				are_u_ready_for_rumble(t_vm *vm)
{
    unsigned int	cycles_count;
    unsigned int	general_cycles_count;

    cycles_count = 0;
    general_cycles_count = vm->cycles_to_die;
    while (1)
    {

// printf("CUR_cycle=%u\n", cycles_count);

////for debuging purposes
//   if (cycles_count == 21895)
//     printf("NOW!\n");


        if ((vm->cycles_to_die <= 0))
        {
            printf("\n1 ON %u CYCLE!\n", cycles_count);
            end_this_game(vm);
        }
        else if (vm->pc_head == NULL)
        {
            printf("\n2 ON %u CYCLE!\n", cycles_count);
            end_this_game(vm);
        }

        pc_list_checker(vm, cycles_count);

        if (cycles_count == general_cycles_count)
        {
            if (check_players_pc_lives(vm))
            {
                vm->cycles_to_die -= CYCLE_DELTA;
                zero_all_alives_screams(vm);
                vm->max_checks = 0;
                general_cycles_count += vm->cycles_to_die;
            }
            else if (vm->max_checks == 10)
            {
                vm->cycles_to_die -= CYCLE_DELTA;
                zero_all_alives_screams(vm);
                vm->max_checks = 0;
                general_cycles_count += vm->cycles_to_die;
            }
            else
            {
                vm->max_checks++;
                zero_all_alives_screams(vm);
                general_cycles_count += vm->cycles_to_die;
            }
        }
        if (vm->dump_flag == 1 && vm->dump_num <= cycles_count)
        {
        //delete this! number of pc`s count

//            write_cur_map(vm);

//            t_pc	*temp = vm->pc_head;
//            int i = 0;
//            printf("\n>>>processes:\n");
//            while (temp)
//            {
//                i++;
//                ft_printf("%3dpc= %02x, alive= %d; carry=%u; pl=%2d cm=%2u  |||  pos=%4u, before=%02x, after=%02x, %02x,%02x,%02x;  cycle_to_go=%d\n",
//                          temp->pc_number, vm->map[temp->cur_pos], temp->alive_bool, temp->carry, vm->players[temp->player_id].player_number ,temp->command, temp->cur_pos, vm->map[temp->cur_pos - 1], vm->map[temp->cur_pos + 1], vm->map[temp->cur_pos + 2], vm->map[temp->cur_pos + 3], vm->map[temp->cur_pos + 4], temp->cycles_to_go);
// ////                ft_printf("           after+1=%02x, after+2=%02x, after+3=%02x, after+4=%02x, after+5=%02x, after+6=%02x, after+7=%02x\n",
// ////                          vm->map[temp->cur_pos + 2], vm->map[temp->cur_pos + 3], vm->map[temp->cur_pos + 4], vm->map[temp->cur_pos + 5], vm->map[temp->cur_pos + 6], vm->map[temp->cur_pos + 7], vm->map[temp->cur_pos + 8]);
//                temp = temp->next;
//            }
//            printf("pc_sum==%d, CYCLE=%u, CYCLE_TO_DIE=%u\n", i, cycles_count, vm->cycles_to_die);

            // write_cur_map(vm);
            free_vm(vm);
            exit(0);
            // error_exit("\nDUMP IN DA E!\n", -1);
        }
        //delete me
//        printf("On %u Cycle\n", cycles_count);
    

        int c;
        if (vm->visual_flag)
        {
            c = getch();
            if (c == 32)
            {
                if (vm->pause_flag)
                {
                    vm->pause_flag = 0;
                    nodelay(stdscr, true);                        
                }
                else
                {
                    vm->pause_flag = 1;
                    nodelay(stdscr, false);
                }
            }
            else if (c == 27)
            {
                delwin(vm->win);
                delwin(vm->sidebar);
                endwin();
                free_vm(vm);
                exit(0);
            }
            else if (c == 81 || c == 82 || c == 87 || c == 69)
            {
                if (c == 81 && vm->speed <= 9000)
                    vm->speed += 1000;
                else if (c == 82 && vm->speed <= 1000)
                    vm->speed -= 1000;
                else if (c == 87 && vm->speed <= 9000)
                    vm->speed += 100;
                else if (c == 69 && vm->speed <= 1000)
                    vm->speed -= 100;
            }
            cursus_print_map(vm, 0);
            cursus_print_sidebar(vm, cycles_count);
            usleep(vm->speed);
        }
        cycles_count++;
    }
}

