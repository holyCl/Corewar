/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:43:56 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/16 17:44:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				write_d_help_d(t_prf *pf, int *res, int *un, int len)
{
	if (pf->space && pf->wid <= pf->pre && pf->pre > len)
		(*res) += (int)write(1, " ", 1);
	else if (pf->space && pf->wid < 1 && pf->pre < 1 && pf->u_n.i)
		(*res) += (int)write(1, " ", 1);
	else if (pf->space && pf->wid > len && pf->zero)
		(*res) += (int)write(1, " ", 1);
	(pf->wid > len && pf->pre && pf->sign && pf->pre < len) ? pf->wid-- : 0;
	pf->wid ? write_d_help(&(*pf), len, (*un), &(*res)) : 0;
	if (pf->plus && (pf->wid == 0 || pf->wid < pf->pre) && pf->null == 0)
		(*res) += (int)write(1, "+", 1);
	if (pf->pre && pf->pre >= len)
		(*res) = precision_write(&(*pf), (*res), pf->pre - len, len);
	if (pf->plus && (pf->pre < pf->wid || (pf->wipre == 0 && pf->null)))
		(*res) += (int)write(1, "+", 1);
	if (pf->sign && (pf->wid > len || pf->pre > len))
		(pf->minsign && pf->zero == 0) ? (*res) += (int)write(1, "-", 1) : (0);
	else if (pf->sign && pf->wid == 0 && pf->pre == 0)
		(*res) += (int)write(1, "-", 1);
	else if (pf->sign && pf->dot && (pf->wid == len || pf->pre <= len))
		(pf->minus == 0) ? (*res) += (int)write(1, "-", 1) : (0);
	return (len);
}

void			write_d_help_fin(t_prf *pf, int *res, int *un, char *s)
{
	int			len;

	len = (int)ft_strlen(s);
	if (pf->dot && pf->pre == 0 && pf->null && pf->wid && pf->zero == 0)
		(*res) += (int)write(1, " ", 1);
	else if (pf->wipre && pf->wid == 0 && pf->pre == 0 && pf->null)
		;
	else if (ft_strcmp(s, "-2147483648") == 0)
		(*res) += (int)write(1, "2147483648", len - 1);
	else if (ft_strcmp(s, "-9223372036854775808") == 0)
		(*res) += (int)write(1, "9223372036854775808", len - 1);
	else if (ft_strcmp(s, "32768") == 0)
		(*res) += (int)write(1, "32768", len);
	else if (ft_strcmp(s, "-32768") == 0)
		(*res) += (int)write(1, "32768", len - 1);
	else
		(*res) += (int)write(1, s, len);
	if (pf->minus > 0)
	{
		pf->zero > 0 ? pf->zero = 0 : (0);
		pf->minus = 0;
		pf->decrem == 0 ? pf->decrem = 1 : pf->decrem++;
		write_d_help(&(*pf), len, *un, &(*res));
	}
}

void			write_x_help(t_prf *pf, int *res, int *un, int len)
{
	if (pf->wid > pf->pre && pf->pre > 0 && pf->pre >= len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid <= pf->pre && pf->pre >= len)
		(*un) = 0;
	else
		(*un) = (pf->wid - len);
	pf->hash > 0 ? (*un)-- : (0);
	if (pf->hex && pf->hash && pf->zero)
	{
		(*res) += (int)write(1, "0x", 2);
		pf->hash = 0;
		(*un)--;
	}
	if (pf->hash && pf->wid > pf->pre && pf->null && pf->pre)
		(*un) += 2;
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, len) : (0);
}

void			write_big_x_help(t_prf *pf, int *res, int *un, int len)
{
	if (pf->wid > pf->pre && pf->pre > 0 && pf->pre >= len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid <= pf->pre && pf->pre >= len)
		(*un) = 0;
	else
		(*un) = (pf->wid - len);
	pf->hash > 0 ? (*un)-- : (0);
	if (pf->hex && pf->hash && pf->zero)
	{
		(*res) += (int)write(1, "0X", 2);
		pf->hash = 0;
		(*un)--;
	}
	if (pf->hash && pf->wid > pf->pre && pf->null && pf->pre)
		(*un) += 2;
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, len) : (0);
}

void			write_u_help(t_prf *pf, int *res, int *un, int len)
{
	if (pf->wid <= pf->pre && pf->pre > 0 && pf->pre >= len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid > pf->pre && pf->pre && pf->pre > len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid <= pf->pre && pf->pre >= len)
		(*un) = 0;
	else
		(*un) = (pf->wid - len);
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, len) : (0);
}
