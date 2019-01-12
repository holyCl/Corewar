/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:52:31 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/16 15:52:47 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_just_magic(uintmax_t *n, int base)
{
	char	str;

	str = *n % base + '0';
	*n /= base;
	if (str > '9')
		return (str + 7);
	return (str);
}

static int	ft_len_math(uintmax_t n, int base)
{
	int		res;

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

char		*ft_itoa_b_u_up(uintmax_t n, int base)
{
	char	*str;
	int		i;
	int		len;

	if (base < 2 || base > 16)
		return (NULL);
	len = ft_len_math(n, base);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (i++ < len)
		str[i] = ft_just_magic(&n, base);
	*(str + len) = '\0';
	ft_reverse_str(str);
	return (str);
}
