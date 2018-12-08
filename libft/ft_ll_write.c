/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:41:50 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:42:09 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_llo(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->plus > 0 ? pf->plus = 0 : (0);
	pf->u_n.ulli = va_arg(ap, unsigned long long int);
	s = ft_itoa_b_u(pf->u_n.ulli, 8);
	len = (int)ft_strlen(s);
	pf->u_n.ulli == 0 ? pf->null = 1 : 0;
	if (pf->wid > 0 || pf->dot)
		write_o_help(pf, &un, len, &res);
	(pf->hash && pf->null == 0) ? res += (int)write(1, "0", 1) : (0);
	(!pf->null) ? res += (int)write(1, s, len) : 0;
	if (pf->null && (pf->wipre == 0 || (pf->wipre && pf->hash)))
		res += (int)write(1, "0", 1);
	pf->minus > 0 ? res = wid_write(&(*pf), res, un, len) : (0);
	ft_strdel(&s);
	return (res);
}

int			write_llu(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.ulli = va_arg(ap, unsigned long long int);
	s = ft_itoa_b_u(pf->u_n.ulli, 10);
	len = (int)ft_strlen(s);
	pf->u_n.ulli == 0 ? pf->null = 1 : 0;
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

static void	write_hd_help_fin(t_prf *pf, int *res, int *un, char *s)
{
	int		len;

	len = (int)ft_strlen(s);
	if (pf->dot && pf->pre == 0 && pf->null && pf->wid && pf->zero == 0)
		(*res) += (int)write(1, " ", 1);
	else if (pf->wipre && pf->wid == 0 && pf->pre == 0 && pf->null)
		;
	else if (ft_strcmp(s, "-128") == 0)
		(*res) += (int)write(1, "128", len - 1);
	else if (ft_strcmp(s, "128") == 0)
		(*res) += (int)write(1, "128", len);
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

int			write_hd(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.sh = (short)va_arg(ap, int);
	pf->u_n.sh == 0 ? pf->null = 1 : (0);
	(pf->u_n.sh < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.sh < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.sh *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.sh, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.sh, 10);
	write_hd_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int			write_hhd(va_list ap, t_prf *pf, int res, int un)
{
	int		len;
	char	*s;

	pf->u_n.c = (char)va_arg(ap, int);
	pf->u_n.c == 0 ? pf->null = 1 : (0);
	(pf->u_n.c < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.c < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.c *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.c, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.c, 10);
	write_hd_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}
