/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:44:25 by inazarin          #+#    #+#             */
/*   Updated: 2018/05/11 17:44:27 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	prec_counter(const char **format, va_list ap, t_prf *pf)
{
	int		i;

	pf->dot == 0 ? pf->dot = 1 : 0;
	pf->wipre == 0 ? pf->wipre = 1 : (0);
	(*format)++;
	i = 0;
	if (**format == '*')
		pf->pre = va_arg(ap, int);
	else if (**format >= '0' && **format <= '9')
	{
		while (**format >= '0' && **format <= '9')
		{
			i *= 10;
			i += **format - '0';
			(*format)++;
		}
		(*format)--;
		pf->pre = i;
	}
	else if (DIOUX(**format) || CCSS(**format) || LONGS(**format))
		(*format)--;
	else if (DOUX(**format) || **format == 'p' || **format == '%')
		(*format)--;
	else if (ft_isalpha(**format))
		(*format)--;
}

int		precision_write(t_prf *pf, int res, int un, int len)
{
	if (un > 0)
	{
		((pf->hash && pf->octal) || (pf->sign && pf->dot)) ? un-- : 0;
		if (pf->sign && (pf->minus || pf->zero || pf->dot))
		{
			un++;
			if (pf->pre != pf->wid)
			{
				pf->zero == 0 ? res += (int)write(1, "-", 1) : 0;
				pf->minsign ? pf->minsign = 0 : 0;
			}
		}
		while (un)
		{
			if (pf->plus && pf->pre > len)
			{
				res += (int)write(1, "+", 1);
				pf->minus ? pf->dcrmnt = 1 : (0);
				pf->plus = 0;
			}
			res += (int)write(1, "0", 1);
			un--;
		}
	}
	return (res);
}

void	initialize_prf(t_prf *pf)
{
	pf->pre = 0;
	pf->wid = 0;
	pf->holder = 0;
	pf->zero = 0;
	pf->plus = 0;
	pf->minus = 0;
	pf->space = 0;
	pf->hash = 0;
	pf->dioux = 0;
	pf->doux = 0;
	pf->octal = 0;
	pf->sign = 0;
	pf->wipre = 0;
	pf->decrem = 0;
	pf->dcrmnt = 0;
	pf->minsign = 0;
	pf->hex = 0;
	pf->null = 0;
	pf->counter = 0;
	pf->dot = 0;
	pf->unicount = 0;
}

int		sp_hand(const char **form, va_list ap, t_prf *pf, int res)
{
	if (**form == 'l')
		res = l_handl(&(*form), ap, &(*pf), res);
	else if (**form == 'h')
		res = h_handl(&(*form), ap, &(*pf), res);
	else if (**form == 'z')
		res = z_handl(&(*form), ap, &(*pf), res);
	else if (**form == 'j')
		res = j_handl(&(*form), ap, &(*pf), res);
	initialize_prf(&(*pf));
	if (pf->holder == 0)
		pf->holder = 1;
	return (res);
}

int		flags(const char *format, t_prf *pf, int res)
{
	if (*format == '#')
	{
		pf->hash = 1;
	}
	else if (*format == '0')
	{
		pf->zero = 1;
	}
	else if (*format == '+')
	{
		pf->plus = 1;
		pf->space > 0 ? pf->space = 0 : (0);
	}
	else if (*format == '-')
	{
		pf->minus = 1;
	}
	else if (*format == ' ')
	{
		pf->plus == 0 ? pf->space = 1 : (0);
	}
	return (res);
}
