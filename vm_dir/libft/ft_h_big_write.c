/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_h_big_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 21:21:18 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/13 15:47:23 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.i = va_arg(ap, int);
	s = ft_itoa_b_u_l(pf->u_n.i, 16);
	pf->hex = 1;
	pf->u_n.i == 0 ? pf->null = 1 : 0;
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

int			write_j_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ulli = va_arg(ap, unsigned long long);
	s = ft_itoa_b_u_up(pf->u_n.ulli, 16);
	pf->u_n.ulli == 0 ? pf->null = 1 : 0;
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

int			write_l_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uli = va_arg(ap, unsigned long int);
	s = ft_itoa_b_u_up(pf->u_n.uli, 16);
	len = (int)ft_strlen(s);
	pf->u_n.uli == 0 ? pf->null = 1 : 0;
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

int			write_z_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.st = va_arg(ap, size_t);
	s = ft_itoa_b_u_up(pf->u_n.st, 16);
	len = (int)ft_strlen(s);
	pf->u_n.st == 0 ? pf->null = 1 : 0;
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

int			write_h_big_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ush = (unsigned short int)va_arg(ap, int);
	pf->hex = 1;
	pf->u_n.ush == 0 ? pf->null = 1 : 0;
	s = ft_itoa_b_u_up(pf->u_n.ush, 16);
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
