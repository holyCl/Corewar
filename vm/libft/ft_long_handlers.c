/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:15:16 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/11 17:15:20 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	b_ll_handle(const char **format, va_list ap, t_prf *pf, int res)
{
	int		un;

	un = 0;
	if (**format == 'X')
		res = write_j_big_x(ap, pf, res, un);
	else if (**format == 'D')
		res = write_ll_big_d(ap, pf, res, un);
	else if (**format == 'O')
		res = write_llo(ap, pf, res, un);
	else if (**format == 'U')
		res = write_llu(ap, pf, res, un);
	pf->holder == 0 ? pf->holder = 1 : 0;
	return (res);
}

static int	ll_handle(const char **format, va_list ap, t_prf *pf, int res)
{
	int		un;

	un = 0;
	(*format)++;
	if (**format == 'd' || **format == 'i')
		res = write_lld(ap, pf, res, un);
	else if (**format == 'o')
	{
		pf->octal = 1;
		res = write_llo(ap, pf, res, un);
	}
	else if (**format == 'x')
		res = write_llx(ap, pf, res, un);
	else if (**format == 'u')
		res = write_llu(ap, pf, res, un);
	else if (DOUX(**format))
		res = b_ll_handle(&(*format), ap, &(*pf), res);
	else if (**format == 'p')
		res = easy_wr(*format, ap, &(*pf), res);
	pf->holder == 0 ? pf->holder = 1 : 0;
	return (res);
}

static int	b_l_handle(const char **format, va_list ap, t_prf *pf, int res)
{
	int		un;

	un = 0;
	if (**format == 'O')
		res = write_lo(ap, pf, res, un);
	else if (**format == 'U')
		res = write_lu(ap, pf, res, un);
	else if (**format == 'D')
		res = write_lld(ap, pf, res, un);
	else if (**format == 'X')
		res = write_l_big_x(ap, pf, res, un);
	else if (**format == 'x')
	{
		pf->plus > 0 ? pf->plus = 0 : (0);
		res = write_lx(ap, pf, res, un);
	}
	pf->holder == 0 ? pf->holder = 1 : (0);
	return (res);
}

int			l_handl(const char **form, va_list ap, t_prf *pf, int res)
{
	int		un;

	un = 0;
	(*form)++;
	if (**form == 'l')
		res = ll_handle(&(*form), ap, &(*pf), res);
	else if (**form == 'd' || **form == 'i')
		res = write_ld(ap, pf, res, un);
	else if (**form == 's')
		res = unistr_write(ap, res, pf, un);
	else if (**form == 'c')
		res = unichr_write(va_arg(ap, unsigned int), res);
	else if (**form == 'u')
		res = write_lu(ap, pf, res, un);
	else if (**form == 'o')
		res = write_lo(ap, pf, res, un);
	else if (DOUX(**form) || **form == 'x')
		res = b_l_handle(&(*form), ap, &(*pf), res);
	else if (**form == 'p')
		res = easy_wr(*form, ap, &(*pf), res);
	initialize_prf(&(*pf));
	pf->holder == 0 ? pf->holder = 1 : (0);
	return (res);
}
