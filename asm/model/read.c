/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:06:35 by akorzhak          #+#    #+#             */
/*   Updated: 2018/10/24 16:06:37 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		count_char_occur(char *str, char c)
{
	int		nb;

	nb = 0;
	while (*str)
	{
		if (*str == c)
			nb++;
		str++;
	}
	return (nb);
}

char	*cut_content(char *str)
{
	char	*str_end;

	if ((str = ft_strchr(str, '"')) == NULL)
		return (NULL);
	++str;
	if ((str_end = ft_strchr(str, '"')) == NULL)
		return (NULL);
	++str_end;
	if (!is_empty_str(str_end))
		return (NULL);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int		read_header(t_asm *a, t_header *header, char **line, int *count)
{
	char	*cont;
	int		i;
	int		flag;

	flag = FALSE;
	while (get_next_line(a->s_fd, line) > 0)
	{
		if ((**line != HEADER_CHAR) && !is_empty_str(*line))
		{
			flag = TRUE;
			break ;
		}
		i = -1;
		if (ft_strnequ(*line, NAME_CMD_STRING, 5))
		{
			if (header->prog_name[0] != '\0')
				return (exit_with_error(a, line, NAME_REDEFINE));
			if ((cont = cut_content(*line)) == NULL)
				return (exit_with_error(a, line, SYNT_ERR_N));
			while (cont[++i])
				header->prog_name[i] = cont[i];
		}
		else if (ft_strnequ(*line, COMMENT_CMD_STRING, 8))
		{
			if (header->comment[0] != '\0')
				return (exit_with_error(a, line, COMM_REDEFINE));
			if ((cont = cut_content(*line)) == NULL)
				return (exit_with_error(a, line, SYNT_ERR_C));
			while (cont[++i])
				header->comment[i] = cont[i];
		}
		ft_strdel(line);
		(*count) += 1;
	}
	if (!flag)
	{
		display_error_message(NO_CMND);
		exit(1);
	}
	return (OK);
}

void	prepare_space_for_next_asm_str(t_asm_str **s_str)
{
	t_asm_str	*prev;

	prev = *s_str;
	(*s_str)->next = (t_asm_str *)ft_memalloc(sizeof(t_asm_str));
	*s_str = (*s_str)->next;
	(*s_str)->prev = prev;
}

int		read_instructions(t_asm *a, t_asm_str **asm_str, char **line, int count)
{
	int			nb;
	t_asm_str	*s_str;

	nb = count;
	s_str = (t_asm_str *)ft_memalloc(sizeof(t_asm_str));
	*asm_str = s_str;
	if (!is_empty_str(*line))
		record_asm_str(*line, &s_str, ++nb);
	ft_strdel(line);
	while (get_next_line(a->s_fd, line) > 0)
	{
		if (is_empty_str(*line))
		{
			ft_strdel(line);
			continue ;
		}
		if (s_str->nb)
			prepare_space_for_next_asm_str(&s_str);
		record_asm_str(*line, &s_str, ++nb);
		ft_strdel(line);
	}
	return (0);
}

int		read_file(t_asm *a, t_header *header, t_asm_str **asm_str)
{
	char	*line;
	int		count;

	count = 0;
	if (read_header(a, header, &line, &count) == ERROR)
		return (ERROR);
	if (validate_header(header) == ERROR)
		return (exit_with_error(a, &line, NO_CMD));
	read_instructions(a, asm_str, &line, count);
	return (OK);
}
