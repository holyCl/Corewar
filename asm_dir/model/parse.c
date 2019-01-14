/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:21:07 by akorzhak          #+#    #+#             */
/*   Updated: 2018/09/29 18:21:09 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		parse_args(char *src, t_asm_str **asm_str, int len, int *temp)
{
	int		n;
	int		a;
	char	**args;

	n = 0;
	a = 0;
	args = ft_strsplit(src, SEPARATOR_CHAR);
	while (args[n])
	{
		*temp = 1;
		len = 0;
		while (args[n][len] && (args[n][len] == ' ' || args[n][len] == '\t'))
			len++;
		len += record_arg_type(args[n][len], asm_str, a);
		if (ft_strlen_space(args[n]) == 1)
			error_type(LEXIC, (*asm_str)->nb, src);
		(*asm_str)->arg_cont[a] = ft_atoi(&args[n][len]);
		if (args[n][len] == LABEL_CHAR)
			(*asm_str)->pointer[a] = ft_strdup(&args[n][++len]);
		a++;
		n++;
	}
	free_2d_array(args);
	free(args);
	return (n);
}

void	convert_endian(int *value)
{
	*value = (((*value & 0x000000FF) << 24) | \
			((*value & 0x0000FF00) << 8) | \
			((*value & 0x00FF0000) >> 8) | \
			((*value & 0xFF000000) >> 24));
}

void	convert_endian_short(short *num)
{
	*num = ((*num & 0xff00) >> 8) | ((*num & 0xff) << 8);
}

int		calculate_codage(t_asm_str *asm_str)
{
	int		arg1;
	int		arg2;
	int		arg3;
	int		codage;

	arg1 = asm_str->type_arg[0];
	arg2 = asm_str->type_arg[1];
	arg3 = asm_str->type_arg[2];
	codage = (arg1 << 6) | (arg2 << 4) | (arg3 << 2);
	return (codage);
}
