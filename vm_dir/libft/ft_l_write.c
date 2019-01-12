/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:38:44 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:39:04 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_lu(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.uli = va_arg(ap, unsigned long int);
	s = ft_itoa_b_u(pf->u_n.uli, 10);
	pf->u_n.uli == 0 ? pf->null = 1 : 0;
	len = (int)ft_strlen(s);
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

int			write_zu(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.st = va_arg(ap, unsigned long long);
	s = ft_itoa_b_u(pf->u_n.st, 10);
	len = (int)ft_strlen(s);
	pf->u_n.st == 0 ? pf->null = 1 : 0;
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

static void	write_ud_help_fin(t_prf *pf, int *res, int *un, char *s)
{
	int		len;

	len = (int)ft_strlen(s);
	if (pf->dot && pf->pre == 0 && pf->null && pf->wid && pf->zero == 0)
		(*res) += (int)write(1, " ", 1);
	else if (pf->wipre && pf->wid == 0 && pf->pre == 0 && pf->null)
		;
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

int			write_h_big_d(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.uli = va_arg(ap, unsigned long int);
	pf->u_n.uli == 0 ? pf->null = 1 : (0);
	s = ft_itoa_b_s(pf->u_n.uli, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.uli, 10);
	write_ud_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int			write_ll_big_d(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.ulli = va_arg(ap, unsigned long long int);
	pf->u_n.ulli == 0 ? pf->null = 1 : (0);
	s = ft_itoa_b_s(pf->u_n.ulli, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.ulli, 10);
	write_ud_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}
