/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hh_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:36:17 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:36:34 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_hhx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uc = (unsigned char)va_arg(ap, int);
	s = ft_itoa_base(pf->u_n.uc, 16);
	pf->u_n.uc == 0 ? pf->null = 1 : 0;
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

int			write_hho(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uc = (unsigned char)va_arg(ap, int);
	s = ft_itoa_b_u(pf->u_n.uc, 8);
	len = (int)ft_strlen(s);
	pf->u_n.uc == 0 ? pf->null = 1 : 0;
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash > 0 && pf->u_n.ush != 0) ? res += (int)write(1, "0", 1) : (0);
	(!pf->null) ? res += (int)write(1, s, len) : 0;
	if (pf->null && (pf->wipre == 0 || (pf->wipre && pf->hash)))
		res += (int)write(1, "0", 1);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_hh_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uc = (unsigned char)va_arg(ap, int);
	s = ft_itoa_b_u_up(pf->u_n.uc, 16);
	pf->hex = 1;
	pf->u_n.uc == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	(pf->hash && pf->wid > len && pf->minus && pf->zero) ? pf->zero = 0 : 0;
	if (pf->wid > 0)
		write_big_x_help(pf, &res, &un, len);
	(pf->hash > 0 && pf->null == 0) ? res += (int)write(1, "0X", 2) : (0);
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

int			write_hh_big_o(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ush = (unsigned short)va_arg(ap, int);
	s = ft_itoa_base(pf->u_n.ush, 8);
	pf->u_n.ush == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
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

int			write_jo(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uim = va_arg(ap, uintmax_t);
	s = ft_itoa_base(pf->u_n.uim, 8);
	len = (int)ft_strlen(s);
	pf->u_n.uim == 0 ? pf->null = 1 : 0;
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
