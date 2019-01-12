/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:05:20 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:05:22 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		hh_b_handl(const char **format, va_list ap, t_prf *pf, int res)
{
	int			un;

	un = 0;
	if (**format == 'X')
		res = write_hh_big_x(ap, pf, res, un);
	else if (**format == 'D')
		res = write_d(ap, pf, res, un);
	else if (**format == 'O')
		res = write_hh_big_o(ap, pf, res, un);
	else if (**format == 'U')
		res = write_hu(ap, pf, res, un);
	else if (**format == 'C')
		res = unichr_write(va_arg(ap, unsigned int), res);
	else if (**format == 'S')
		res = unistr_write(ap, res, pf, un);
	initialize_prf(&(*pf));
	if (pf->holder == 0)
		pf->holder = 1;
	return (res);
}

static int		hh_handler(const char **format, va_list ap, t_prf *pf, int res)
{
	int			un;

	un = 0;
	(*format)++;
	if (**format == 'd' || **format == 'i')
		res = write_hhd(ap, pf, res, un);
	else if (**format == 'o')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		res = write_hho(ap, pf, res, un);
	}
	else if (**format == 'x')
		res = write_hhx(ap, pf, res, un);
	else if (**format == 'u')
		res = write_hhu(ap, pf, res, un);
	else if (DOUX(**format) || **format == 'C' || **format == 'S')
		res = hh_b_handl(&(*format), ap, &(*pf), res);
	else if (**format == 'p')
		res = easy_wr(*format, ap, &(*pf), res);
	initialize_prf(&(*pf));
	pf->holder == 0 ? pf->holder = 1 : 0;
	return (res);
}

static int		h_b_handl(const char **format, va_list ap, t_prf *pf, int res)
{
	int			un;

	un = 0;
	if (**format == 'X')
		res = write_h_big_x(ap, pf, res, un);
	else if (**format == 'U')
		res = write_lu(ap, pf, res, un);
	else if (**format == 'D')
		res = write_h_big_d(ap, pf, res, un);
	else if (**format == 'O')
		res = write_lo(ap, pf, res, un);
	else if (**format == 'p')
		res = easy_wr(*format, ap, &(*pf), res);
	return (res);
}

int				h_handl(const char **form, va_list ap, t_prf *pf, int res)
{
	int			un;

	un = 0;
	(*form)++;
	if (**form == 'h')
		res = hh_handler(&(*form), ap, &(*pf), res);
	else if (**form == 'd' || **form == 'i')
		res = write_hd(ap, pf, res, un);
	else if (**form == 'u')
		res = write_hu(ap, pf, res, un);
	else if (**form == 'o')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		pf->plus > 0 ? pf->plus = 0 : (0);
		res = write_ho(ap, pf, res, un);
	}
	else if (**form == 'x')
		res = write_hx(ap, pf, res, un);
	else if (DOUX(**form) || **form == 'p')
		res = h_b_handl(&(*form), ap, &(*pf), res);
	initialize_prf(&(*pf));
	pf->holder == 0 ? pf->holder = 1 : 0;
	return (res);
}
