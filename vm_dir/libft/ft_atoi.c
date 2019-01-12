/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:55:32 by inazarin          #+#    #+#             */
/*   Updated: 2017/11/15 16:41:23 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_spaces(int c)
{
	return (c == '\n' || c == ' ' || c == '\v' || \
			c == '\t' || c == '\r' || c == '\f');
}

int			ft_atoi(const char *str)
{
	unsigned long int	res;
	int					i;
	int					sign;

	sign = 1;
	i = 0;
	res = 0;
	while (ft_spaces(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (sign == -1 && res > 9223372036854775807)
			return (0);
		else if (sign == 1 && res > 9223372036854775806)
			return (-1);
		i++;
	}
	return (res * sign);
}
