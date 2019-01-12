/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:50:07 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:50:20 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		wid_handle(const char **format, va_list ap, t_prf *pf)
{
	int		i;

	pf->wipre == 0 ? pf->wipre = 1 : (0);
	i = 0;
	if (**format == '*')
	{
		pf->wid = va_arg(ap, int);
		if (pf->wid < 0)
		{
			pf->minus = 1;
			pf->wid *= (-1);
		}
	}
	else if (**format >= '1' && **format <= '9')
	{
		while (**format >= '0' && **format <= '9')
		{
			i *= 10;
			i += **format - '0';
			(*format)++;
		}
		(*format)--;
		pf->wid = i;
	}
}

int			write_d_help(t_prf *pf, int len, int un, int *res)
{
	if (pf->sign && pf->wid && pf->minus == 0 && pf->pre == 0 && pf->zero == 0)
		pf->minsign = 1;
	else if (pf->sign && pf->wid > pf->pre && pf->wid > len)
		pf->minsign = 1;
	if (pf->wid > pf->pre && pf->pre > 0 && pf->pre >= len)
		un = pf->wid - pf->pre;
	else if (pf->wid <= pf->pre && pf->pre >= len)
		un = 0;
	else
		un = (pf->wid - len);
	if (pf->sign && pf->minus && pf->wid > pf->pre)
	{
		(*res) += (int)write(1, "-", 1);
		pf->minsign ? pf->minsign = 0 : 0;
	}
	if (pf->plus > 0 && pf->zero > 0 && pf->wid > 0)
	{
		pf->sign == 0 ? (*res) += (int)write(1, "+", 1) : (0);
		pf->plus = 0;
		pf->decrem = 1;
		(pf->sign == 0) ? un-- : (0);
	}
	(pf->hash && pf->wid > pf->pre && pf->null && pf->pre) ? un++ : 0;
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, un, len) : (0);
	return (*res);
}

static int	sign_cor_wid_write(t_prf *pf, int res, int *un, int len)
{
	(pf->sign && pf->wid > pf->pre && pf->pre > len) ? (*un)-- : 0;
	if (pf->sign && pf->wid && pf->zero)
	{
		res += (int)write(1, "-", 1);
		pf->minsign ? pf->minsign = 0 : 0;
	}
	else if ((pf->sign && pf->wid > pf->pre && pf->pre))
		(*un)--;
	else if (pf->decrem && pf->sign)
		(*un)--;
	else if (pf->dcrmnt || (pf->space && pf->wid > len && pf->zero))
		(*un)--;
	else if (pf->sign && pf->minus && pf->wid > pf->pre)
	{
		res += (int)write(1, "-", 1);
		pf->minsign ? pf->minsign = 0 : 0;
	}
	(pf->decrem && pf->sign && pf->dot == 0 && pf->wid >= len) ? (*un)++ : 0;
	if (pf->hash && pf->wid > pf->pre && pf->pre > len && pf->dot && !pf->null)
		(*un)++;
	else if (pf->minsign && pf->wid > len && pf->pre && pf->wid > pf->pre)
		(*un)++;
	else if (pf->wid >= len && pf->sign && (pf->pre == 0 || pf->pre < len))
		(*un)--;
	return (res);
}

int			wid_write(t_prf *pf, int res, int un, int len)
{
	if (un > 0)
	{
		if ((pf->plus && pf->sign == 0) || (pf->hash && pf->octal == 0))
			un--;
		if (pf->plus > 0 && pf->wid <= len)
		{
			pf->sign == 0 ? res += (int)write(1, "+", 1) : un++;
			pf->null < 1 ? pf->plus = 0 : (0);
			pf->null < 1 ? un-- : (0);
		}
		res = sign_cor_wid_write(&(*pf), res, &un, len);
		while (un)
		{
			if (pf->zero && pf->pre == 0 && pf->dot && (pf->dioux || pf->doux))
				res += (int)write(1, " ", 1);
			else if (pf->zero && (pf->wid < 1 || pf->pre < 1))
				res += (int)write(1, "0", 1);
			else if ((pf->sign || pf->plus) && pf->wid && pf->zero)
				res += (int)write(1, "0", 1);
			else
				res += (int)write(1, " ", 1);
			un--;
		}
	}
	return (res);
}
