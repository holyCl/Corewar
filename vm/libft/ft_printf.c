/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:20:44 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 19:20:50 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	parse_help(const char *format, t_prf *pf, int *res)
{
	if (pf->wid && pf->minus == 0)
	{
		while (pf->wid-- > 1)
			if (pf->zero == 0)
				(*res) += (int)write(1, " ", 1);
			else
				(*res) += (int)write(1, "0", 1);
	}
	(*res) += (int)write(1, &(*format), 1);
	if (pf->wid && pf->minus)
	{
		while (pf->wid-- > 1)
			(*res) += (int)write(1, " ", 1);
	}
}

int			parsedata(const char *form, va_list ap, t_prf pf, int res)
{
	int		x;

	while (*form)
	{
		if (*form && *form != '%')
		{
			parse_help(&(*form), &pf, &res);
			(pf.counter == 0 && pf.wid == 0) ? pf.counter = res : 0;
			form++;
		}
		else if (*form && *form == '%')
		{
			x = parsing(&form, ap, &pf, res);
			if (x == 0 && pf.wid == 0)
				initialize_prf(&pf);
			else
			{
				res = x;
				(pf.counter && pf.wid) ? res += pf.counter : 0;
			}
			form++;
		}
	}
	return (res);
}

int			ft_printf(const char *format, ...)
{
	int		res;
	va_list	ap;
	t_prf	pf;

	initialize_prf(&pf);
	va_start(ap, format);
	res = 0;
	res = parsedata(format, ap, pf, res);
	va_end(ap);
	return (res);
}
