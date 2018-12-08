/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:32 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 19:23:34 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_p_help(t_prf *pf, int *res, int *un, int len)
{
	if (pf->wid <= pf->pre && pf->pre > 0 && pf->pre >= len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid > pf->pre && pf->pre && pf->pre > len)
		(*un) = pf->wid - pf->pre;
	else if (pf->wid <= pf->pre && pf->pre >= len)
		(*un) = 0;
	else
		(*un) = (pf->wid - len);
	pf->minus == 0 ? (*res) = wid_write(&(*pf), *res, *un, len) : (0);
	return (*res);
}

int			write_p(va_list ap, t_prf *pf, int res)
{
	int		len;
	int		un;
	char	*s;

	un = 0;
	pf->u_n.uli = va_arg(ap, unsigned long int);
	s = ft_itoa_base(pf->u_n.uli, 16);
	len = (int)(ft_strlen(s) + 2);
	(pf->zero) ? res += (int)write(1, "0x", 2) : 0;
	pf->wid ? (res = write_p_help(&(*pf), &res, &un, len)) : 0;
	(pf->zero == 0) ? res += (int)write(1, "0x", 2) : 0;
	if ((pf->pre > 0) && (pf->pre >= len))
	{
		if (pf->u_n.uli != 0)
			res = precision_write(&(*pf), res, pf->pre - len + 2, len);
		else
			res = precision_write(&(*pf), res, pf->pre - len + 2, len);
	}
	if (pf->dot && pf->pre == 0 && pf->u_n.uli == 0)
		;
	else
		res += (int)write(1, s, (len - 2));
	(pf->minus && pf->wid > len) ? res = wid_write(&(*pf), res, un, len) : 0;
	ft_strdel(&s);
	return (res);
}

int			easy_wr(const char *form, va_list ap, t_prf *pf, int res)
{
	if (*form == '%')
	{
		if (pf->wid > 0 && pf->minus == 0)
		{
			if (pf->plus > 0)
				res = wid_write(&(*pf), res, pf->wid, 1);
			else
				res = wid_write(&(*pf), res, pf->wid - 1, 1);
		}
		res += (int)write(1, "%%", 1);
		pf->minus > 0 ? res = wid_write(&(*pf), res, (pf->wid - 1), 1) : (0);
	}
	else if (*form == 'p')
		res = write_p(ap, pf, res);
	initialize_prf(&(*pf));
	if (!pf->holder)
		pf->holder = 1;
	return (res);
}

static int	parse_help(const char **format, va_list ap, t_prf *pf, int res)
{
	if (FLAGS(**format))
		res = flags(*format, &(*pf), res);
	else if (WIDTH(**format))
		wid_handle(&(*format), ap, &(*pf));
	else if (**format == '.')
		prec_counter(&(*format), ap, &(*pf));
	else if (LONGS(**format))
		res = sp_hand(&(*format), ap, &(*pf), res);
	else if (DIOUX(**format))
		res = dioux(*format, ap, &(*pf), res);
	else if (DOUX(**format))
		res = doux(*format, ap, &(*pf), res);
	else if (CCSS(**format))
		res = sscc(*format, ap, &(*pf), res);
	else if (**format == '%' || **format == 'p')
		res = easy_wr(*format, ap, &(*pf), res);
	return (res);
}

int			parsing(const char **form, va_list ap, t_prf *pf, int res)
{
	pf->holder ? pf->holder = 0 : 0;
	while (**form && pf->holder == 0)
	{
		(*form)++;
		if (**form == '\0')
		{
			(*form)--;
			return (0);
		}
		if (FLAGS(**form) || WIDTH(**form) || **form == '.')
			res = parse_help(&(*form), ap, &(*pf), res);
		else if (LONGS(**form) || **form == '%' || **form == 'p')
			res = parse_help(&(*form), ap, &(*pf), res);
		else if (DIOUX(**form) || DOUX(**form) || CCSS(**form))
			res = parse_help(&(*form), ap, &(*pf), res);
		else if (**form && pf->holder == 0)
		{
			(*form)--;
			return (0);
		}
	}
	return (res);
}
