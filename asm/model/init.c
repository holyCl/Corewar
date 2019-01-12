/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:30:07 by akorzhak          #+#    #+#             */
/*   Updated: 2018/09/29 18:30:09 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init(void *s)
{
	ft_bzero(s, sizeof(s));
}

void	init_header(t_header *header)
{
	init(header);
	ft_bzero(header->prog_name, sizeof(header->prog_name));
	ft_bzero(header->comment, sizeof(header->comment));
	header->magic = COREWAR_EXEC_MAGIC;
}
