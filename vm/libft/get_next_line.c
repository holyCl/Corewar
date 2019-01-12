/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 20:17:52 by inazarin          #+#    #+#             */
/*   Updated: 2018/03/08 20:17:54 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_magic(char **line, char *res, char *buf)
{
	char		*end;
	char		*for_del;

	if (ft_strchr(res, '\n'))
	{
		for_del = res;
		end = ft_strchr(res, '\n');
		*end = '\0';
		*line = ft_strdup(res);
		res = ft_strdup(end + 1);
		ft_strdel(&for_del);
	}
	else
	{
		*line = ft_strdup(res);
		ft_strdel(&res);
	}
	(buf) ? ft_strdel(&buf) : 0;
	return (res);
}

char	*ft_changes(char *res, char *buf, ssize_t bytes)
{
	char		*tmp;

	buf[bytes] = '\0';
	tmp = res;
	res = ft_strjoin(tmp, buf);
	free(tmp);
	ft_strdel(&buf);
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static char	*res[1200];
	char		*buf;
	ssize_t		bytes;

	if (fd < 0 || BUFF_SIZE < 1 || !line || (bytes = read(fd, "", 0)) < 0)
		return (-1);
	res[fd] == NULL ? res[fd] = ft_strnew(0) : (0);
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!ft_strchr(res[fd], '\n') && (bytes = read(fd, buf, BUFF_SIZE)))
	{
		res[fd] = ft_changes(res[fd], buf, bytes);
		return (get_next_line(fd, line));
	}
	if (res[fd] == NULL || res[fd][0] == '\0')
	{
		(buf) ? ft_strdel(&buf) : 0;
		return (0);
	}
	if ((ft_strchr(res[fd], '\n') || ft_strlen(res[fd]) > 0))
	{
		res[fd] = ft_magic(line, res[fd], buf);
		return (1);
	}
	(buf) ? ft_strdel(&buf) : 0;
	return (0);
}
