/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 20:37:44 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 20:38:05 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					dioux(const char *format, va_list ap, t_prf *pf, int res)
{
	int				un;

	un = 0;
	pf->dioux == 0 ? pf->dioux = 1 : (0);
	if (*format == 'd' || *format == 'i')
		res = write_d(ap, pf, res, un);
	else if (*format == 'o')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		res = write_o(ap, pf, res, un);
	}
	else if (*format == 'u')
		res = write_u(ap, pf, res, un);
	else if (*format == 'x')
		res = write_x(ap, pf, res, un);
	initialize_prf(&(*pf));
	if (pf->holder == 0)
		pf->holder = 1;
	return (res);
}

int					doux(const char *format, va_list ap, t_prf *pf, int res)
{
	int				un;

	un = 0;
	pf->doux == 0 ? pf->doux = 1 : (0);
	if (*format == 'D')
		res = write_ld(ap, pf, res, un);
	else if (*format == 'O')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		res = write_lo(ap, pf, res, un);
	}
	else if (*format == 'U')
		res = write_lu(ap, pf, res, un);
	else if (*format == 'X')
		res = write_big_x(ap, pf, res, un);
	initialize_prf(&(*pf));
	if (!pf->holder)
		pf->holder = 1;
	return (res);
}

int					sscc(const char *format, va_list ap, t_prf *pf, int res)
{
	int				un;
	unsigned int	unich;

	un = 0;
	if (*format == 's')
		res = write_s(ap, pf, res, un);
	else if (*format == 'c')
		res = write_c(va_arg(ap, int), pf, res);
	else if (*format == 'S')
		res = unistr_write(ap, res, pf, un);
	else if (*format == 'C')
	{
		unich = va_arg(ap, unsigned int);
		if (unich <= 255)
			res = write_c((int)unich, pf, res);
		else
			res = wr_big_uni_c(unich, res, pf, un);
	}
	initialize_prf(&(*pf));
	if (!pf->holder)
		pf->holder = 1;
	return (res);
}

int					z_handl(const char **form, va_list ap, t_prf *pf, int res)
{
	int				un;

	un = 0;
	(*form)++;
	if (**form == 'd' || **form == 'i' || **form == 'D')
		res = write_zd(ap, pf, res, un);
	else if (**form == 'u' || **form == 'U')
		res = write_zu(ap, pf, res, un);
	else if (**form == 'o' || **form == 'O')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		res = write_zo(ap, pf, res, un);
	}
	else if (**form == 'x')
		res = write_zx(ap, pf, res, un);
	else if (**form == 'X')
		res = write_z_big_x(ap, pf, res, un);
	else if (**form == 'p')
		res = easy_wr(*form, ap, &(*pf), res);
	initialize_prf(&(*pf));
	if (pf->holder == 0)
		pf->holder = 1;
	return (res);
}

int					j_handl(const char **form, va_list ap, t_prf *pf, int res)
{
	int				un;

	un = 0;
	(*form)++;
	if (**form == 'd' || **form == 'i' || **form == 'D')
		res = write_jd(ap, pf, res, un);
	else if (**form == 'u' || **form == 'U')
		res = write_llu(ap, pf, res, un);
	else if (**form == 'o' || **form == 'O')
	{
		pf->octal = 1;
		pf->minus > 0 ? pf->zero = 0 : (0);
		res = write_jo(ap, pf, res, un);
	}
	else if (**form == 'x')
		res = write_jx(ap, pf, res, un);
	else if (**form == 'X')
		res = write_j_big_x(ap, pf, res, un);
	else if (**form == 'p')
		res = easy_wr(*form, ap, &(*pf), res);
	initialize_prf(&(*pf));
	if (pf->holder == 0)
		pf->holder = 1;
	return (res);
}
