/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:46:34 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/11 17:42:03 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ws_len(char const *s)
{
	size_t	j;
	size_t	i;
	size_t	n;

	j = ft_strlen((char *)s) - 1;
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		if (s[i] == '\0')
			return (0);
	}
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	n = j - i + 1;
	return (n);
}

char		*ft_strtrim(char const *s)
{
	char	*cp;
	size_t	i;
	size_t	j;
	size_t	n;

	if (s == NULL)
		return (NULL);
	n = ft_ws_len(s);
	cp = (char*)malloc(sizeof(char) * (n + 1));
	i = 0;
	j = 0;
	if (cp == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[i] && j < n)
	{
		cp[j] = s[i];
		i++;
		j++;
	}
	cp[j] = '\0';
	return (cp);
}
