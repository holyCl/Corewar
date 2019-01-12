/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 14:07:50 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/07 18:20:25 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (s == NULL || f == NULL)
		return (0);
	i = 0;
	j = ft_strlen(s);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	while (i < j)
	{
		str[i] = f(s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
