/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 20:42:33 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/30 20:42:35 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_just_magic(intmax_t *n, int base)
{
	char	str;

	str = *n % base + '0';
	*n /= base;
	if (str > '9')
		return (str + 39);
	return (str);
}

static int	ft_len_math(intmax_t n, int base)
{
	int		res;

	if (n < 0 && base == 10)
		res = 2;
	else
		res = 1;
	while (n /= base)
		res++;
	return (res);
}

static void	ft_reverse_str(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char		*ft_itoa_b_s(intmax_t n, int b)
{
	char	*str;
	int		i;
	int		len;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	len = ft_len_math(n, b);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))) || b < 2 || b > 16)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		if (b == 10)
			*(str + len - 1) = '-';
	}
	i = -1;
	while (i++ < len)
	{
		if (*(str + len - 1) == '-' && i == len - 1)
			break ;
		str[i] = ft_just_magic(&n, b);
	}
	*(str + len) = '\0';
	ft_reverse_str(str);
	return (str);
}
