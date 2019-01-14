/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:06:35 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 16:06:37 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		count_char_occur(char *str, char c)
{
	int		nb;

	nb = 0;
	while (*str)
	{
		if (*str == c)
			nb++;
		str++;
	}
	return (nb);
}

char	*cut_content(char *str)
{
	char	*str_end;

	if ((str = ft_strchr(str, '"')) == NULL)
		return (NULL);
	++str;
	if ((str_end = ft_strchr(str, '"')) == NULL)
		return (NULL);
	++str_end;
	if (!is_empty_str(str_end))
		return (NULL);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}
