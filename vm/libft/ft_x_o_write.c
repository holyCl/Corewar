/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_o_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 13:58:20 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/13 13:58:38 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_x(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.i = va_arg(ap, int);
	pf->hex = 1;
	pf->u_n.i == 0 ? pf->null = 1 : 0;
	s = ft_itoa_base_u(pf->u_n.i, 16);
	len = (int)ft_strlen(s);
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

int			write_lx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uli = va_arg(ap, unsigned long int);
	s = ft_itoa_b_u(pf->u_n.uli, 16);
	pf->u_n.uli == 0 ? pf->null = 1 : 0;
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

int			write_llx(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ulli = va_arg(ap, unsigned long long int);
	s = ft_itoa_b_u(pf->u_n.ulli, 16);
	pf->u_n.ulli == 0 ? pf->null = 1 : 0;
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

int			write_o(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.u = va_arg(ap, unsigned int);
	s = ft_itoa_b_u(pf->u_n.u, 8);
	pf->u_n.u == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash > 0 && pf->null == 0) ? res += (int)write(1, "0", 1) : (0);
	pf->u_n.u != 0 ? res += (int)write(1, s, len) : 0;
	if (pf->null && (pf->wipre == 0 || (pf->wipre && pf->hash)))
		res += (int)write(1, "0", 1);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_lo(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.uli = va_arg(ap, unsigned long int);
	s = ft_itoa_b_u(pf->u_n.uli, 8);
	pf->u_n.uli == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash > 0) ? res += (int)write(1, "0", 1) : (0);
	if (pf->null && pf->wipre)
		;
	else
		res += (int)write(1, s, len);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}
