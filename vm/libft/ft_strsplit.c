/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:16:40 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/17 20:44:36 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numw(const char *str, char c)
{
	size_t i;
	size_t num;

	i = 0;
	num = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			num++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (num);
}

static size_t	ft_slen(const char *s, char c)
{
	size_t	m;

	m = 0;
	while (*s == c)
		s++;
	while (*s != c && *s != '\0')
	{
		m++;
		s++;
	}
	return (m);
}

static char		*ft_sword(const char *s, char c)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_slen(s, c) + 1));
	if (new == NULL)
		return (NULL);
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

static char		**ft_freeptr(char **ret, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	char	*word;
	size_t	n;
	size_t	j;

	if (s == NULL)
		return (NULL);
	n = ft_numw(s, c);
	if (!(ret = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	j = 0;
	while (j < n)
	{
		while (*s == c && *s)
			s++;
		word = ft_sword(s, c);
		if (!word)
			ft_freeptr(ret, j);
		while (*s != c && *s)
			s++;
		ret[j] = word;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
