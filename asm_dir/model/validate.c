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

void	valid_label(char *asm_str, int nb, char *src)
{
	int i;

	i = -1;
	while (asm_str[++i])
	{
		if (!ft_strchr(LABEL_CHARS, asm_str[i]))
			error_type(INC_LABELNAME, nb, src);
	}
}
