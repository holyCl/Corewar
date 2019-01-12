/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_read_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:09:33 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 16:09:35 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	calculate_exe_size(t_header *header, t_asm_str **asm_str)
{
	unsigned int	exe_size;
	t_asm_str		*str;

	exe_size = 0;
	str = *asm_str;
	while (str)
	{
		exe_size += str->size;
		str = str->next;
	}
	header->prog_size = exe_size;
}

void	handle_read_data(t_header *header, t_asm_str **asm_str)
{
	find_labels_addresses(asm_str);
	calculate_exe_size(header, asm_str);
}
