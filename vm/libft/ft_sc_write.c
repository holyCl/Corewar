/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sc_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:43:52 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:44:07 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		write_s_help(t_prf *pf, int *res, int *un, int *len)
{
	if (pf->u_n.s != 0)
		(*len) = (int)ft_strlen(pf->u_n.s);
	else
		(*len) = 0;
	if (pf->wid > 0)
	{
		if (pf->pre > 0 && pf->wid > pf->pre)
		{
			if (pf->pre < *len)
				(*un) = pf->wid - pf->pre;
			else
				(*un) = pf->wid - *len;
		}
		else if (pf->wid > *len)
			(*un) = (pf->wid - *len);
		pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, *len) : 0;
	}
}

int				write_s(va_list ap, t_prf *pf, int res, int un)
{
	int			len;

	pf->u_n.s = va_arg(ap, char*);
	if (pf->u_n.s == NULL && pf->dot == 0)
	{
		res += (int)write(1, "(null)", 6);
		return (res);
	}
	write_s_help(pf, &res, &un, &len);
	if (pf->pre > 0 && pf->pre < len)
		res += (int)write(1, pf->u_n.s, pf->pre);
	else if (pf->dot && pf->wid == 0 && pf->pre == 0)
		;
	else if (pf->pre == 0 && pf->wid > len && pf->dot)
		res = wid_write(&(*pf), res, len, len);
	else
		res += (int)write(1, pf->u_n.s, len);
	pf->minus ? res = wid_write(&(*pf), res, un, len) : 0;
	return (res);
}

int				write_c(int c, t_prf *pf, int res)
{
	pf->u_n.c = c;
	if (pf->wid > 0)
	{
		if (pf->minus == 0)
			res = wid_write(&(*pf), res, pf->wid - 1, 1);
	}
	res += (int)write(1, &pf->u_n.c, 1);
	if (pf->minus > 0)
		res = wid_write(&(*pf), res, pf->wid - 1, 1);
	return (res);
}
