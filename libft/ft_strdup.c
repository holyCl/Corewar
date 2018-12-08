/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:40:37 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/11 15:32:39 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	if (s != NULL)
	{
		while (j < i)
		{
			s[j] = s1[j];
			j++;
		}
		s[j] = '\0';
	}
	return (s);
}
