/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_h_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:32:38 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:32:54 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_hhu(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.uc = (unsigned char)va_arg(ap, int);
	s = ft_itoa_base(pf->u_n.uc, 10);
	len = (int)ft_strlen(s);
	pf->u_n.uc == 0 ? pf->null = 1 : 0;
	if (pf->wid > 0)
		write_u_help(pf, &res, &un, len);
	if (pf->dot && pf->wid >= pf->pre && pf->pre > len && pf->null)
		res = precision_write(&(*pf), res, (pf->pre - len + 1), len);
	else if ((pf->pre > 0) && (pf->pre >= len))
		res = precision_write(&(*pf), res, pf->pre - len, len);
	if (pf->null && pf->wipre)
		;
	else
		res += (int)write(1, s, len);
	if (pf->minus > 0)
		res = wid_write(&(*pf), res, un, len);
	ft_strdel(&s);
	return (res);
}

int			write_hu(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.ush = (unsigned short int)va_arg(ap, int);
	s = ft_itoa_b_u(pf->u_n.ush, 10);
	len = (int)ft_strlen(s);
	pf->u_n.ush == 0 ? pf->null = 1 : 0;
	if (pf->wid > 0)
		write_u_help(pf, &res, &un, len);
	if (pf->dot && pf->wid >= pf->pre && pf->pre > len && pf->null)
		res = precision_write(&(*pf), res, (pf->pre - len + 1), len);
	else if ((pf->pre > 0) && (pf->pre >= len))
		res = precision_write(&(*pf), res, pf->pre - len, len);
	if (pf->null && pf->wipre)
		;
	else
		res += (int)write(1, s, len);
	if (pf->minus > 0)
		res = wid_write(&(*pf), res, un, len);
	ft_strdel(&s);
	return (res);
}

int			write_hx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ush = (unsigned short int)va_arg(ap, int);
	pf->hex = 1;
	s = ft_itoa_base(pf->u_n.ush, 16);
	len = (int)ft_strlen(s);
	pf->u_n.ush == 0 ? pf->null = 1 : 0;
	(pf->hash && pf->wid > len && pf->minus && pf->zero) ? pf->zero = 0 : 0;
	if (pf->wid > 0)
		write_x_help(pf, &res, &un, len);
	(pf->hash && pf->null == 0) ? res += (int)write(1, "0x", 2) : (0);
	if ((pf->pre > 0) && (pf->pre >= len))
		res = precision_write(&(*pf), res, pf->pre - len, len);
	if (pf->wipre > 0 && pf->pre == 0 && pf->u_n.uli == 0 && pf->wid > 0)
		res += (int)write(1, " ", 1);
	else if (pf->wipre > 0 && pf->wid == 0 && pf->pre == 0 && pf->null)
		;
	else
		res += (int)write(1, s, len);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_ho(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ush = va_arg(ap, int);
	s = ft_itoa_b_u(pf->u_n.ush, 8);
	pf->u_n.ush == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash > 0 && pf->u_n.ush != 0) ? res += (int)write(1, "0", 1) : (0);
	pf->u_n.ush != 0 ? res += (int)write(1, s, len) : 0;
	if (pf->u_n.ush == 0 && (pf->wipre == 0 || (pf->wipre && pf->hash)))
		res += (int)write(1, "0", 1);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_jx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uim = va_arg(ap, uintmax_t);
	s = ft_itoa_b_u(pf->u_n.uim, 16);
	pf->u_n.uim == 0 ? pf->null = 1 : 0;
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
