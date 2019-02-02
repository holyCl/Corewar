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

void	fill_in_cor_file(int fd_cor, t_asm_str *asm_str)
{
	int i;

	i = -1;
	while ((++i < 3) && asm_str->type_arg[i])
	{
		if (asm_str->type_arg[i] == REG_CODE)
			write(fd_cor, &(asm_str->arg_cont[i]), REG_SIZE);
		else if ((asm_str->type_arg[i] == IND_CODE) || asm_str->label_size == 2)
		{
			convert_endian_short((short *)&asm_str->arg_cont[i]);
			write(fd_cor, &asm_str->arg_cont[i], 2);
		}
		else if (asm_str->type_arg[i] == DIR_CODE)
		{
			convert_endian(&asm_str->arg_cont[i]);
			write(fd_cor, &asm_str->arg_cont[i], 4);
		}
		i++;
	}
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
