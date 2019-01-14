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

int		record_label(int *i, char *src, t_asm_str **asm_str)
{
	int fl;
	int a;

	fl = 0;
	a = *i;
	while (src[a] != ' ' && src[a] != '\t' && src[a] != '\0')
	{
		if (src[a] == LABEL_CHAR)
		{
			if (src[a + 1] == LABEL_CHAR)
				error_type(LEXIC, (*asm_str)->nb, src);
			if (src[a + 1] != ' ' && src[a + 1] != '\t')
				error_type(LEXIC, (*asm_str)->nb, src);
			(*asm_str)->label = ft_strnew(a);
			ft_strncpy((*asm_str)->label, src, a);
			valid_label((*asm_str)->label, (*asm_str)->nb, src);
			fl = 1;
		}
		if ((src[a + 1] == ' ' || src[a + 1] == '\t') && !fl)
			fl = 2;
		a++;
	}
	*i = ++a;
	return (fl);
}

int		record_arg_type(char arg_char, t_asm_str **asm_str, int a)
{
	if (arg_char == REG_CHAR)
	{
		(*asm_str)->type_arg[a] = REG_CODE;
		(*asm_str)->size += REG_SIZE;
		return (1);
	}
	if (arg_char == DIRECT_CHAR)
	{
		(*asm_str)->type_arg[a] = DIR_CODE;
		(*asm_str)->size += DIR_SIZE((*asm_str)->label_size);
		return (1);
	}
	(*asm_str)->type_arg[a] = IND_CODE;
	(*asm_str)->size += IND_SIZE;
	return (0);
}

void	record_asm_str(char *src, t_asm_str **asm_str, int nb)
{
	t_ints s;

	s.temp = 0;
	s.i = 0;
	(*asm_str)->nb = nb;
	if (src[s.i] == LABEL_CHAR)
		error_type(INC_LABELNAME, (*asm_str)->nb, src);
	s.fl = record_label(&s.i, src, asm_str);
	s.i *= (s.fl == 2) ? 0 : 1;
	while (src[s.i] == ' ' || src[s.i] == '\t')
		s.i++;
	s.len = ft_wordlen(&src[s.i]);
	s.oper = identify_operation(s.len, &src[s.i], asm_str);
	if (g_op_tab[s.oper].codage)
		iterate_asm_str(asm_str);
	(*asm_str)->label_size = g_op_tab[s.oper].label_size;
	s.i += s.len + 1;
	if (g_op_tab[s.oper].arg_nb != parse_args(&src[s.i], \
		asm_str, s.len, &s.temp))
		error_type(INC_ARGS, (*asm_str)->nb, src);
	if (s.oper == 17)
		error_type(OP_EXIST, (*asm_str)->nb, src);
	if (!s.temp)
		error_type(INC_ARGS, (*asm_str)->nb, src);
}
