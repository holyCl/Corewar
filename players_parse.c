/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:26:04 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/20 17:26:06 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void				parse_player_name(int fd, t_player *player)
{
	int				i;
	size_t			rd;
	unsigned char	temp[4];

	rd = read(fd, &player->name, PROG_NAME_LENGTH);
	if (rd != PROG_NAME_LENGTH)
		error_exit("cant read name bytes.\n", fd);
	rd = read(fd, &temp, 4);
	if (rd != 4)
		error_exit("error parsing null before comment.\n", fd);
	i = -1;
	while (++i < 4)
	{
		if (temp[i] != 0)
			error_exit("NULL terminator after name is invalid.\n", fd);
	}
}

static void				parse_comment(int fd, t_player *player)
{
	size_t				rd;
	int					i;
	unsigned char 		temp[4];

	rd = read(fd, &player->comment, COMMENT_LENGTH);
	if (rd != COMMENT_LENGTH)
		error_exit("error during reading players comment.\n", fd);
	rd = read(fd, &temp, 4);
	if (rd != 4)
		error_exit("error parsing null after comment.\n", fd);
	i = -1;
	while (++i < 4)
	{
		if (temp[i] != 0)
			error_exit("NULL terminator after comment is invalid.\n", fd);
	}

}

static void				parse_size(int fd, t_player *player)
{
	size_t				rd;
	unsigned int	endian;
	
	rd = read(fd, &endian, 4);
	if (rd != 4)
		error_exit("Error reading champ size.", fd);
	player->size = endian;
	((unsigned char *)&player->size)[0] = ((unsigned char *)&endian)[3];
	((unsigned char *)&player->size)[1] = ((unsigned char *)&endian)[2];
	((unsigned char *)&player->size)[2] = ((unsigned char *)&endian)[1];
	((unsigned char *)&player->size)[3] = ((unsigned char *)&endian)[0];
	if (!player->size || (int)player->size > CHAMP_MAX_SIZE)
		error_exit("Error. Invalid champ size.", fd);
}

static t_player		player_struct_init(int fd, t_player *new_node)
{
	unsigned int	temp;
	unsigned int	magic_buffer;

	read(fd, &magic_buffer, 4);
	temp = magic_buffer;
	((unsigned char *)&temp)[0] = ((unsigned char *)&magic_buffer)[3];
	((unsigned char *)&temp)[1] = ((unsigned char *)&magic_buffer)[2];
	((unsigned char *)&temp)[2] = ((unsigned char *)&magic_buffer)[1];
	((unsigned char *)&temp)[3] = ((unsigned char *)&magic_buffer)[0];
	if (temp != COREWAR_EXEC_MAGIC)
		error_exit("Invalid magic number\n", fd);
	if (new_node == NULL)
	{
		close(fd);
		error_exit("Error, player wasnt malloced.\n", fd);
	}
	ft_bzero(new_node, sizeof(t_player));
	// new_node->id = 0;
	new_node->exec_code = NULL;
	return (*new_node);
}

void				parse_exec_code(int fd, t_player *player)
{
	ssize_t			rd;
	unsigned char	check[1];

	player->exec_code = (unsigned char *)malloc(sizeof(unsigned char) * (player->size + 1));
	if (!player->exec_code)
		error_exit("Error while executable code parsing\n", fd);
	rd = read(fd, player->exec_code, player->size);
	if (rd != (ssize_t)player->size)
		error_exit("Error executable reading.\n", fd);
	if (read(fd, &check, 1) != 0){
		printf("player='%s'\n", player->name);
		error_exit("Not null after exec, its not so good mate.", fd);
	}
}
void				parse_all_players(int ac, char **av, t_vm *vm)
{
	int				fd;
	int				i;
	unsigned int	id;

	id = 0;
	i = 0;
	while (++i < ac)//stupid!
	{
		if (ft_strstr(av[i], ".cor"))
		{
			fd = open(av[i], O_RDONLY);
			if (fd < 0)
				error_exit("Failed to read file.\n", fd);
			else
			{
				vm->players[id] = player_struct_init(fd, &vm->players[id]);
				parse_player_name(fd, &vm->players[id]);
				parse_size(fd, &vm->players[id]);
				parse_comment(fd, &vm->players[id]);
				parse_exec_code(fd, &vm->players[id]);
				vm->players[id].id = id;
				vm->players[id].player_number = (id + 1) * (-1);
			}
			id++;
			close(fd);
		}
	}
}
