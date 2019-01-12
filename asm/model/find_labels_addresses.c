/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_labels_addresses.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:19:28 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 16:19:33 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

long		find_label_address_after_arg(t_asm_str *label_str,
					t_asm_str *cur_str)
{
	int		total_bytes;

	total_bytes = 0;
	while (cur_str != label_str)
	{
		total_bytes += cur_str->size;
		cur_str = cur_str->next;
	}
	return (total_bytes);
}

long		find_label_address_before_arg(t_asm_str *label_str,
					t_asm_str *cur_str)
{
	int		total_bytes;

	total_bytes = 0;
	cur_str = cur_str->prev;
	while (cur_str != label_str)
	{
		total_bytes += cur_str->size;
		cur_str = cur_str->prev;
	}
	total_bytes += cur_str->size;
	return (0 - total_bytes);
}

t_asm_str	*search_label(t_asm_str **asm_str, char *label)
{
	t_asm_str	*cur_str;

	cur_str = *asm_str;
	while (cur_str)
	{
		if (ft_strcmp(cur_str->label, label) == EQUAL)
		{
			return (cur_str);
		}
		cur_str = cur_str->next;
	}
	return (NULL);
}

void		calc_pointer_value(t_asm_str **str, t_asm_str **cur_str, int i)
{
	t_asm_str	*label_str;

	label_str = search_label(str, (*cur_str)->pointer[i]);
	if (!label_str)
		error_type(INC_LABELNAME, (*str)->nb);
	if (label_str->nb - (*cur_str)->nb > 0)
	{
		(*cur_str)->arg_cont[i] =
			find_label_address_after_arg(label_str, *cur_str);
	}
	else
	{
		(*cur_str)->arg_cont[i] =
			find_label_address_before_arg(label_str, *cur_str);
	}
}

void		find_labels_addresses(t_asm_str **asm_str)
{
	int			i;
	t_asm_str	*cur_str;

	if (*asm_str)
	{
		cur_str = *asm_str;
		while (cur_str)
		{
			i = 0;
			while (i < 3)
			{
				if (cur_str->pointer[i])
				{
					calc_pointer_value(asm_str, &cur_str, i);
				}
				i++;
			}
			cur_str = cur_str->next;
		}
	}
}
