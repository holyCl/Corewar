/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uni_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:52:55 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:53:19 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_dec_to_bin(unsigned int i)
{
	int				res;
	int				tmp;

	tmp = i;
	res = 0;
	while (tmp > 0)
	{
		tmp = tmp / 2;
		res++;
	}
	return (res);
}

static int			unichr_two(unsigned int ui, int res, unsigned char chr)
{
	unsigned int	m1;
	unsigned char	o2;
	unsigned char	o1;

	m1 = 49280;
	o2 = (ui << 26) >> 26;
	o1 = ((ui >> 6) << 27) >> 27;
	chr = (m1 >> 8) | o1;
	res += (int)write(1, &chr, 1);
	chr = ((m1 << 24) >> 24) | o2;
	res += (int)write(1, &chr, 1);
	return (res);
}

static int			unichr_three(unsigned int ui, int res, unsigned char chr)
{
	unsigned int	m2;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;

	m2 = 14712960;
	o3 = (ui << 26) >> 26;
	o2 = ((ui >> 6) << 26) >> 26;
	o1 = ((ui >> 12) << 28) >> 28;
	chr = (m2 >> 16) | o1;
	res += (int)write(1, &chr, 1);
	chr = ((m2 << 16) >> 24) | o2;
	res += (int)write(1, &chr, 1);
	chr = ((m2 << 24) >> 24) | o3;
	res += (int)write(1, &chr, 1);
	return (res);
}

static int			unichr_four(unsigned int ui, int res, unsigned char chr)
{
	unsigned int	m3;
	unsigned char	o4;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;

	m3 = 4034953344;
	o4 = (ui << 26) >> 26;
	o3 = ((ui >> 6) << 26) >> 26;
	o2 = ((ui >> 12) << 26) >> 26;
	o1 = ((ui >> 18) << 29) >> 29;
	chr = (m3 >> 24) | o1;
	res += (int)write(1, &chr, 1);
	chr = ((m3 << 8) >> 24) | o2;
	res += (int)write(1, &chr, 1);
	chr = ((m3 << 16) >> 24) | o3;
	res += (int)write(1, &chr, 1);
	chr = ((m3 << 24) >> 24) | o4;
	res += (int)write(1, &chr, 1);
	return (res);
}

int					unichr_write(unsigned int v, int res)
{
	unsigned char	chr;
	int				size;

	chr = 0;
	size = ft_dec_to_bin(v);
	if (size <= 7)
	{
		chr = v;
		res += (int)write(1, &chr, 1);
	}
	else if (size <= 11)
	{
		res = unichr_two(v, res, chr);
	}
	else if (size <= 16)
	{
		res = unichr_three(v, res, chr);
	}
	else
	{
		res = unichr_four(v, res, chr);
	}
	return (res);
}
