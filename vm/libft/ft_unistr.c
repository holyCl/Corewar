/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unistr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:22:36 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/13 16:22:47 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_unistrlen(const unsigned int *str, int flag)
{
	unsigned char	tmp;
	int				res;
	int				i;

	i = 0;
	res = 0;
	while (str[i])
	{
		tmp = ft_dec_to_bin(str[i]);
		if (tmp <= 7)
			res++;
		else if (tmp <= 11)
			res += 2;
		else if (tmp <= 16)
			res += 3;
		else
			res += 4;
		i++;
	}
	if (flag == 1)
		return (i);
	return (res);
}

static int			ft_unipre(const unsigned int *str, t_prf *pf)
{
	unsigned char	tmp;
	int				prec;
	int				i;

	i = 0;
	prec = 0;
	while (str[i])
	{
		tmp = ft_dec_to_bin(str[i]);
		if (tmp <= 7)
			pf->unicount++;
		else if (tmp <= 11)
			pf->unicount += 2;
		else if (tmp <= 16)
			pf->unicount += 3;
		else
			pf->unicount += 4;
		i++;
		if (pf->unicount > pf->pre && pf->dot)
			return (prec);
		prec = i;
	}
	return (prec);
}

static int			unistr_wid_help(t_prf *pf, int *un, int len, int unimax)
{
	int				res;

	res = 0;
	if (pf->pre && pf->wid > pf->pre)
	{
		if (pf->pre < len)
			(*un) = pf->wid - pf->pre;
		else
			(*un) = pf->wid - len;
	}
	else if (pf->wid > len)
		if (pf->dot)
			(*un) = (pf->wid - unimax);
		else
			(*un) = (pf->wid - len);
	else if (pf->pre == 0 && pf->dot && pf->wid)
		(*un) = pf->wid - 1;
	if (pf->pre < len && pf->dot && pf->wid > pf->pre && pf->pre != 1)
		(*un)++;
	pf->minus == 0 ? res = wid_write(&(*pf), res, (*un), len) : 0;
	return (res);
}

int					unistr_write(va_list ap, int res, t_prf *pf, int un)
{
	unsigned int	*str;
	int				len;
	int				unimax;

	str = va_arg(ap, unsigned int*);
	if (!str)
	{
		res += (int)write(1, "(null)", 6);
		return (res);
	}
	len = ft_unistrlen(str, 0);
	unimax = ft_unipre(str, &(*pf));
	if (pf->wid)
		res += unistr_wid_help(pf, &un, len, unimax);
	while (*str)
	{
		if (unimax == 0 && pf->pre < len && pf->dot)
			break ;
		res = unichr_write(*str, res);
		str++;
		unimax--;
	}
	(pf->wid > len && pf->minus) ? res = wid_write(&(*pf), res, un, len) : 0;
	return (res);
}

int					wr_big_uni_c(unsigned int v, int res, t_prf *pf, int un)
{
	int				tmp;
	int				len;

	len = 0;
	if (!v)
	{
		res += (int)write(1, "(null)", 6);
		return (res);
	}
	tmp = ft_dec_to_bin((int)v);
	if (tmp <= 7)
		len++;
	else if (tmp <= 11)
		len += 2;
	else if (tmp <= 16)
		len += 3;
	else
		len += 4;
	if (pf->wid)
		res += unistr_wid_help(pf, &un, len, 1);
	res = unichr_write(v, res);
	(pf->wid > len && pf->minus) ? res = wid_write(&(*pf), res, un, len) : 0;
	return (res);
}
