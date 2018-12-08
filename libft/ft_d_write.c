/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:48:18 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:48:33 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				write_d(va_list ap, t_prf *pf, int res, int un)
{
	int			len;
	char		*s;

	pf->u_n.i = va_arg(ap, int);
	pf->u_n.i == 0 ? pf->null = 1 : (0);
	(pf->u_n.i < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.i < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.i *= (-1);
	}
	s = ft_itoa(pf->u_n.i);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa(pf->u_n.i);
	write_d_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int				write_ld(va_list ap, t_prf *pf, int res, int un)
{
	long int	len;
	char		*s;

	pf->u_n.li = va_arg(ap, long int);
	pf->u_n.li == 0 ? pf->null = 1 : (0);
	(pf->u_n.li < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.li < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.li *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.li, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.li, 10);
	write_d_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int				write_lld(va_list ap, t_prf *pf, int res, int un)
{
	int			len;
	char		*s;

	pf->u_n.lli = va_arg(ap, long long int);
	pf->u_n.lli == 0 ? pf->null = 1 : (0);
	(pf->u_n.lli < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.lli < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.lli *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.lli, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.lli, 10);
	write_d_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int				write_jd(va_list ap, t_prf *pf, int res, int un)
{
	int			len;
	char		*s;

	pf->u_n.im = va_arg(ap, intmax_t);
	pf->u_n.im == 0 ? pf->null = 1 : (0);
	(pf->u_n.im < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.im < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.im *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.im, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.im, 10);
	write_d_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}

int				write_zd(va_list ap, t_prf *pf, int res, int un)
{
	int			len;
	char		*s;

	pf->u_n.sst = va_arg(ap, ssize_t);
	pf->u_n.sst == 0 ? pf->null = 1 : (0);
	(pf->u_n.sst < 0) ? pf->plus = 0 : 0;
	if (pf->u_n.sst < 0)
	{
		pf->sign = 1;
		pf->space = 0;
		pf->u_n.sst *= (-1);
	}
	s = ft_itoa_b_s(pf->u_n.sst, 10);
	len = (int)ft_strlen(s);
	len = write_d_help_d(pf, &res, &un, len);
	if (pf->sign && pf->wid >= len)
		s = ft_itoa_b_s(pf->u_n.sst, 10);
	write_d_help_fin(pf, &res, &un, s);
	ft_strdel(&s);
	return (res);
}
