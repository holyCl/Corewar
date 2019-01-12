/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:15:48 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 17:15:50 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		validate_header(t_header *header)
{
	if (header->prog_name[0] == '\0' || header->comment[0] == '\0')
		return (ERROR);
	return (OK);
}
