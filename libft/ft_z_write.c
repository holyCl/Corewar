/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_z_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:08:57 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:09:12 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_zx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.st = va_arg(ap, size_t);
	s = ft_itoa_base(pf->u_n.st, 16);
	pf->u_n.st == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	pf->hex = 1;
	(pf->hash && pf->wid > len && pf->minus && pf->zero) ? pf->zero = 0 : 0;
	if (pf->wid > 0)
		write_x_help(pf, &res, &un, len);
	(pf->hash && pf->null == 0) ? res += (int)write(1, "0x", 2) : (0);
	if ((pf->pre > 0) && (pf->pre >= len))
		res = precision_write(&(*pf), res, pf->pre - len, len);
	if (pf->wipre > 0 && pf->pre == 0 && pf->null && pf->wid > 0)
		res += (int)write(1, " ", 1);
	else if (pf->wipre > 0 && pf->wid == 0 && pf->pre == 0 && pf->null)
		;
	else
		res += (int)write(1, s, len);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_zo(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.st = va_arg(ap, size_t);
	s = ft_itoa_base(pf->u_n.st, 8);
	len = (int)ft_strlen(s);
	pf->u_n.st == 0 ? pf->null = 1 : 0;
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash > 0 && pf->null == 0) ? res += (int)write(1, "0", 1) : (0);
	(!pf->null) ? res += (int)write(1, s, len) : 0;
	if (pf->null && (pf->wipre == 0 || (pf->wipre && pf->hash)))
		res += (int)write(1, "0", 1);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_u(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.u = va_arg(ap, unsigned int);
	s = ft_itoa_base(pf->u_n.u, 10);
	pf->u_n.u == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	if (pf->wid > 0)
		write_u_help(pf, &res, &un, len);
	if (pf->dot && pf->wid >= pf->pre && pf->pre > len && pf->null)
		res = precision_write(&(*pf), res, (pf->pre - len + 1), len);
	else if ((pf->pre > 0) && (pf->pre >= len))
		res = precision_write(&(*pf), res, pf->pre - len, len);
	if (pf->u_n.u == 0 && pf->wipre)
		;
	else
		res += (int)write(1, s, len);
	if (pf->minus > 0)
		res = wid_write(&(*pf), res, un, len);
	ft_strdel(&s);
	return (res);
}

void		write_o_help(t_prf *pf, int *un, int len, int *res)
{
	if (pf->hash && pf->wid > pf->pre && pf->null && pf->pre)
		pf->pre++;
	if (pf->wid <= pf->pre && pf->pre > len)
		pf->wid = 0;
	else if (pf->wid > pf->pre && pf->pre > 0 && pf->pre >= len)
		(*un) = pf->wid - pf->pre;
	else
		(*un) = (pf->wid - len);
	pf->hash > 0 ? (*un)-- : (0);
	pf->null ? (*un)++ : (0);
	if (pf->hash && pf->wid >= pf->pre && pf->pre > len && pf->dot)
		(*un)++;
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, len) : (0);
	if (pf->dot && pf->wid >= pf->pre && pf->hash)
		(*res) = precision_write(&(*pf), *res, pf->pre - len + 1, len);
	else if (pf->pre && pf->pre >= len)
		(*res) = precision_write(&(*pf), *res, pf->pre - len, len);
}
