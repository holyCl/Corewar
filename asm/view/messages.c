/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:49:55 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 14:50:01 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	display_error_message(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
}

void	error_type(char *line, int nb)
{
	ft_putstr(line);
	ft_printf(" in line %d\n", nb);
	exit(1);
}
