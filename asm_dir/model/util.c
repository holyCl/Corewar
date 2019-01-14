/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:09:04 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 17:09:06 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_wordlen(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	return (len);
}

int		ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

void	iterate_asm_str(t_asm_str **asm_str)
{
	(*asm_str)->codage = 1;
	(*asm_str)->size += 1;
}

char	is_empty_str(char *str)
{
	if (str && *str)
	{
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		if (*str && *str != COMMENT_CHAR)
			return (FALSE);
	}
	return (TRUE);
}

int		open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}
