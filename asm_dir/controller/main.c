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

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))

int		ft_wordlen(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	return (len);
}

void	valid_label(char *asm_str, int nb)
{
	int i;

	i = -1;
	while (asm_str[++i])
	{
		if (!ft_strchr(LABEL_CHARS, asm_str[i]))
			error_type(INC_LABELNAME, nb);
	}
}

int		ft_strlen_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

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
				error_type(LEXIC, (*asm_str)->nb);
			if (src[a + 1] != ' ' && src[a + 1] != '\t')
				error_type(LEXIC, (*asm_str)->nb);
			(*asm_str)->label = ft_strnew(a);
			ft_strncpy((*asm_str)->label, src, a);
			valid_label((*asm_str)->label, (*asm_str)->nb);
			fl = 1;
		}
		if ((src[a + 1] == ' ' || src[a + 1] == '\t') && !fl)
			fl = 2;
		a++;
	}
	*i = a;
	return (fl);
}

int 	record_arg_type(char arg_char, t_asm_str **asm_str, int a)
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

int		parse_args(char *src, t_asm_str **asm_str, int len, int *temp)
{
	int 	n;
	int 	a;
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
			error_type(LEXIC, (*asm_str)->nb);
		(*asm_str)->arg_cont[a] = ft_atoi(&args[n][len]);
		if (args[n][len] == LABEL_CHAR)
			(*asm_str)->pointer[a] = ft_strdup(&args[n][++len]);
		a++;
		n++;
	}
	free_2d_array(&args);
	return (n);
}

int 	identify_operation(int len, char *src, t_asm_str **asm_str)
{
	int 	oper;
	char	*op;

	oper = 0;
	op = ft_strnew(len);
	ft_strncpy(op, src, len);
	while (oper < 17)
	{
		if (ft_strcmp(g_op_tab[oper].name, op) == EQUAL)
		{
			(*asm_str)->op_code = g_op_tab[oper].op_code;
			(*asm_str)->size = 1;
			break ;
		}
		oper++;
	}
	ft_strdel(&op);
	return (oper);
}

void	record_asm_str(char *src, t_asm_str **asm_str, int nb)
{
	int		i;
	int		len;
	int		fl;
	int		temp;
	int		oper;

	temp = 0;
	i = 0;
	(*asm_str)->nb = nb;
	if (src[i] == LABEL_CHAR)
		error_type(INC_LABELNAME, (*asm_str)->nb);
	fl = record_label(&i, src, asm_str);
	i++;
	i *= (fl == 2) ? 0 : 1;
	while (src[i] == ' ' || src[i] == '\t')
		i++;
	len = ft_wordlen(&src[i]);
	oper = identify_operation(len, &src[i], asm_str);
	if (g_op_tab[oper].codage)
	{
		(*asm_str)->codage = 1;
		(*asm_str)->size += 1;
	}
	(*asm_str)->label_size = g_op_tab[oper].label_size;
	i += len + 1;
	if (g_op_tab[oper].arg_nb != parse_args(&src[i], asm_str, len, &temp))
		error_type(INC_ARGS, (*asm_str)->nb);
	if (oper == 17)
		error_type(OP_EXIST, (*asm_str)->nb);
	if (!temp)
		error_type(INC_ARGS, (*asm_str)->nb);
}

char	is_empty_str(char *str)
{
	if (str && *str)
	{
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		if (*str && *str != COMMENT_CHAR)
			return (FALSE);
	}
	return (TRUE);
}

char	*substitute_extention(char *src, char *new_ext)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(src) + 2;
	dest = ft_strnew(len);
	while (src[i])
	{
		dest[i] = src[i];
		if (dest[i++] == EXTENTION_CHAR)
			break ;
	}
	while (i < len)
		dest[i++] = *new_ext++;
	return (dest);
}

int		open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
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

void	write_cor_file_instructions(int fd_cor, t_asm_str *asm_str)
{
	int		codage;
	int		i;

	while (asm_str)
	{
		if (asm_str->op_code)
			write(fd_cor, &asm_str->op_code, 1);
		if (asm_str->codage)
		{
			codage = calculate_codage(asm_str);
			write(fd_cor, &codage, 1);
		}
		i = -1;
		while ((++i < 3) && asm_str->type_arg[i])
		{
			if (asm_str->type_arg[i] == REG_CODE)
				write(fd_cor, &(asm_str->arg_cont[i]), REG_SIZE);
			else if ((asm_str->type_arg[i] == IND_CODE) || \
				asm_str->label_size == 2)
			{
				convert_endian_short((short *)&asm_str->arg_cont[i]);
				write(fd_cor, &asm_str->arg_cont[i], 2);
			}
			else if (asm_str->type_arg[i] == DIR_CODE)
			{
				convert_endian(&asm_str->arg_cont[i]);
				write(fd_cor, &asm_str->arg_cont[i], 4);
			}
		}
		asm_str = asm_str->next;
	}
}

void	write_cor_file_header(int fd_cor, t_header *header)
{
	convert_endian(&header->magic);
	write(fd_cor, &header->magic, 4);
	write(fd_cor, &header->prog_name, PROG_NAME_LENGTH);
	write(fd_cor, "\0", 4);
	convert_endian(&header->prog_size);
	write(fd_cor, &header->prog_size, 4);
	write(fd_cor, &header->comment, COMMENT_LENGTH);
	write(fd_cor, "\0", 4);
}

void	write_cor_file(char *file_name_s, t_header *header, t_asm_str **asm_str)
{
	int		fd_cor;
	char	*file_name;

	file_name = substitute_extention(file_name_s, "cor");
	fd_cor = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	write_cor_file_header(fd_cor, header);
	write_cor_file_instructions(fd_cor, *asm_str);
	ft_printf("Writing output program to %s\n", file_name);
	ft_strdel(&file_name);
	close(fd_cor);
}

int		program_logic_controller(char *file_s, t_header *h, t_asm_str **str)
{
	write_cor_file(file_s, h, str);
	return (OK);
}

int		parsing_controller(char *file_s, t_header *h, t_asm_str **str)
{
	t_asm		a;

	init(&a);
	if ((a.s_fd = open_file(file_s)) == -1)
	{
		display_error_message(FAIL_OPEN_S);
		return (ERROR);
	}
	if (read_file(&a, h, str) == ERROR)
	{
		display_error_message(a.error_message);
		return (ERROR);
	}
	handle_read_data(h, str);
	close(a.s_fd);
	return (OK);
}

int		main(int argc, char **argv)
{
	t_header	header;
	t_asm_str	*asm_str;

	init_header(&header);
	if (argc == 2)
	{
		if (parsing_controller(argv[1], &header, &asm_str) == ERROR)
		{
			return (ERROR);
		}
		if (program_logic_controller(argv[1], &header, &asm_str) == ERROR)
		{
			display_error_message(INTERNAL_ERROR);
			return (ERROR);
		}
	}
	return (ERROR);
}
