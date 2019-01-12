/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:57:33 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/07 19:56:46 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char *b;
	char *l;

	if (!*little)
		return ((void *)big);
	while (*big)
	{
		if (*big == *little)
		{
			b = (void *)big + 1;
			l = (void *)little + 1;
			while (*b && *l && *b == *l)
			{
				++b;
				++l;
			}
			if (!*l)
				return ((void *)big);
		}
		big++;
	}
	return (NULL);
}
