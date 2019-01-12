/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 21:01:25 by inazarin          #+#    #+#             */
/*   Updated: 2018/04/23 21:02:55 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_pow(int num, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (num * ft_pow(num, pow - 1));
}

char						*ft_itoa_b_l(unsigned long long nbr, int base)
{
	int		i;
	char	*s;

	i = 1;
	while (ft_pow(base, i) - 1 < nbr)
		i++;
	s = (char*)malloc(sizeof(char) * i);
	s[i] = '\0';
	while (i-- > 0)
	{
		s[i] = (nbr % base) + (nbr % base > 9 ? 'A' - 10 : '0');
		nbr = nbr / base;
	}
	return (s);
}

char						*ft_itoa_base(unsigned long long nbr, int base)
{
	int		i;
	char	*s;

	i = 1;
	while (ft_pow(base, i) - 1 < nbr)
		i++;
	s = (char*)malloc(sizeof(char) * i);
	s[i] = '\0';
	while (i-- > 0)
	{
		s[i] = (nbr % base) + (nbr % base > 9 ? 'a' - 10 : '0');
		nbr = nbr / base;
	}
	return (s);
}

char						*ft_itoa_b_u_l(unsigned int nbr, int base)
{
	int		i;
	char	*s;

	i = 1;
	while (ft_pow(base, i) - 1 < nbr)
		i++;
	s = (char*)malloc(sizeof(char) * i);
	s[i] = '\0';
	while (i-- > 0)
	{
		s[i] = (nbr % base) + (nbr % base > 9 ? 'A' - 10 : '0');
		nbr = nbr / base;
	}
	return (s);
}

char						*ft_itoa_base_u(unsigned int nbr, int base)
{
	int		i;
	char	*s;

	i = 1;
	while (ft_pow(base, i) - 1 < nbr)
		i++;
	s = (char*)malloc(sizeof(char) * i);
	s[i] = '\0';
	while (i-- > 0)
	{
		s[i] = (nbr % base) + (nbr % base > 9 ? 'a' - 10 : '0');
		nbr = nbr / base;
	}
	return (s);
}
