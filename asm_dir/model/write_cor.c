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

void	write_cor_file_instructions(int fd_cor, t_asm_str *asm_str)
{
	int		codage;

	while (asm_str)
	{
		if (asm_str->op_code)
			write(fd_cor, &asm_str->op_code, 1);
		if (asm_str->codage)
		{
			codage = calculate_codage(asm_str);
			write(fd_cor, &codage, 1);
		}
		fill_in_cor_file(fd_cor, asm_str);
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
