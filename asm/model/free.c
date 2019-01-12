/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:20:10 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/29 14:20:13 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		exit_with_error(t_asm *a, char **line, char *error_message)
{
	a->error_message = ft_strdup(error_message);
	ft_strdel(line);
	return (ERROR);
}
