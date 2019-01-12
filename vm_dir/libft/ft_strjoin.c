/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:43:53 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/07 20:22:20 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	fresh = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (fresh == NULL)
		return (0);
	while (*s1)
	{
		fresh[i++] = *s1++;
	}
	while (*s2)
	{
		fresh[i++] = *s2++;
	}
	fresh[i++] = '\0';
	return (fresh);
}
