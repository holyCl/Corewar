/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:27:56 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/07 20:21:38 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cint(int n)
{
	if ((n > 9) || (n < -9))
	{
		return (ft_cint(n / 10) + 1);
	}
	else if ((n >= 0 && n <= 9) || (n < 0 && n >= -9))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static char	*ft_str_wr(char *s, int n, int sign, int num)
{
	int i;

	i = num - 1;
	while (i > 0)
	{
		s[i] = (n % 10) * sign + '0';
		n = n / 10;
		i--;
	}
	if (sign != -1)
		s[i] = (n % 10) * sign + '0';
	s[num] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		num;
	int		sign;

	num = ft_cint(n);
	if (n < 0)
		num++;
	s = (char *)malloc(sizeof(char) * (num + 1));
	if (s == NULL)
		return (0);
	if (s)
	{
		sign = 1;
		if (n < 0)
		{
			s[0] = '-';
			sign = -1;
		}
		if (n == 0)
			s[0] = '0';
		s = ft_str_wr(s, n, sign, num);
	}
	return (s);
}
